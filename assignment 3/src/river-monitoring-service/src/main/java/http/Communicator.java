package http;

import java.util.Optional;

public interface Communicator {
    /*
    sends the values to the dashboard
     */
    public void write(double waterLevel, int gateLevel, String state);
    /*
    left side rapresents if the gate level is set manually by the dashjboard
    right side rapresents the level set
     */
    public Optional<Integer> check();
}
