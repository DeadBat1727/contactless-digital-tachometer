/*
 * Contactless Digital Tachometer Using Microcontroller
 * ----------------------------------------------------
 * Measures the RPM of a rotating object without physical contact,
 * using a TCRT5000 IR sensor and an Arduino Uno, with output on a
 * 16x2 I2C LCD.
 *
 * Working principle: reflective tape on the rotating object reflects
 * IR light once per revolution, generating a pulse on pin D2. A
 * hardware interrupt times the gap between pulses to compute RPM.
 *
 * Course:  EE 3200 - Electrical & Electronic Project Design
 * Author:  Mohammad Tanzid Ahmed (Roll: 2003031), KUET
 * Supervisor: Dr. Md. Shahjahan, Professor, Dept. of EEE, KUET
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sensorPin = 2;  // IR sensor connected to digital pin 2 (INT0)

volatile unsigned long pulseTime = 0;
volatile unsigned long lastPulseTime = 0;
volatile int rpm = 0;

void setup() {
  pinMode(sensorPin, INPUT);

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Digital");
  lcd.setCursor(0, 1);
  lcd.print("Tachometer");

  // Attach an interrupt to the sensor pin.
  // FALLING mode triggers when the pin goes HIGH -> LOW (tape detected).
  attachInterrupt(digitalPinToInterrupt(sensorPin), calculateRPM, FALLING);

  delay(2000);  // Show splash screen
  lcd.clear();
}

void loop() {
  // Display the RPM value calculated by the interrupt routine
  lcd.setCursor(0, 0);
  lcd.print("RPM: ");
  lcd.print(rpm);
  lcd.print("    ");  // Clear any leftover characters

  delay(500);  // Small delay to stabilize the LCD display
}

// Interrupt Service Routine (ISR)
void calculateRPM() {
  pulseTime = millis();  // Get the current time
  if (pulseTime - lastPulseTime > 10) {          // Basic debouncing filter
    rpm = 60000 / (pulseTime - lastPulseTime);   // Calculate RPM
    lastPulseTime = pulseTime;                   // Save for next calculation
  }
}
