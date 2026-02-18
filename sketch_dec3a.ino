#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const bool USE_LCD = true;
const int SERIAL_SPEED = 9600;


const int spoilagePin = A0; 
const int fatPin = A1;
const int ledSourcePin = 7;
const int alarmPin = 13; 


const int SPOILAGE_LIMIT = 700;  
const int MILK_MIN_LIMIT = 600;   
const int WATER_MIN_LIMIT = 100;  


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
    lcd.print("Ready...");
    delay(2000);
  }
}

void loop() {
  int conductivity = analogRead(spoilagePin);
  int lightLevel = analogRead(fatPin);
  
  if (USE_LCD) lcd.clear();


  if (conductivity > SPOILAGE_LIMIT) {
    Serial.println("Status: SPOILED!");
    digitalWrite(alarmPin, HIGH); // Alarm ON
    
    if (USE_LCD) {
      lcd.setCursor(0, 0);
      lcd.print("WARNING:");
      lcd.setCursor(0, 1);
      lcd.print("SPOILED MILK!");
    }
  }

  
  else if (conductivity >= MILK_MIN_LIMIT) {
    digitalWrite(alarmPin, LOW);
    
    
    int fatPercent = map(lightLevel, WATER_LIGHT_VAL, CREAM_LIGHT_VAL, 0, 10);
    fatPercent = constrain(fatPercent, 0, 10);
    
    Serial.print("Status: Good Milk | Fat: "); Serial.println(fatPercent);

    if (USE_LCD) {
      lcd.setCursor(0, 0);
      lcd.print("Fat: ");
      lcd.print(fatPercent);
      lcd.print("%");
      
      lcd.setCursor(0, 1);
      lcd.print("Good Milk");
    }
  }

  
  else if (conductivity >= WATER_MIN_LIMIT) {
    Serial.println("Status: Water Detected");
    digitalWrite(alarmPin, LOW);
    
    if (USE_LCD) {
      lcd.setCursor(0, 0);
      lcd.print("Water Detected");
      lcd.setCursor(0, 1);
      lcd.print("Not Milk");
    }
  }

  
  else {
    Serial.println("Status: Empty");
    digitalWrite(alarmPin, LOW);
    
    if (USE_LCD) {
      lcd.setCursor(0, 0);
      lcd.print("Add Milk Sample");
      lcd.setCursor(0, 1);
      lcd.print("Container Empty");
    }
  }

  delay(1000);
}