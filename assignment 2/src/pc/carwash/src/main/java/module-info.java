module pc.carwash.carwash {
    requires javafx.controls;
    requires javafx.fxml;
    requires jssc;
    requires java.desktop;


    opens pc.carwash to javafx.fxml;
    exports pc.carwash;
}