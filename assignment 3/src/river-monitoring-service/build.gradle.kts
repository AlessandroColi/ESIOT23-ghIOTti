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
}

tasks.test {
    useJUnitPlatform()
}