package http;

class DataPoint {
	private double waterLevel;
	private int valveValue;
	private long time;
	private String state, controlType;
	
	public DataPoint(double waterLevel, int valveValue, long time, String state, String controlType) {
		this.waterLevel = waterLevel;
		this.valveValue = valveValue;
		this.time = time;
		this.state = state;
		this.controlType = controlType;
	}
	
	public double getValveValue() {
		return valveValue;
	}

	public double getWaterLevel() {
		return waterLevel;
	}
	
	public long getTime() {
		return time;
	}
	
	public String getState() {
		return state;
	}

	public String getControlType() {
		return controlType;
	}
}