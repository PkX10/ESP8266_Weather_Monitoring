#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

// OLED Display Settings
#define LED_PIN 2
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT Sensor Settings
#define DHTPIN D5          // GPIO14 on ESP8266
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Wi-Fi and ThingSpeak settings
const char* ssid = "Your_WiFi_SSID";            // Enter your Wi-Fi SSID
const char* password = "WiFi_password";    // Enter your Wi-Fi Password
unsigned long myChannelNumber = "ThinkSpeak_ID";    // Enter your ThingSpeak channel number
const char * myWriteAPIKey = "ThinkSpeak_Write_API_key";

WiFiClient client;

// Timing variables
unsigned long previousMillisOLED = 0;
unsigned long previousMillisThingSpeak = 0;

void setup() {
    Serial.begin(115200);
    dht.begin();

    // Setup OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Try address 0x3C
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
    display.display();

    // Setup Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");

    // Initialize ThingSpeak
    ThingSpeak.begin(client);
    // Blink on board LED
    pinMode(LED_PIN, OUTPUT);

}

void loop() {
    unsigned long currentMillis = millis();

    // Update OLED Display every 2 seconds
    if (currentMillis - previousMillisOLED >= 2000) {
        previousMillisOLED = currentMillis;

        float temp = dht.readTemperature();
        float hum = dht.readHumidity();

        // Check if reading is valid
        if (isnan(temp) || isnan(hum)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
        }

        // Display on OLED
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print("Temp: ");
        display.setCursor(0, 16);
        display.print(temp);
        display.setCursor(28, 16);
        display.println(" C");
        display.setCursor(60, 0);
        display.print("Humidity: ");
        display.setCursor(60, 16);
        display.print(hum);
        display.setCursor(94, 16);
        display.println(" %");
        display.display();
    }

    // Update ThingSpeak every 30 seconds
    if (currentMillis - previousMillisThingSpeak >= 1800000) {  // 1800000 ms = 30 minutes
        previousMillisThingSpeak = currentMillis;

        float temp = dht.readTemperature();
        float hum = dht.readHumidity();

        // Write data to ThingSpeak
        ThingSpeak.setField(1, temp);
        ThingSpeak.setField(2, hum);
        int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
        if (x == 200) {
            Serial.println("Channel update successful.");
        } else {
            Serial.println("Problem updating channel. HTTP error code " + String(x));
        }
    }
  // Turn the LED on
  digitalWrite(LED_PIN, LOW);  // LOW turns the LED on (inverted logic)
  delay(50);                 // Wait for 1 second

  // Turn the LED off
  digitalWrite(LED_PIN, HIGH); // HIGH turns the LED off
  delay(1950);
}
