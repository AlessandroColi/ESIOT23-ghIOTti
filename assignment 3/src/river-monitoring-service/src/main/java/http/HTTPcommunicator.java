package http;

import util.Pair;
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.InetSocketAddress;
import java.net.URL;
import com.sun.net.httpserver.HttpServer;

public class HTTPcommunicator implements Communicator {
    private static final int PORT = 3030;
    private static final String BASE_PATH = "http://localhost:3030";

    public HTTPcommunicator() {
        try {
            HttpServer server = HttpServer.create(new InetSocketAddress(PORT), 0);
            server.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void write(double waterLevel, int gateLevel, String state) {
        try {
            URL url = new URL(BASE_PATH + "/api/room");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("POST");
            connection.setDoOutput(true);
            
            String postData = "waterLevel=" + waterLevel + "&gateLevel=" + gateLevel + "&state=" + state;
            try (DataOutputStream wr = new DataOutputStream(connection.getOutputStream())) {
                wr.writeBytes(postData);
                wr.flush();
            }

            int responseCode = connection.getResponseCode();
            System.out.println("POST Response Code: " + responseCode);
            if (responseCode == HttpURLConnection.HTTP_OK) {
                System.out.println("POST request successful");
            } else {
                System.out.println("POST request failed");
            }

            connection.disconnect();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public Pair<Boolean, Integer> check() {
        try {
            URL url = new URL(BASE_PATH + "/api/room");
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            
            int responseCode = connection.getResponseCode();
            System.out.println("GET Response Code: " + responseCode);
            if (responseCode == HttpURLConnection.HTTP_OK) {
                try (BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()))) {
                    String inputLine;
                    StringBuilder response = new StringBuilder();
                    while ((inputLine = in.readLine()) != null) {
                        response.append(inputLine);
                    }
                    System.out.println("GET response: " + response.toString());
                    
                    // Analisi della risposta per estrarre le informazioni manuali e di livello della valvola
                    boolean manual = false;
                    int level = 0;
                    String[] parts = response.toString().split(",");
                    for (String part : parts) {
                        String[] keyValue = part.split(":");
                        if (keyValue[0].trim().equals("\"manual\"")) {
                            manual = Boolean.parseBoolean(keyValue[1].trim());
                        } else if (keyValue[0].trim().equals("\"level\"")) {
                            level = Integer.parseInt(keyValue[1].trim());
                        }
                    }
    
                    // Creazione e restituzione di un oggetto Pair<Boolean, Integer>
                    return new Pair<>(manual, level);
                }
            } else {
                System.out.println("GET request failed");
            }
    
            connection.disconnect();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }    
}
