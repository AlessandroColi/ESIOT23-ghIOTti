plugins {
    id("java")
}

group = "org.example"
version = "1.0-SNAPSHOT"

repositories {
    google()
    mavenCentral()
    maven {
        url = uri("https://repo.eclipse.org/content/repositories/paho-releases/")
    }
}

dependencies {
    implementation("org.eclipse.paho:org.eclipse.paho.client.mqttv3:1.2.5")
    implementation("io.github.java-native:jssc:2.9.5")
    implementation("io.vertx:vertx-core:4.2.6")   
    implementation("io.vertx:vertx-web:4.2.6")
    implementation("io.vertx:vertx-web-client:4.2.6")
    implementation("io.vertx:vertx-mqtt:4.2.6")
    implementation("org.slf4j:slf4j-api:1.7.25")
    implementation("org.slf4j:slf4j-jdk14:1.7.36")

}

tasks.test {
    useJUnitPlatform()
}