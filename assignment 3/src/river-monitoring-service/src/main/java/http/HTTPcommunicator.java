package http;

import util.Pair;

public interface HTTPcommunicator {
    /*
    sends the values to the dashboard
     */
    public void write(double waterLevel, int gateLevel, String state);
    /*
    left side rapresents if the gate level is set manually by the dashjboard
    right side rapresents the level set
     */
    public Pair<Boolean,Integer> check();
}
