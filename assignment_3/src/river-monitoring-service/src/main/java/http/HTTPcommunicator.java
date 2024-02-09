package http;

import java.util.Optional;
import java.util.concurrent.CompletableFuture;

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
        CompletableFuture<Optional<Integer>> future = new CompletableFuture<>();

        client
            .get(PORT, HOST, "/api/data")
            .send()
            .onSuccess(res -> {
                System.out.println("Getting - Received response with status code: " + res.statusCode());
                String controlType = res.bodyAsJsonArray().getJsonObject(0).getString("controlType");
                if (controlType.equals("auto")) {
                    future.complete(Optional.of(res.bodyAsJsonArray().getJsonObject(0).getInteger("valveValue")));
                } else {
                    future.complete(Optional.empty());
                }
                
            })
            .onFailure(err -> {
                System.out.println("Something went wrong " + err.getMessage());
                // Completa il future con Optional.empty() in caso di errore
                future.complete(Optional.empty());
            });

        try {
            return future.get();
        } catch (Exception e) {
            System.err.println("Exception while getting response: " + e.getMessage());
            return Optional.empty();
        }
    }
}
