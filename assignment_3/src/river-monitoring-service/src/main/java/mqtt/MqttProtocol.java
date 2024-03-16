package mqtt;

import org.eclipse.paho.client.mqttv3.*;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;


import util.Pair;

import java.util.HashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.SubmissionPublisher;

public class MqttProtocol {

    private final String host = "broker.mqtt-dashboard.com";
    private final int port = 1883;

    private final ExecutorService executorService = Executors.newSingleThreadExecutor();

    private final SubmissionPublisher<byte[]> defaultFlow = new SubmissionPublisher<>();
    private final HashMap<Pair<String, String>, String> registeredTopics = new HashMap<>();
    private final HashMap<String, SubmissionPublisher<byte[]>> topicChannels = new HashMap<>();

    private MqttAsyncClient mqttClient;

    public SubmissionPublisher<byte[]> readFromChannel(String from, String to) {
        String candidateTopic = registeredTopics.get(new Pair<>(from, to));
        SubmissionPublisher<byte[]> channel = topicChannels.get(candidateTopic);
        return channel != null ? channel : defaultFlow;
    }

    public void setupChannel(String source, String destination) {
        registeredTopics.put(new Pair<>(source, destination), toTopics(source, destination));
        topicChannels.put(toTopics(source, destination), new SubmissionPublisher<>());
    }

    public void writeToChannel(String from, String to, byte[] message) throws ProtocolError {
        String topic = registeredTopics.get(new Pair<>(from, to));

        if (topic == null) {
            throw new ProtocolError.EntityNotRegistered(to);
        }

        MqttMessage mqttMessage = new MqttMessage(message);
        mqttMessage.setQos(0);

        executorService.submit(() -> {
            try {
                IMqttToken token = mqttClient.publish(topic, mqttMessage);
                token.waitForCompletion();
            } catch (MqttException e) {
                throw new RuntimeException(new ProtocolError.ProtocolException(e));
            }
        });
    }

    public void initialize() {
        try {
            mqttClient = new MqttAsyncClient("tcp://" + host + ":" + port, "MqttProtocol Test", new MemoryPersistence());

            executorService.submit(() -> {
                try {
                    IMqttToken token = mqttClient.connect();
                    token.waitForCompletion();

                    MqttCallback callback = new MqttCallback() {

                        @Override
                        public void connectionLost(Throwable throwable) {

                        }

                        @Override
                        public void messageArrived(String topic, MqttMessage message) {
                            byte[] payload = message.getPayload();
                            requireNotNull(payload);
                            SubmissionPublisher<byte[]> channel = topicChannels.get(topic);
                            if (channel != null) {
                                channel.submit(payload);
                            }
                        }

                        @Override
                        public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken) {

                        }
                    };

                    mqttClient.setCallback(callback);
                    mqttClient.subscribe(new String[]{"RiverMonitoring/+/+"}, new int[]{0}).waitForCompletion();
                } catch (MqttException e) {
                    throw new RuntimeException(new ProtocolError.ProtocolException(e));
                }
            });

        } catch (Exception e) {
            throw new RuntimeException(new ProtocolError.ProtocolException(e));
        }
    }

    public void disconnect() {
        try {
            mqttClient.disconnect();
            mqttClient.close();
            executorService.shutdownNow();

        } catch (MqttException e) {
            throw new RuntimeException(new ProtocolError.ProtocolException(e));
        }
    }

    private String toTopics(String source, String destination) {
        return "RiverMonitoring/" + source + "/" + destination;
    }

    private static <T> void requireNotNull(T value) {
        if (value == null) {
            throw new IllegalArgumentException("Message cannot be null");
        }
    }
}
