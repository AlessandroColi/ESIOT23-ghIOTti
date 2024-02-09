package serial;

import java.util.Optional;

public interface SerialCommunicator {

    /**
     * Send a message represented by a string (without new line).
     *
     * Asynchronous model.
     *
     * @param msg
     */
    public void write(Integer text);

    /**
     * To receive a message.
     *
     * Blocking behaviour.
     */
    public Optional<Integer> get() throws InterruptedException;
}
