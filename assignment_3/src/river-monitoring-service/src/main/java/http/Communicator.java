package http;

import java.util.Optional;

public interface Communicator {

    /**
     * @param waterLevel
     * @param gateLevel
     * @param state
     */
    public void write(double waterLevel, int gateLevel, String state);
    /**
     * @return empty if the gate level is set automatically, an integer if is set manually from the dashboard.
     */
    public Optional<Integer> check();
}
