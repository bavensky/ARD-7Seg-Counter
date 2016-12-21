#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

#define LATCH 12    // ST_CP
#define CLOCK 13    // SH_CP
#define DATA  11    // DS
#define BUTTON1 10  // count 5 minute
#define BUTTON2 9   // count 10 minute
#define BUTTON3 8   // count 15 minute

int num1[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
int num2[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
int num3[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };
int num4[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F };

int digit1, digit2, digit3, digit4, coundown = 0;

void setup() {
  Serial.begin(115200);
  rtc.begin();

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);

  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  digitalWrite(LATCH, HIGH);

  digit1 = 8;
  digit2 = 8;
  digit3 = 8;
  digit4 = 8;
  delay(2000);

  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();
  Serial.print("Time = ");
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print('.');
  Serial.print(now.second());
  Serial.print("    ");
  Serial.print(digit1);
  Serial.print(digit2);
  Serial.print(":");
  Serial.print(digit3);
  Serial.print(digit4);
  Serial.print("    ");
  Serial.print(digitalRead(BUTTON1));
  Serial.print(digitalRead(BUTTON2)); 
  Serial.println(digitalRead(BUTTON3));

  digit1 = (now.minute() % 100) / 10;
  digit2 = now.minute() % 10;
  digit3 = (now.second() % 100) / 10;
  digit4 = now.second() % 10;
  DataOut(num1[digit1], num2[digit2], num3[digit3], num4[digit4]);

  delay(200);
}

void DataOut(byte data1, byte data2, byte data3, byte data4) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, data1);
  shiftOut(DATA, CLOCK, MSBFIRST, data2);
  shiftOut(DATA, CLOCK, MSBFIRST, data3);
  shiftOut(DATA, CLOCK, MSBFIRST, data4);
  digitalWrite(LATCH, HIGH);
}
