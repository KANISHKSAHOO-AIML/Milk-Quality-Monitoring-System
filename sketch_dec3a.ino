#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const bool USE_LCD = true;+

const int SERIAL_SPEED = 9600;

const int spoilagePin = A0; 
const int fatPin = A1;
const int ledSourcePin = 7;
const int alarmPin = 13; 
const int SPOILAGE_LIMIT = 700; 
const int WATER_LIGHT_VAL = 850;
const int CREAM_LIGHT_VAL = -600;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.println("--- MILK TEST START ---");
  pinMode(ledSourcePin, OUTPUT);
  digitalWrite(ledSourcePin, HIGH);
  pinMode(alarmPin, OUTPUT);
  if (USE_LCD) {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Milk System");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
    delay(2000);
  }
  Serial.println("System Ready. Reading Sensors...");
  Serial.println("Cond\tLight\tFat%\tStatus");
}
void loop() {
  int conductivity = analogRead(spoilagePin);
  int lightLevel = analogRead(fatPin);
  int fatPercent = map(lightLevel, WATER_LIGHT_VAL, CREAM_LIGHT_VAL, 0, 10);
  fatPercent = constrain(fatPercent, 0, 10); 
  String status = "";
  if (conductivity > SPOILAGE_LIMIT) {
    status = "SPOILED!";
    digitalWrite(alarmPin, HIGH);
  } 
  else if (fatPercent < 3) {
    status = "Skim/Watery";
    digitalWrite(alarmPin, LOW);
  } 
  else {
    status = "Good Milk";
    digitalWrite(alarmPin, LOW);
  }
  Serial.print(conductivity);
  Serial.print("\t");
  Serial.print(lightLevel);
  Serial.print("\t");
  Serial.print(fatPercent);
  Serial.print("%\t");
  Serial.println(status);
  if (USE_LCD) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Fat: ");
    lcd.print(fatPercent);
    lcd.print("%");
    lcd.setCursor(0, 1);
    lcd.print(status);
  }
  delay(1000);
}