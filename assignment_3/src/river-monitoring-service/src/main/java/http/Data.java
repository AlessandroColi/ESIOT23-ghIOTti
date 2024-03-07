package http;

class Data {
	private double waterLevel;
	private int valveLevel;
	private String state;
	private long time;
	private String controlType;
	
	public Data(double waterLevel, int valveLevel, String state, long time, String controlType) {
		this.waterLevel = waterLevel;
		this.valveLevel = valveLevel;
		this.state = state;
		this.time = time;
		this.controlType = controlType;
	}
	
	public double getWaterLevel() {
		return waterLevel;
	}
	
	public int getValveLevel() {
		return valveLevel;
	}
	
	public String getState() {
		return state;
	}
	
	public long getTime() {
		return time;
	}

	public String getControlType() {
		return controlType;
	}
}
