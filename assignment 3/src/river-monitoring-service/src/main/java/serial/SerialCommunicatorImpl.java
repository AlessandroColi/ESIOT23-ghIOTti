package serial;

import java.util.Optional;
import java.util.concurrent.*;
import jssc.*;

public class SerialCommunicatorImpl implements SerialCommunicator, SerialPortEventListener {
    
    private SerialPort serialPort;
    private BlockingQueue<String> queue;
    private StringBuffer currentMsg = new StringBuffer("");

    public SerialCommunicatorImpl(String portName, int rate) throws Exception{
        queue = new ArrayBlockingQueue<String>(100);
        serialPort = new SerialPort(portName);

        serialPort.openPort();

        serialPort.setParams(rate,
                                SerialPort.DATABITS_8,
                                SerialPort.STOPBITS_1,
                SerialPort.PARITY_NONE);
                                
        serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | 
                                            SerialPort.FLOWCONTROL_RTSCTS_OUT);
                                        
        // serialPort.addEventListener(this, SerialPort.MASK_RXCHAR);
        serialPort.addEventListener(this);
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
    public Optional<Integer> get() throws InterruptedException {
        return Optional.ofNullable(Integer.parseInt(queue.take()));
    }


    @Override
    public void serialEvent(SerialPortEvent serialPortEvent) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'serialEvent'");
    }

    private boolean isMsgPresent() {
        return !queue.isEmpty() && (queue.peek().length() > 11);
    }
    
}
