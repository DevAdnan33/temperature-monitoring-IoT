#include <DHT.h>
#include <SoftwareSerial.h>

#define DHTPIN 2          // DHT11 data pin
#define DHTTYPE DHT11
#define LEDPIN 8          // LED indicator pin
#define TEMP_THRESHOLD 30 // Threshold temperature in Celsius

DHT dht(DHTPIN, DHTTYPE);

// Use pins 10 (TX) and 11 (RX) for SoftwareSerial to ESP8266
SoftwareSerial esp8266(10, 11);

void setup() {
  Serial.begin(9600);
  esp8266.begin(9600); // ESP8266 default baud rate
  dht.begin();
  pinMode(LEDPIN, OUTPUT);

  Serial.println("System started");
}

void loop() {
  delay(2000); // Delay between sensor reads

  float temp = dht.readTemperature(); // Celsius

  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  // For the degree symbol, it's better to use (char)248 for wider terminal compatibility
  // or simply " deg C" if UTF-8 display is inconsistent.
  // The "Â°C" often results from a UTF-8 degree symbol being misinterpreted.
  // If your serial monitor correctly displays UTF-8, then "°C" is fine.
  // Serial.println(" Â°C"); // Original
  Serial.print(" ");
  Serial.write(248); // Degree symbol in many extended ASCII sets
  Serial.println("C");


  // Send data to ESP8266 (e.g., to local server or just monitor)
  esp8266.print("Temperature: ");
  esp8266.print(temp);
  // esp8266.println(" Â°C"); // Original
  esp8266.print(" ");
  esp8266.write(248); // Degree symbol
  esp8266.println("C");


  // LED Control
  if (temp > TEMP_THRESHOLD) {
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  } // Cleaned this line - ensure only regular spaces or tabs are here
}