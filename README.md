# ESP8266 IoT Temperature and Humidity Monitoring System

This project monitors temperature and humidity using a DHT11 sensor connected to an ESP8266 microcontroller. The ESP8266 reads data from the sensor, stores the values, and serves at ThinkSpeak cloud web page that dynamically displays the readings in a real-time graph, updated every 30 minute (variable). This graph is accessible from any device by logging in to ThinkSpeak from anywhere.

## Table of Contents
- [Features](#features)
- [Components Needed](#components-needed)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [License](#license)

## Features
- **Real-time Temperature and Humidity Monitoring**: Captures and displays temperature (in °C) and humidity (%) data.
- **Graphical Representation**: Data is plotted on a graph in a web interface, updating every 30 minutes.
- **ThingSpeak Integration**: Data is updated to the ThingSpeak cloud every 30 minutes for remote monitoring and visualization.
- **OLED Display**: Displays real-time temperature and humidity readings locally on a 0.91-inch OLED screen, refreshing every 2 seconds.

## Components Needed
- **ESP8266 NodeMCU**
- **DHT11 Temperature and Humidity Sensor**
- **0.91 inch OLED display for real-time monitoring**
- **Jumper Wires**
- **MicroUSB data Cable** (for programming and powering the ESP8266)

![image_alt](https://github.com/PkX10/ESP8266_Weather_Monitoring/blob/695bf12dbb625be64b2dc16224410b97356cf430/IMG_20241026_131232.jpg)


## Circuit Diagram
1. Connect **DHT11 data pin** to **GPIO2** on the ESP8266 (D4).
2. Connect the **VCC** pin of the DHT11 to **3.3V** on the ESP8266.
3. Connect the **GND** pin of the DHT11 to **GND** on the ESP8266.
4. Connect **VCC** of OLED to **3.3V** on ESP8266.
5. Connect **GND** of OLED to **GND** on ESP8266.
6. Connect **SCL** of OLED to **D1 (GPIO 5)** on ESP8266.
7. Connect **SDA** of OLED to **D2 (GPIO 4)** on ESP8266.

## Installation
1. **Clone or Download** this repository:
    ```bash
    git clone https://github.com/PkX10/ESP8266_Weather_Monitoring.git
    ```

2. **Open** the project in the Arduino IDE.

3. **Install Required Libraries**:
   - [ESP8266WiFi Library](https://github.com/esp8266/Arduino) (for Wi-Fi communication)
   - [Adafruit Unified Sensor Library](https://github.com/adafruit/Adafruit_Sensor) (for DHT sensor support)
   - [DHT Sensor Library by Adafruit](https://github.com/adafruit/DHT-sensor-library) (for reading temperature and humidity)
   - [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306) (for the OLED display)
   - [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library) (for graphics support on OLED)
   - [ThingSpeak Library](https://github.com/mathworks/thingspeak-arduino) (for updating data on the ThingSpeak cloud)

5. **Enter WiFi Credentials**:
   - Open the code file and update the `ssid` and `password` variables with your Wi-Fi credentials:
     ```cpp
     const char* ssid = "Your_SSID";
     const char* password = "Your_PASSWORD";
     ```

6. **Upload** the code to your ESP8266.

## Usage
1. Once uploaded, the ESP8266 connects to Wi-Fi and displays "WiFi connected" in the Serial Monitor. Once data sending started it displays "Channel update successful".
2. **Access the ThinkSpeak Web Interface**:
   - Open a web browser on any device connected to internet (Same network is not necessary).
   - Login to your ThinkSpeak ID.
   - Navigate to the channel and goto Private View to see the Temperature & Humidity charts.
3. **Data Update**:
   - The graph updates every 30 Minutes with the latest readings.
   - Update time can be modified by changing the value in milliseconds in the code -
     ```cpp
        if (currentMillis - previousMillisThingSpeak >= <Enter_time_in_milliseconds>) {
        previousMillisThingSpeak = currentMillis;
     ```

## Project Structure
- **/src**: Contains the source code, including the main `.ino` file.
- **/README.md**: Project documentation.

## How It Works
1. **ESP8266 Initialization**:
   - Connects to Wi-Fi using the provided SSID and password.
   - Initializes the DHT11 sensor and sets up a web server on port 80.

2. **Data Collection**:
   - Every 2 seconds, the ESP8266 reads temperature and humidity from the DHT11 sensor and sends the data after every 30 minutes.
   - The readings are stored in arrays (`tempData` and `humData`) of the last 50 entries, creating a rotating buffer of recent data.

3. **ThingSpeak Server and Data Display**:
   - Data is sent to the ThingSpeak cloud, where it is stored and visualized.
   - ThingSpeak's built-in tools allow for dynamic graphs to display the latest temperature and humidity readings.
   - Graphs update every 30 minutes, providing a real-time view of environmental conditions.

4. **ThingSpeak Visualization**:
   - ThingSpeak's platform generates charts for temperature and humidity data.
   - The graphs are color-coded and show historical trends for easy analysis.
   - Users can access the data remotely by logging into their ThingSpeak account and viewing the channel.


## License
This project is open-source and available under the [MIT License](https://opensource.org/licenses/MIT).
