package pc.carwash;

import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.util.Timer;
import java.util.TimerTask;

public class SmartCarWash extends Application {


    private final Logic logic = new LogicImpl();
    private final Label washLabel = new Label();
    private final Label tempLabel = new Label();
    private final Label stateLabel = new Label();
    private final Button maintenenceDone = new Button("Maintenance done");

    public SmartCarWash() throws Exception {
    }

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) throws InterruptedException {
        primaryStage.requestFocus();
        primaryStage.setTitle("Car Washing Dashboard");
        //primaryStage.setFullScreen(true);
        logic.update();

        // Labels
        update();

        // Buttons

        maintenenceDone.setOnAction(e -> logic.maintenenceDone());
        maintenenceDone.setDisable( true );

        // Layout
        VBox layout = new VBox(10);
        layout.setAlignment(Pos.CENTER);
        layout.getChildren().addAll(washLabel, tempLabel, stateLabel, maintenenceDone);

        Scene scene = new Scene(layout, 300, 200);
        primaryStage.setScene(scene);
        primaryStage.show();

        Timer timer = new Timer();
        timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                update();
            }
        }, 1000, 1000);
    }

    private void update() {
        try {
            logic.update();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        CarWasherState state = logic.getState();
        String stateText;

        if( state == CarWasherState.MAINTENANCE){
            stateText = state.toString();
            stateLabel.setUnderline( true );
            maintenenceDone.setDisable( false );
        }else{
            stateText = "State: " + state;
            if(stateLabel.isUnderline()) {
                stateLabel.setUnderline( false );
                maintenenceDone.setDisable( true );
            }
        }

        Platform.runLater(() -> {
            stateLabel.setText(stateText);
            washLabel.setText("Total Washes: " + logic.getWashes());
            tempLabel.setText("Current Temperature: " + logic.getTemperature() + "°C");
        });
    }

}
