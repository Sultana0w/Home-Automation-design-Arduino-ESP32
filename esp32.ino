#include <DHT.h>       // Include the DHT library for DHT sensor


#define fanPin 5          // PWM-capable pin for controlling the fan
#define dhtPin 4          // Digital pin DHT sensor is connected to ESP32
#define irPin 13          // Digital pin IR sensor is connected to ESP32
#define ldrPin 2          // Analog pin LDR sensor connected to ESP32
#define ledPin 18         // Digital pin LED connected
#define FAN_THRESHOLD 20  // Temperature threshold to turn on the fan (adjust as needed)
#define LIGHT_THRESHOLD 620 // Threshold value for LDR sensor

#define DHTTYPE DHT11   // DHT type is DHT11

DHT dht(dhtPin, DHTTYPE); // Initialize DHT sensor

void setup() {
  
  Serial.begin(9600);
  dht.begin();               // Initialize DHT sensor
  pinMode(irPin, INPUT);     // Set IR pin as input
  pinMode(ldrPin, INPUT);    // Set LDR pin as input
  pinMode(fanPin, OUTPUT);   // Set Fan Pin as output
  pinMode(ledPin, OUTPUT);   // Set LED pin as output

  
}

void loop() {
  int irValue = digitalRead(irPin);       // Read IR sensor
  int lightValue = analogRead(ldrPin);    // Read LDR sensor

  int temperature = dht.readTemperature(); // Read temperature from DHT sensor
  int humidity = dht.readHumidity();       // Read humidity from DHT sensor

  Serial.print("Current humidity = ");
  Serial.print(humidity);
  Serial.print("%  ");
  Serial.print("temperature = ");
  Serial.print(temperature);
  Serial.println(" C ");
  Serial.print("Light intensity:");
  Serial.println(lightValue);

  if (irValue == LOW) {
    // IR sensor detects motion
    if (temperature > FAN_THRESHOLD && lightValue < LIGHT_THRESHOLD) {
      // Both conditions are met, turn on fan and LED
      digitalWrite(fanPin, HIGH);
      digitalWrite(ledPin, HIGH);
      Serial.println("Motion detected! Temperature above threshold! Fan turned on!\nLight intensity below threshold! LED turned on!");
    } 
    else if (temperature > FAN_THRESHOLD && lightValue > LIGHT_THRESHOLD ) {
      // Only temperature condition is met, turn on fan
      digitalWrite(fanPin, HIGH);
      digitalWrite(ledPin, LOW);
      Serial.println("Motion detected! Temperature above threshold! Fan turned on!\nLight intensity above threshold! LED turned off!");
    } 
      else if (temperature > FAN_THRESHOLD && lightValue > LIGHT_THRESHOLD) {
      // Only light intensity condition is met, turn on LED
      digitalWrite(ledPin, LOW);
      digitalWrite(fanPin, LOW);
      Serial.println("Motion detected! Temperature above threshold! Fan turned off!\nLight intensity below threshold! LED turned off!");
    } 
      else if (temperature < FAN_THRESHOLD && lightValue > LIGHT_THRESHOLD) {
      // Only light intensity condition is met, turn on LED
      digitalWrite(ledPin, LOW);
      digitalWrite(fanPin, LOW);
      Serial.println("Motion detected! Temperature below threshold! Fan turned off!\nLight intensity below threshold! LED turned off!");
    } 
   
  } else {
    // IR sensor does not detect motion, turn off fan and LED
    digitalWrite(fanPin, LOW);
    digitalWrite(ledPin, LOW);
    Serial.println("No motion detected! Fan and LED turned off!");
  }

  delay(5000); // Adjust delay as needed
}
