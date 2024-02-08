package http;

import util.Pair;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;

public class HttpCommunicator implements Communicator {

    private final String baseUrl;

    public HttpCommunicator(String baseUrl) {
        this.baseUrl = baseUrl;
    }

    @Override
    public void write(double waterLevel, int gateLevel, String state) {
        try {
            URL url = new URL(baseUrl + "/api/room");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Type", "application/json");
            conn.setDoOutput(true);

            String jsonInputString = String.format("{\"waterLevel\": %f, \"gateLevel\": %d, \"state\": \"%s\"}",
                    waterLevel, gateLevel, state);

            try (OutputStream os = conn.getOutputStream()) {
                byte[] input = jsonInputString.getBytes("utf-8");
                os.write(input, 0, input.length);
            }

            try (BufferedReader br = new BufferedReader(
                    new InputStreamReader(conn.getInputStream(), "utf-8"))) {
                StringBuilder response = new StringBuilder();
                String responseLine;
                while ((responseLine = br.readLine()) != null) {
                    response.append(responseLine.trim());
                }
                // Process response if needed
            }
        } catch (Exception e) {
            e.printStackTrace();
            // Handle exception
        }
    }

    @Override
    public Pair<Boolean, Integer> check() {
        try {
            URL url = new URL(baseUrl + "/api/room");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setRequestMethod("GET");
    
            try (BufferedReader br = new BufferedReader(
                    new InputStreamReader(conn.getInputStream(), "utf-8"))) {
                StringBuilder response = new StringBuilder();
                String responseLine;
                while ((responseLine = br.readLine()) != null) {
                    response.append(responseLine.trim());
                }
    
                // Assume response format is something like "gateLevel: 5, manualControl: true"
                String[] parts = response.toString().split(",");
                int gateLevel = Integer.parseInt(parts[0].split(":")[1].trim());
                boolean manualControl = Boolean.parseBoolean(parts[1].split(":")[1].trim());
    
                return new Pair<>(manualControl, gateLevel);
            }
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
