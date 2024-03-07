package http;

import java.util.Optional;
import java.util.concurrent.atomic.AtomicReference;

import io.vertx.core.Vertx;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;
import io.vertx.ext.web.client.WebClient;

public class CommunicatorHTTP implements Communicator {
    private static final int PORT = 8080;
    private static final String HOST = "localhost";
    private final Vertx vertx;
    private final WebClient client;

    public CommunicatorHTTP() {
        this.vertx = Vertx.vertx();
        client = WebClient.create(vertx);
        DataService service = new DataService(PORT);
        vertx.deployVerticle(service);
    }

    @Override
    public void write(double waterLevel, int valveLevel, String state) {
        JsonObject item = new JsonObject();
        item.put("waterLevel", waterLevel);
        item.put("valveLevel", valveLevel);
        item.put("state", state);
        item.put("controlType", "DATA");

        client
        .post(PORT, HOST, "/api/data")
        .sendJson(item)
        .onSuccess(response -> {
            System.out.println("Posting - Received response with status code: " + response.statusCode());
        });
    }

    @Override
    public Optional<Integer> check() {
        AtomicReference<Optional<Integer>> value = new AtomicReference<>(Optional.empty());
        client
        .get(PORT, HOST, "/api/data")
        .send()
        .onSuccess(res -> { 
            JsonArray response = res.bodyAsJsonArray();
            if (!response.isEmpty()) {
                JsonObject jsonObject = response.getJsonObject(0);
                if (jsonObject.getString("controlType").equals("SET")) {
                    value.set(Optional.of(jsonObject.getInteger("valveLevel")));
                }
            }
        })
        .onFailure(err -> System.out.println("Something went wrong " + err.getMessage()));
        try {
            Thread.sleep(200);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Optional<Integer> result = value.get();
        return result;
    }
}

