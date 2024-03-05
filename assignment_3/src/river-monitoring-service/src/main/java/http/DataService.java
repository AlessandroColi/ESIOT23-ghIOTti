package http;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;

import java.util.Date;
import java.util.LinkedList;

public class DataService extends AbstractVerticle {

	private int port;
	private static final int MAX_SIZE = 10;
	private LinkedList<DataPoint> values;
	
	public DataService(int port) {
		values = new LinkedList<>();		
		this.port = port;
	}

	@Override
	public void start() {		
		Router router = Router.router(vertx);
		router.route().handler(BodyHandler.create());
		router.route().handler(CorsHandler.create("*"));
		router.post("/api/data").handler(this::handlePostData);
		router.get("/api/data").handler(this::handleGetData);		
		vertx
			.createHttpServer()
			.requestHandler(router)
			.listen(port);

		log("Service ready on port: " + port);
	}
	
	private void handlePostData(RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		JsonObject res = routingContext.getBodyAsJson();
		if (res == null) {
			sendError(400, response);
		} else {
			long time = System.currentTimeMillis();
			double waterLevel = 1.0;	// TODO: per ora waterLevel è fasullo
			int valveValue = Integer.parseInt(res.getString("valveValue"));
			String state = res.getString("state");
			String controlType = res.getString("controlType");
			
			values.addFirst(new DataPoint(waterLevel, valveValue, time, state, controlType));
			if (values.size() > MAX_SIZE) {
				values.removeLast();
			}
			
			log("New valveValue: " + valveValue + " from " + state + " on " + new Date(time));
			response.setStatusCode(200).end();
		}
	}
	
	private void handleGetData(RoutingContext routingContext) {
		JsonArray arr = new JsonArray();
		for (DataPoint p: values) {
			JsonObject data = new JsonObject();
			data.put("time", p.getTime());
			data.put("valveValue", p.getValveValue());
			data.put("waterLevel", p.getWaterLevel());
			data.put("state", p.getState());
			data.put("controlType", p.getControlType());
			arr.add(data);
		}
		routingContext.response()
			.putHeader("Content-Type", "application/json")
			.end(arr.encodePrettily());
	}
	
	private void sendError(int statusCode, HttpServerResponse response) {
		response.setStatusCode(statusCode).end();
	}

	private void log(String msg) {
		//System.out.println("[DATA SERVICE] "+msg);
	}

}