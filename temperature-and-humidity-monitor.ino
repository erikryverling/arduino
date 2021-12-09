#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

DHT dht(7, DHT11);
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHT11 init"));

  dht.begin();

  Serial.println(F("LCD init"));

  lcd.init();
  lcd.backlight();
}

void loop() {
  // Update ever 2 second
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  lcd.setCursor(0, 0);

  // Same length as the LCD characters
  char buffer[16];
  
  sprintf(buffer, "TEMP: %d C", round(temperature));
  lcd.print(buffer);
 
  lcd.setCursor(0, 1);

  sprintf(buffer, "HMD:  %d %%", round(humidity));
  lcd.print(buffer);
}
