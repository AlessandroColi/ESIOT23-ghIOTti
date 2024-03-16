package core;

import mqtt.*;
import serial.*;
import http.*;

import java.nio.ByteBuffer;
import java.util.Optional;
import java.util.concurrent.Flow;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class RiverMonitoringService {

    private final static String backend = "backend";
    private final static String esp = "esp32";
    private final MqttProtocol espComm = new MqttProtocol();
    private final SerialCommunicator arduinoComm = new  SerialCommunicatorImpl("COM9",9600);
    private final Communicator dashboardComm = new CommunicatorHTTP();
    private final stateControl state = new stateControl();
    private double waterLevel = 0.0;
    private boolean arduino_manual = false;
    private int arduino_level;
    private final ScheduledExecutorService scheduler = Executors.newSingleThreadScheduledExecutor();
    private boolean keepAlive = true;

    public RiverMonitoringService() throws Exception {
    }

    public void run() {
        espComm.initialize();
        espComm.setupChannel(backend, esp);
        espComm.setupChannel(esp, backend);

        espComm.readFromChannel(esp, backend).subscribe(new Flow.Subscriber<byte[]>() {
                    @Override
                    public void onSubscribe(Flow.Subscription subscription){
                        subscription.request(Long.MAX_VALUE); // Request all available messages
                    }

                    @Override
                    public void onNext(byte[] level) {
                        // Convert bytes to hexadecimal string
                        StringBuilder hexStringBuilder = new StringBuilder();
                        for (byte b : level) {
                            hexStringBuilder.append(String.format("%02X", b));
                        }
                        String hexString = hexStringBuilder.toString();

                        // Convert hexadecimal string to ASCII
                        StringBuilder asciiStringBuilder = new StringBuilder();
                        for (int i = 0; i < hexString.length(); i += 2) {
                            String str = hexString.substring(i, i + 2);
                            asciiStringBuilder.append((char) Integer.parseInt(str, 16));
                        }
                        String asciiString = asciiStringBuilder.toString();

                        // Convert ASCII string to double
                        double wl = Double.parseDouble(asciiString.trim());
                        if(wl > 0){
                            state.updateLevel(wl);
                            waterLevel = wl;
                        }
                    }

                    @Override
                    public void onError(Throwable e) {
                        throw new RuntimeException("mqtt listen error: ", e);
                    }

                    @Override
                    public void onComplete() {
                        keepAlive = false;
                    }
                });
        tick();
    }

    private void tick() {
        scheduler.schedule( ()-> {
            updateAll(state.getUpdateFrequency(),
                    getGateLevel(),
                    waterLevel,
                    state.getState());
            if(keepAlive) tick();
        },state.getUpdateFrequency(), TimeUnit.MILLISECONDS);
    }

    private int getGateLevel() {
        return getArduinoLevel().orElse(getDashboardLevel().orElse(state.getGateLevel()));
    }

    private Optional<Integer> getDashboardLevel() {
        Optional<Integer> val =  dashboardComm.check();
        return val;
    }

    private Optional<Integer> getArduinoLevel() {
        Optional<String> arduino;
        try {
            arduino = arduinoComm.get();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        if(arduino_manual){
            if ( arduino.isPresent() && arduino.get().equals("AUTO")) {
                arduino_manual = false;
            }else {
                arduino.ifPresent(s -> arduino_level = Integer.parseInt(s));
            }
        }else{
            if(arduino.isPresent()){
                try{
                    arduino_level = Integer.parseInt(arduino.get());
                    arduino_manual = true;
                }catch (NumberFormatException ignored){}
            }
        }
        return arduino_manual ? Optional.of(arduino_level) : Optional.empty();
    }

    private void updateAll(int frequency, int gateLevel, double waterLevel, String state) {
        System.out.println( "wl: "+waterLevel + " -> " + state + " f: " + frequency + " gl: " + gateLevel);
        updateEsp(frequency);
        updateArduino(gateLevel);
        updateDashboard(state,waterLevel,gateLevel);
    }

    private void updateDashboard(String state, double waterLevel, int gateLevel) {
        dashboardComm.write(waterLevel,gateLevel,state);
    }

    private void updateArduino(int level) {
        arduinoComm.write(level);
    }

    private void updateEsp(int frequency) {
        try {
            espComm.writeToChannel(backend, esp, intToByteArray(frequency));
        } catch (ProtocolError e) {
            throw new RuntimeException("mqtt write error: ", e);
        }
    }

    private byte[] intToByteArray(int value) {
        ByteBuffer buffer = ByteBuffer.allocate(Integer.BYTES);
        buffer.putInt(value);
        return buffer.array();
    }

    public static void main(String[] args) throws Exception {
        RiverMonitoringService monitoringService = new RiverMonitoringService();
        monitoringService.run();
    }
}
