package core;

import mqtt.*;
import serial.*;
import http.*;

import java.nio.ByteBuffer;
import java.util.Optional;
import java.util.concurrent.Flow;

public class RiverMonitoringService {

    private final static String backend = "backend";
    private final static String esp = "esp32";
    private final MqttProtocol espComm = new MqttProtocol();
    private SerialCommunicator arduinoComm ; //TODO piso inizializza qua e rendi final
    private final Communicator dashboardComm = new HTTPcommunicator();
    private final stateControl state = new stateControl();

    private boolean keepAlive = true;


    public void run() {
        espComm.initialize();
        espComm.setupChannel(backend, esp);
        espComm.readFromChannel(esp, backend).subscribe(new Flow.Subscriber<byte[]>() {
                    @Override
                    public void onSubscribe(Flow.Subscription subscription){
                    }

                    @Override
                    public void onNext(byte[] level) {
                        // Process the received message
                        double waterLevel = ByteBuffer.wrap(level).getDouble();
                        state.updateLevel(waterLevel);
                        updateAll(state.getUpdateFrequency(),
                                getGateLevel(),
                                waterLevel,
                                state.getState());
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

        while (keepAlive) {
            try {
                Thread.sleep(state.getUpdateFrequency());
            } catch (InterruptedException e) {
                throw new RuntimeException("loop error: ",e);
            }
        }
    }

    private int getGateLevel() {

        Optional<Integer> arduino = arduinoComm.get();
        Optional<Integer> dashboard = dashboardComm.check();

        return arduino.orElse(dashboard.orElse(state.getGateLevel()));

    }

    private void updateAll(int frequency, int gateLevel, double waterLevel, String state) {
        updateEsp(frequency);
        updateArduino(gateLevel);
        updateDashboard(state,waterLevel,gateLevel);
    }

    private void updateDashboard(String state, double waterLevel, int gateLevel) {
        //TODO rivedere dopo iml di http
        dashboardComm.write(waterLevel,gateLevel,state);
    }

    private void updateArduino(int level) {
        //TODO rivedere dopo impl della serial
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

    public static void main(String[] args) {
        RiverMonitoringService monitoringService = new RiverMonitoringService();
        monitoringService.run();
    }
}