#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int motor_pin_A1 = 10;
int motor_pin_A2 = 9;
int motor_pin_B1 = 8;
int motor_pin_B2 = 7;
int motor_pin_PWMA = 6;
int motor_pin_PWMB = 5;
unsigned long previousMillis = 0;
void setup() {
  Serial.begin(9600);
  lcd.begin();
  pinMode(motor_pin_A1, OUTPUT);
  pinMode(motor_pin_A2, OUTPUT);
  pinMode(motor_pin_B1, OUTPUT);
  pinMode(motor_pin_B2, OUTPUT);
  pinMode(motor_pin_PWMA, OUTPUT);
  pinMode(motor_pin_PWMB, OUTPUT);

}

void loop() {
  int sensorValueA = (int)analogRead(A0) - 512;
  int sensorValueB = (int)analogRead(A1) - 512;

  if (sensorValueA > 10) {
    analogWrite(motor_pin_PWMA, (abs(sensorValueA / 2)) - 1);
    digitalWrite(motor_pin_A1, HIGH);
    digitalWrite(motor_pin_A2, LOW);
  } else if (sensorValueA < -10) {
    analogWrite(motor_pin_PWMA, (abs(sensorValueA / 2)) - 1);
    digitalWrite(motor_pin_A1, LOW);
    digitalWrite(motor_pin_A2, HIGH);
  } else {
    analogWrite(motor_pin_PWMA, 0);
    digitalWrite(motor_pin_A1, LOW);
    digitalWrite(motor_pin_A2, LOW);
  }
  ////////////
  if (sensorValueB > 10) {
    analogWrite(motor_pin_PWMB, (abs(sensorValueB / 2)) - 1);
    digitalWrite(motor_pin_B1, HIGH);
    digitalWrite(motor_pin_B2, LOW);
  } else if (sensorValueB < -10) {
    analogWrite(motor_pin_PWMB, (abs(sensorValueB / 2)) - 1);
    digitalWrite(motor_pin_B1, LOW);
    digitalWrite(motor_pin_B2, HIGH);
  } else {
    analogWrite(motor_pin_PWMB, 0);
    digitalWrite(motor_pin_B1, LOW);
    digitalWrite(motor_pin_B2, LOW);
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    float numA = sensorValueA / 5.12f;
    float numB = sensorValueB / 5.12f;
    Serial.print(abs(numA));
    Serial.print(" ");
    Serial.println(abs(numB));
    
    lcd.clear();
    lcd.print("A = ");
    lcd.print(abs(numA));
    lcd.print(" %");
    if (sensorValueA > 10) {
    lcd.print(" ");
    lcd.print("-");
    lcd.print(">");
  } else if (sensorValueA < -10) {
    lcd.print("<");
    lcd.print("-");
    lcd.print(" ");
  } else {
    lcd.print(" ");
    lcd.print("-");
    lcd.print(" ");
  }
    lcd.setCursor(0, 1);
    lcd.print("B = ");
    lcd.print(abs(numB));
    lcd.print(" %");
    if (sensorValueB > 10) {
    lcd.print(" ");
    lcd.print("-");
    lcd.print(">");
  } else if (sensorValueB < -10) {
    lcd.print("<");
    lcd.print("-");
    lcd.print(" ");
  } else {
    lcd.print(" ");
    lcd.print("-");
    lcd.print(" ");
  }
    //delay(1);
  }
}
