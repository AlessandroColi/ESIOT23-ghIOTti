package core;

public class stateControl {
    private config.State state = config.State.NORMAL;

    public void updateLevel(double waterLevel){
        if( waterLevel < config.WL1){
            this.state = config.State.ALARM_TOO_LOW;
        }else if( inRange(waterLevel, config.WL1 , config.WL2  ) ){
            this.state = config.State.NORMAL;
        }else if( inRange(waterLevel, config.WL2 , config.WL3  ) ){
            this.state = config.State.PRE_ALARM_TOO_HIGH;
        }else if( inRange(waterLevel, config.WL3 , config.WL4  ) ){
            this.state = config.State.ALARM_TOO_HIGH;
        }else{
            this.state = config.State.ALARM_TOO_HIGH_CRITIC;
        }
    }

    private static boolean inRange(double value, double start, double end) {
        double epsilon = 1e-15;
        return value >= start - epsilon && value <= end + epsilon;
    }

    public int getUpdateFrequency(){
        return state.updateFrequency;
    }

    public int getGateLevel(){
        return state.gateLevel;
    }

    public String getState() { return state.toString(); }

}
