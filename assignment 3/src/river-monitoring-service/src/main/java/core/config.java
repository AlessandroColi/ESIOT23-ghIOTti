package core;
public class config{
    
    public enum WaterLevel{
        WL1(1),  //lower water level for normal state
        WL2(2),  //upper water level for normal state
        WL3(3),  //PRE-ALARM-TOO-HIGH state water level
        WL4(4);  //ALARM-TOO-HIGH state water level

        public final double level;

        WaterLevel(double level){
            this.level = level;
        }
    }

    public enum GateLevel{
        L0(0),   //valve opening level for ALARM-TOO-LOW state
        L1(25),  //valve opening level for normal state
        L2(50),  //valve opening level for ALARM-TOO-HIGH state
        L3(100); //valve opening level for ALARM-TOO-HIGH-CRITIC state

        public final int perc;

        GateLevel(int p){
            this.perc = p;
        }
    }

    public enum UpdateFrequency{
        F1(200), //frequency for normal state
        F2(100); //frequency for allert states

        public final double millis;

        UpdateFrequency(double f){
            this.millis = f;
        }
    }

    public enum State{
        ALARM_TOO_LOW,
        NORMAL,
        PRE_ALARM_TOO_HIGH,
        ALARM_TOO_HIGH,
        ALARM_TOO_HIGH_CRITIC;
    }
}