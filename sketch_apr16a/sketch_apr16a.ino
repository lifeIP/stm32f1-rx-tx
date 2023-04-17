#include <SoftwareSerial.h>
#include <stdio.h>

SoftwareSerial mySerial(PA3, PA2); // RX, TX

#define A PB11
#define B PB10
#define C PB5
#define D PB6
#define E PB7
#define F PB8
#define G PB12
#define O PA0


void setup() {
  Serial.begin(9600);
  mySerial.begin(4000);

  pinMode (O, OUTPUT);
  pinMode (A, OUTPUT);
  pinMode (B, OUTPUT);
  pinMode (C, OUTPUT);
  pinMode (D, OUTPUT);
  pinMode (E, OUTPUT);
  pinMode (F, OUTPUT);
  pinMode (G, OUTPUT);
}


char numbers[10]{
  252,
  96,
  218,
  242,
  102,
  182,
  190,
  224,
  254,
  246
};


typedef struct {
  int     range; // диапазон от 0 до 65 535
  int     num; // число, которое должно отображаться на семисегдентнике
} digits;

void getINFO(digits& data);

void getINFO(digits& data){
  digits buffer;
  if (!mySerial.readBytes((byte*)&buffer, sizeof(buffer))) {
    return;
  }
  data = buffer;
}

void numpad(char bits){
  digitalWrite(A, bool(bits & 128));
  digitalWrite(B, bool(bits & 64));
  digitalWrite(C, bool(bits & 32));
  digitalWrite(D, bool(bits & 16));
  digitalWrite(E, bool(bits & 8));
  digitalWrite(F, bool(bits & 4));
  digitalWrite(G, bool(bits & 2));
}

void loop() {
  digits buf;
  buf.range = 0;
  buf.num = 0;
  while(1){
    getINFO(buf);
    analogWrite(O, buf.range);
    numpad(numbers[buf.num]);
  }
}
