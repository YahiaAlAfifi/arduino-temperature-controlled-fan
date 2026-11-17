#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Pin assignments
#define TMP_PIN A1
#define RELAY_PIN 9
#define RED_LED 7
#define GREEN_LED 6

// Temperature threshold in degrees Celsius.
const float TEMP_THRESHOLD = 25.0f;

void setup() {
  Serial.begin(9600);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("ERROR: SSD1306 allocation failed"));
    while (true) {
      // Halt safely when the display is unavailable.
    }
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.print("TEMP CTRL");
  display.display();
  delay(1000);
}

void loop() {
  const int rawAdc = analogRead(TMP_PIN);
  const float voltage = rawAdc * (5.0f / 1023.0f);
  const float temperatureC = (voltage - 0.5f) * 100.0f;
  const bool fanOn = temperatureC >= TEMP_THRESHOLD;

  digitalWrite(RELAY_PIN, fanOn ? HIGH : LOW);
  digitalWrite(RED_LED, fanOn ? HIGH : LOW);
  digitalWrite(GREEN_LED, fanOn ? LOW : HIGH);

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.print("TEMP CTRL");

  display.setTextSize(1);
  display.setCursor(0, 32);
  display.print("T: ");
  display.print(temperatureC, 1);
  display.write(248);
  display.print("C");

  display.setCursor(80, 32);
  display.print(fanOn ? "FAN ON" : "FAN OFF");
  display.display();

  Serial.print("Temp: ");
  Serial.print(temperatureC, 1);
  Serial.print(" C | Fan: ");
  Serial.println(fanOn ? "ON" : "OFF");

  delay(500);
}
