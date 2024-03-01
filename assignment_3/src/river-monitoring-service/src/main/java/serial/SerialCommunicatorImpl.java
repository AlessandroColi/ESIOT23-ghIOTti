package serial;

import java.util.Optional;
import java.util.concurrent.*;
import jssc.*;

public class SerialCommunicatorImpl implements SerialCommunicator, SerialPortEventListener {
    
    private SerialPort serialPort;
    private String lastMsg = null;
    private StringBuffer currentMsg = new StringBuffer("");

    public SerialCommunicatorImpl(String portName, int rate) throws Exception{
        serialPort = new SerialPort(portName);

        serialPort.openPort();

        serialPort.setParams(rate,
                                SerialPort.DATABITS_8,
                                SerialPort.STOPBITS_1,
                                SerialPort.PARITY_NONE);
                                
        serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | 
                                            SerialPort.FLOWCONTROL_RTSCTS_OUT);
                                        
        serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
    }

    @Override
    public void write(Integer text) {
        char[] array = (text + "\n").toCharArray();
        byte[] bytes = new byte[array.length];
        for (int i = 0; i < array.length; i++) {
            bytes[i] = (byte) array[i];
        }

        try {
                synchronized (serialPort) {
                    serialPort.writeBytes(bytes);
                }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public Optional<String> get() throws InterruptedException {
        String msg = lastMsg;
        lastMsg = null;
        return Optional.ofNullable(msg);
    }

    public void close() {
        try {
            if (serialPort != null) {
                serialPort.removeEventListener();
                serialPort.closePort();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    @Override
    public void serialEvent(SerialPortEvent event) {
        if (event.isRXCHAR()) {
            try {
                String msg = serialPort.readString(event.getEventValue());

                msg = msg.replaceAll("\r", "");
                msg = msg.replaceAll(" ", "");

                currentMsg.append(msg);

                boolean goAhead = true;

                while (goAhead) {
                    String msg2 = currentMsg.toString();
                    int index = msg2.indexOf("\n");
                    if (index >= 0) {
                        lastMsg = msg2.substring(0, index);
                        currentMsg = new StringBuffer("");
                        if(index + 1 < msg2.length()) {
                            currentMsg.append(msg2.substring(index + 1));
                        }
                    } else {
                        goAhead = false;
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                System.out.println("Error in receiving string from COM-port " + e);
            }
        }
    }
    
}
