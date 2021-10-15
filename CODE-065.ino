//#VTM https://www.youtube.com/c/VTMVlogVoThongMinh
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
const int stepPin = 11;//clk+
const int dirPin = 12;//cw+
#define start 9
#define stopp 10
#define relay 13
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(start, INPUT_PULLUP);
  pinMode(stopp, INPUT_PULLUP);
  digitalWrite(relay, LOW);
}
//...........................................................................
void loop() {
set:
  long bb = analogRead(A0);
  long aa = analogRead(A1);
  long cc = analogRead(A2);
  double b = map(bb, 0, 1023, 1, 50);//speed
  long a = map(aa, 0, 1023, 1, 10);//distance
  double c = map(cc, 0, 1023, 2, 15);//delay
  //Serial.println(bb);
  //lcd.clear();
  //..........................................................................
  lcd.setCursor(0, 0);
  lcd.print("Speed:");
  lcd.setCursor(10, 0);
  lcd.print(b / 10);
  lcd.setCursor(15, 0);
  lcd.print("(v/s)");

  lcd.setCursor(0, 1);
  lcd.print("Interval:");
  lcd.setCursor(10, 1);
  lcd.print(a * 10);
  lcd.setCursor(15, 1);
  lcd.print("(mm)");

  lcd.setCursor(0, 2);
  lcd.print("Timer:");
  lcd.setCursor(10, 2);
  lcd.print(c / 10);
  lcd.setCursor(15, 2);
  lcd.print("(s)");

  lcd.setCursor(0, 3);
  lcd.print("");
  lcd.setCursor(10, 3);
  lcd.print("");
  lcd.setCursor(0, 3);
  lcd.print("                    ");

  //..............................................................................
  if (a < 10)
  {
    lcd.setCursor(12, 1);
    lcd.print(" ");
  }
  if (a < 1)
  {
    lcd.setCursor(11, 1);
    lcd.print(" ");
  }
  //......................................................................
  if (digitalRead(start) == 0)
  {
    lcd.setCursor(0, 3);
    lcd.print("--------START-------");
    while (1)
    {
      Serial.println("ON");
      digitalWrite(dirPin, HIGH);
      for (int x = 0; x < a * 1952 ; x++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(3125 / b);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(3125 / b);
        if (digitalRead(stopp) == 0)
        {
          Serial.println("stop");
          lcd.setCursor(0, 3);
          lcd.print("                    ");
          goto set;
        }
      }
      digitalWrite(relay, HIGH);
      delay(c * 100);
      digitalWrite(relay, LOW);
      if (digitalRead(stopp) == 0)
      {
        Serial.println("stop");
        lcd.setCursor(0, 3);
        lcd.print("--------STOP--------");
        goto set;
      }
    }
  }
}
