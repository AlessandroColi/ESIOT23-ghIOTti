package serial;

public interface SerialCommunicator {
    public <T> void write(T text);
}
