import org.eclipse.paho.mqttv5.client.IMqttToken;
import org.eclipse.paho.mqttv5.client.MqttAsyncClient;
import org.eclipse.paho.mqttv5.client.MqttCallback;
import org.eclipse.paho.mqttv5.client.MqttConnectionOptions;
import org.eclipse.paho.mqttv5.client.persist.MemoryPersistence;
import org.eclipse.paho.mqttv5.common.MqttException;
import org.eclipse.paho.mqttv5.common.MqttMessage;
import org.eclipse.paho.mqttv5.common.packet.MqttProperties;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class MqttProtocol implements Protocol {

    private final String host = "test.mosquitto.org";
    private final int port = 1883;

    private final ExecutorService executorService = Executors.newSingleThreadExecutor();

    private final MutableSharedFlow<ByteArray> defaultFlow = new MutableSharedFlow<>(1);
    private final MutableMap<Pair<String, String>, String> registeredTopics = new HashMap<>();
    private final MutableMap<String, MutableSharedFlow<ByteArray>> topicChannels = new HashMap<>();

    private MqttAsyncClient mqttClient;

    @Override
    public Flow<ByteArray> readFromChannel(String from, String to) {
        String candidateTopic = registeredTopics.get(new Pair<>(from, to));
        MutableSharedFlow<ByteArray> channel = topicChannels.get(candidateTopic);
        return channel != null ? channel.asSharedFlow() : defaultFlow.asSharedFlow();
    }

    @Override
    public void setupChannel(String source, String destination) {
        registeredTopics.put(new Pair<>(source, destination), toTopics(source, destination));
        registeredTopics.put(new Pair<>(destination, source), toTopics(destination, source));
        topicChannels.put(toTopics(source, destination), new MutableSharedFlow<>(1));
        topicChannels.put(toTopics(destination, source), new MutableSharedFlow<>(1));
    }

    @Override
    public void writeToChannel(String from, String to, byte[] message) {
        String topic = registeredTopics.get(new Pair<>(from, to));

        if (topic == null) {
            throw new ProtocolError.StringNotRegistered(to);
        }

        MqttMessage mqttMessage = new MqttMessage(message);
        mqttMessage.setQos(2);

        executorService.submit(() -> {
            try {
                IMqttToken token = mqttClient.publish(topic, mqttMessage);
                token.waitForCompletion();
            } catch (MqttException e) {
                throw new ProtocolError.ProtocolException(e);
            }
        });
    }

    public void initialize() {
        try {
            mqttClient = new MqttAsyncClient("tcp://" + host + ":" + port, "MqttProtocol Test", new MemoryPersistence());

            Future<?> result = executorService.submit(() -> {
                try {
                    IMqttToken token = mqttClient.connect(createConnectionOptions());
                    token.waitForCompletion();

                    MqttCallback callback = new MqttCallback() {
                        @Override
                        public void messageArrived(String topic, MqttMessage message) {
                            byte[] payload = message.getPayload();
                            requireNotNull(payload, "Message cannot be null");
                            topicChannels.get(topic).tryEmit(payload);
                        }
                    };

                    mqttClient.setCallback(callback);
                    mqttClient.subscribe(new String[]{"RiverMonitoring/+/+"}, new int[]{1}).waitForCompletion();
                } catch (MqttException e) {
                    throw new ProtocolError.ProtocolException(e);
                }
            });

            result.get(); // Wait for initialization to complete

        } catch (Exception e) {
            throw new ProtocolError.ProtocolException(e);
        }
    }

    public void finalize() {
        try {
            mqttClient.disconnect();
            mqttClient.close();
            executorService.shutdownNow();

        } catch (MqttException e) {
            throw new ProtocolError.ProtocolException(e);
        }
    }

    private String toTopics(String source, String destination) {
        if (source.getId() != null && destination.getId() != null) {
            return "RiverMonitoring/" + source.getStringName() + "/" + destination.getStringName();
        } else {
            return "RiverMonitoring/" + source.getStringName() + "/" + destination.getStringName();
        }
    }

    private MqttConnectionOptions createConnectionOptions() {
        MqttConnectionOptions options = new MqttConnectionOptions();
        options.setCleanStart(false);
        return options;
    }

    private static <T> T requireNotNull(T value, String message) {
        if (value == null) {
            throw new IllegalArgumentException(message);
        }
        return value;
    }
}