package serial;

import java.util.Optional;

public interface SerialCommunicator {
    public <T> void write(T text);

    public Optional<Integer> get(); 
}
