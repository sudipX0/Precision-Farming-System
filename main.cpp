#include <LiquidCrystal.h>

const int LM35 = A0;                    // Temperature sensor pin
const int soilMoistureSensor = A1;     // Soil moisture sensor pin
const int photoresistorPin = A2;       // Photoresistor pin
const int motor = 13;                   // Water pump control pin
const int LedRed = 12;                  // Red LED pin
const int LedGreen = 11;                // Green LED pin

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);                   // Initialize serial communication
  lcd.begin(16, 2);
  lcd.print("Precision");
  lcd.setCursor(0, 1);
  lcd.print("Farming System!");
  pinMode(motor, OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  delay(2000);
  lcd.clear();
}

void loop() {
  // Read temperature from LM35
  int value = analogRead(LM35);
  float Temperature = value * 500.0 / 1023.0;

  // Read soil moisture
  int moistureValue = analogRead(soilMoistureSensor);
  int moisturePercentage = map(moistureValue, 0, 1023, 0, 100); // Convert to percentage

  // Read light value from photoresistor
  int lightValue = analogRead(photoresistorPin);

  // Clear the LCD before displaying new data
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(Temperature);
  lcd.print("C  "); // Extra spaces to clear previous data

  lcd.setCursor(0, 1);
  lcd.print("Moist: ");
  lcd.print(moisturePercentage);
  lcd.print("%  "); // Extra spaces to clear previous data

  // Control the water pump based on temperature and soil moisture
  bool pumpStatus = (Temperature > 50 || moisturePercentage < 30); // Determine pump status
  if (pumpStatus) { // Pump ON if either condition is true
    digitalWrite(motor, HIGH);
    digitalWrite(LedRed, HIGH);
    digitalWrite(LedGreen, LOW);
    lcd.setCursor(11, 1);
    lcd.print("P-ON ");
  } else { // Pump OFF if both conditions are false
    digitalWrite(motor, LOW);
    digitalWrite(LedRed, LOW);
    digitalWrite(LedGreen, HIGH);
    lcd.setCursor(11, 1);
    lcd.print("P-OFF");
  }

  // Display values in Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(Temperature);
  Serial.print("C, Soil Moisture: ");
  Serial.print(moisturePercentage);
  Serial.print("%, Light Value: ");
  Serial.print(lightValue); // Print light value to Serial Monitor
  Serial.print(", Pump Status: ");
  Serial.println(pumpStatus ? "ON" : "OFF"); // Print pump status

  delay(1000); // Wait for 1 second before the next loop
}
