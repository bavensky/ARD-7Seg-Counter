#include <CountUpDownTimer.h>
CountUpDownTimer T(DOWN);

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

boolean coundown = false;
int digit1, digit2, digit3, digit4, TimeMinute = 0, TimeSecond = 0;
byte CountMinute = 0, CountSecond = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);

  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(DATA, OUTPUT);
  digitalWrite(LATCH, HIGH);

  for (int i = 10; i > 0; i--) {
    DataOut(num1[i], num2[i], num3[i], num4[i]);
    delay(100);
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  if (digitalRead(BUTTON1) == 0) {
    delay(500);
    Serial.println("1");
    T.SetTimer(0, 5, 0);
    coundown = true;
  }
  
  if (digitalRead(BUTTON2) == 0) {
    delay(500);
    Serial.println("2");
    T.SetTimer(0, 10, 0);
    coundown = true;
  }
  
  if (digitalRead(BUTTON3) == 0) {
    delay(500);
    Serial.println("3");
    T.SetTimer(0, 15, 0);
    coundown = true;
  }

  while (coundown == true) {
    T.StartTimer();
    Timecount();
  }

  DataOut(num1[0], num2[0], num3[0], num4[0]);
//  Serial.println("main");
  delay(100);
}

void DataOut(byte data1, byte data2, byte data3, byte data4) {
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, data1);
  shiftOut(DATA, CLOCK, MSBFIRST, data2);
  shiftOut(DATA, CLOCK, MSBFIRST, data3);
  shiftOut(DATA, CLOCK, MSBFIRST, data4);
  digitalWrite(LATCH, HIGH);
}

void Timecount() {
  T.Timer();
  if (T.ShowMinutes() <= 0 && T.ShowSeconds() <= 0) {
    DataOut(0x00, 0x00, 0x00, 0x00);
    delay(500);
    DataOut(0xFF, 0xFF, 0xFF, 0xFF);
    delay(500);
    DataOut(0x00, 0x00, 0x00, 0x00);
    delay(500);
    DataOut(0xFF, 0xFF, 0xFF, 0xFF);
    delay(500);
    coundown = false;
  }

  if (digitalRead(BUTTON1) == 0 || digitalRead(BUTTON2) == 0 || digitalRead(BUTTON3) == 0) {
    delay(200);
    coundown = false;
  }

//  Serial.print("Count = ");
//  Serial.print(T.ShowMinutes());
//  Serial.print(':');
//  Serial.println(T.ShowSeconds());
  
  digit1 = (T.ShowMinutes() % 100) / 10;
  digit2 = T.ShowMinutes() % 10;
  digit3 = (T.ShowSeconds() % 100) / 10;
  digit4 = T.ShowSeconds() % 10;
  DataOut(num1[digit1], num2[digit2], num3[digit3], num4[digit4]);
//  delay(200);
}
