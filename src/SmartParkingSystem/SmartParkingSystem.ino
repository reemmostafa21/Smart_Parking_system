// LCD libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo motor library
#include <Servo.h>
Servo myservo;

// Pin definitions
int IR1 = 2;  // IR sensor for entrance gate
int IR2 = 3;  // IR sensor for exit gate

int Slot = 4;  // Initial number of available parking slots

int flag1 = 0;  // Entrance gate flag
int flag2 = 0;  // Exit gate flag

#define buzzer 13
#define led 7

void setup() {
  // Configure inputs
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);

  // Initialize serial communication and LCD
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  // Initialize servo with the gate in the closed position
  myservo.attach(4);
  myservo.write(142);

  // Startup message
  lcd.setCursor(0, 0);
  lcd.print("     ARDUINO    ");

  lcd.setCursor(0, 1);
  lcd.print(" PARKING SYSTEM ");

  delay(2000);
  lcd.clear();

  // Buzzer and LED pin configuration
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  // Case 1: Vehicle detected at the entrance
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) {
      flag1 = 1;
      if (flag2 == 0) {
        myservo.write(47);
        Slot = Slot - 1;
      }
    } else {
      lcd.setCursor(0, 0);
      lcd.print("    SORRY :(    ");
      lcd.setCursor(0, 1);
      lcd.print("  Parking Full  ");
      delay(3000);
      lcd.clear();
    }

    // LED activation code was commented out in the supplied sketch.
    // digitalWrite(led, HIGH);
    // delay(500);
    // digitalWrite(led, LOW);
  }

  // Case 2: Vehicle detected at the exit
  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1;
    if (flag1 == 0) {
      myservo.write(47);
      Slot = Slot + 1;
    }
  }

  // Case 3: Close the gate after an entry or exit event
  if (flag1 == 1 || flag2 == 1) {
    delay(1000);
    myservo.write(142);
    flag1 = 0;
    flag2 = 0;
  }

  // Display the current parking status
  lcd.setCursor(0, 0);
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);

  // Alert when the slot counter exceeds the configured capacity
  if (Slot > 4) {
    tone(buzzer, 1480, 200);
    delay(370);
    noTone(buzzer);
  }
}
