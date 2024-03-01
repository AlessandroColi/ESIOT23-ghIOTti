package http;

import java.util.Optional;

import io.vertx.core.Vertx;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.client.WebClient;

public class HTTPcommunicator implements Communicator {
    private static final int PORT = 8080;
    private static final String HOST = "localhost";
    private final Vertx vertx;
    private final WebClient client;

    public HTTPcommunicator() {
        this.vertx = Vertx.vertx();
        client = WebClient.create(vertx);
		DataService service = new DataService(PORT);
		vertx.deployVerticle(service);
    }

    @Override
    public void write(double waterLevel, int gateLevel, String state) {
        JsonObject item = new JsonObject();
		item.put("waterLevel", waterLevel);
        item.put("valveValue", gateLevel);
        item.put("state", state);
        item.put("controlType", "auto");

		client
		.post(PORT, HOST, "/api/data")
		.sendJson(item)
		.onSuccess(response -> {
			System.out.println("Posting - Received response with status code: " + response.statusCode());
		});
    }

    @Override
    public Optional<Integer> check() {
        return Optional.empty();    //TODO
    }
}
