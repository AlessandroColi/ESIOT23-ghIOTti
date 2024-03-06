package http;

class Data {
	private double waterLevel;
	private int valveLevel;
	private String state;
	private long time;
	
	public Data(double waterLevel, int valveLevel, String state, long time) {
		this.waterLevel = waterLevel;
		this.valveLevel = valveLevel;
		this.state = state;
		this.time = time;
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
}
