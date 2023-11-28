package pc.carwash;

public enum CarWasherState {
    WAITING_FOR_CAR("Waiting for Car"),
    CAR_DETECTED_FOR_CHECK_IN("Car Detected for Check-in"),
    ENTERING_WASHING_AREA("Car entering Washing Area"),
    READY_TO_WASH("Car ready to Wash"),
    WASHING("Car washing"),
    LEAVING_WASHING_AREA("Car Leaving Washing Area"),
    CHECK_OUT("Car Checking-Out"),
    MAINTENANCE("Maintenance required");

    private final String displayValue;

    CarWasherState(String displayValue) {
        this.displayValue = displayValue;
    }

    @Override
    public String toString() {
        return displayValue;
    }
}

