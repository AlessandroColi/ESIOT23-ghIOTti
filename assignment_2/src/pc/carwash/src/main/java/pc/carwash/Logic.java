package pc.carwash;

public interface Logic {
    public double getTemperature();
    public CarWasherState getState();
    public int getWashes();
    public void update() throws InterruptedException;
    public void maintenenceDone();
}
