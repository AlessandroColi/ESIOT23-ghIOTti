package pc.carwash;

public class LogicImpl implements Logic{

    private static String PORT = "COM6";
    private final SerialCommChannel serial = new SerialCommChannel(PORT ,9600);
    private int totalWashes = 0;
    private CarWasherState state = CarWasherState.MAINTENANCE;
    private double temperature = 0;

    public LogicImpl() throws Exception {}

    @Override
    public double getTemperature() {
        return temperature;
    }

    @Override
    public CarWasherState getState() {
        return state;
    }

    @Override
    public int getWashes() {
        return totalWashes;
    }

    @Override
    public void update() throws InterruptedException {
        if( serial.isMsgAvailable() ){
            unpackString(serial.receiveMsg());
        }
    }

    @Override
    public void maintenenceDone() {
        if( state == CarWasherState.MAINTENANCE){
            serial.sendMsg("Maintenence done");
        }
    }
    private void unpackString(String input) {
        // Split the input string using ":" as the delimiter format is state:Temperature
        String[] parts = input.split(":");

        if (parts.length == 2) {
            try {
                String stringValue = parts[0];
                temperature = Double.parseDouble(parts[1]);
                CarWasherState currState = toState(stringValue);
                if(state == CarWasherState.WASHING
                        && currState == CarWasherState.LEAVING_WASHING_AREA) {
                    totalWashes++;
                }
                state = currState;
            } catch (NumberFormatException e) {
                System.out.println("Error parsing values: " + e.getMessage());
            }
        } else {
            System.out.println("Invalid input format");
        }
    }

    private CarWasherState toState(String stringValue) {
        return switch ( stringValue ){
            case "WAITING_FOR_CAR" -> CarWasherState.WAITING_FOR_CAR;
            case "CAR_DETECTED_FOR_CHECK_IN" -> CarWasherState.CAR_DETECTED_FOR_CHECK_IN;
            case "ENTERING_WASHING_AREA" -> CarWasherState.ENTERING_WASHING_AREA;
            case "READY_TO_WASH" -> CarWasherState.READY_TO_WASH;
            case "WASHING" -> CarWasherState.WASHING;
            case "LEAVING_WASHING_AREA" -> CarWasherState.LEAVING_WASHING_AREA;
            case "CHECK_OUT" -> CarWasherState.CHECK_OUT;
            case "MAINTENANCE" -> CarWasherState.MAINTENANCE;
            default -> throw new IllegalArgumentException(stringValue + "State does not exist");
        };
    }
}
