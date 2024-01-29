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
    implementation("org.eclipse.paho:org.eclipse.paho.mqttv5.client:1.2.5")
}

tasks.test {
    useJUnitPlatform()
}