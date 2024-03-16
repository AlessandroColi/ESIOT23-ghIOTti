package http;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.ext.web.handler.CorsHandler;

import java.util.LinkedList;

public class DataService extends AbstractVerticle {

	private int port;
	private static final int MAX_SIZE = 10;
	private LinkedList<Data> values;
	
	public DataService(int port) {
		values = new LinkedList<>();		
		this.port = port;
	}

	@Override
	public void start() {		
		Router router = Router.router(vertx);
		router.route().handler(BodyHandler.create());
		router.route().handler(CorsHandler.create("*"));
		router.post("/api/data").handler(this::handleAddNewData);
		router.get("/api/data").handler(this::handleGetData);		
		vertx
			.createHttpServer()
			.requestHandler(router)
			.listen(port);

		log("Service ready on port: " + port);
	}
	
	private void handleAddNewData(RoutingContext routingContext) {
		HttpServerResponse response = routingContext.response();
		JsonObject res = routingContext.getBodyAsJson();
		if (res == null) {
			sendError(400, response);
		} else {
			String controlType = res.getString("controlType");
			long time = System.currentTimeMillis();
			double waterLevel = res.getDouble("waterLevel");
			int valveLevel = (controlType == "DATA") ? res.getInteger("valveLevel") : Integer.parseInt(res.getString("valveLevel"));
			String state = res.getString("state");
			
			values.addFirst(new Data(waterLevel, valveLevel, state, time, controlType));
			while (values.stream().filter(x -> x.getControlType().equals("DATA")).count() > MAX_SIZE) {
				values.removeLast();
			}
			
			log("New dataset [control type: " + controlType + ", valve level: " + valveLevel + "]");
			response.setStatusCode(200).end();
		}
	}
	
	private void handleGetData(RoutingContext routingContext) {
		JsonArray arr = new JsonArray();
		for (Data p: values) {
			JsonObject data = new JsonObject();
			data.put("controlType", p.getControlType());
			data.put("waterLevel", p.getWaterLevel());
			data.put("valveLevel", p.getValveLevel());
			data.put("state", p.getState());
			data.put("time", p.getTime());
			arr.add(data);
		}
		routingContext.response()
			.putHeader("content-type", "application/json")
			.end(arr.encodePrettily());
	}
	
	private void sendError(int statusCode, HttpServerResponse response) {
		response.setStatusCode(statusCode).end();
	}

	private void log(String msg) {
		//System.out.println("[SERVICE] "+msg);
	}

}