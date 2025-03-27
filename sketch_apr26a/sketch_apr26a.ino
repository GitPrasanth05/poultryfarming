#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "FirebaseESP8266.h"

const char *ssid = "oneplus11r";
const char *password = "12345678";  

const char *FIREBASE_AUTH= "AIzaSyCEIIZYTV-hSUG0rc3LlOWWrCjjibOguUQ"; 
const char *FIREBASE_HOST= "https://ammonia-detection-default-rtdb.asia-southeast1.firebasedatabase.app/"; 
const char *WIFI_SSID= "SECE-TRAINING"; 
const char *WIFI_PASSWORD= "sece@123"; 

const int ammoniaPin = A0;
const int ammoniaLedPinLow = D4; 
const int ammoniaLedPinHigh = D3;

const int relay1Pin = D5;
const int relay2Pin = D6;


WiFiClient client;
FirebaseData firebaseData;

#define LCD_ADDRESS 0x27

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void setup() {
  Serial.begin(115200);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  connectToWiFi();
  ThingSpeak.begin(client);

  pinMode(ammoniaLedPinLow, OUTPUT);
  pinMode(ammoniaLedPinHigh, OUTPUT);
  pinMode(relay1Pin, OUTPUT);
  pinMode(relay2Pin, OUTPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {

  int ammoniaValue = analogRead(ammoniaPin);
  float ammoniaConcentration = map(ammoniaValue, 0, 1023, 0, 100);

  Serial.println("Ammonia Concentration: " + String(ammoniaConcentration) + " ppm");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ammonia: ");
  lcd.print(ammoniaConcentration);
  lcd.print(" ppm");

  bool ledState = digitalRead(ammoniaLedPinLow);
  lcd.setCursor(0, 1);
  lcd.print("LED: ");
  lcd.print(ledState ? "ON " : "OFF");

  if (ammoniaConcentration > 20) {
    digitalWrite(ammoniaLedPinLow, HIGH);
    digitalWrite(ammoniaLedPinHigh, LOW);
  } else {
    digitalWrite(ammoniaLedPinLow, LOW);
    digitalWrite(ammoniaLedPinHigh, HIGH);
  }
  Firebase.setString(firebaseData, "/ammoniaValues/value", ammoniaConcentration);

  if (ammoniaConcentration > 20) {
    Serial.println("Ammonia concentration exceeds 23 ppm. Enabling relay 1...");
    digitalWrite(relay1Pin, LOW); 
    delay(1000);  
    Serial.println("60 seconds delay completed. Enabling relay 2...");
    digitalWrite(relay2Pin, LOW); 
  } else {
    Serial.println("Ammonia concentration below 23 ppm. Disabling relays...");
    digitalWrite(relay1Pin, HIGH); 
    digitalWrite(relay2Pin, HIGH); 
  }
  delay(3000);
}

void connectToWiFi() {
  WiFi.begin(ssid, password);

  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to WiFi. Please check your credentials.");
  }
}