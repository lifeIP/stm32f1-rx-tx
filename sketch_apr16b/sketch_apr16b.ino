#include <SoftwareSerial.h>
#include <stdio.h>

SoftwareSerial mySerial(PA3, PA2); // RX, TX

#define A PB10
#define B PB11
#define C PB6
#define D PB7
#define E PB8
#define F PB1
#define G PB0
#define R_in PA7

void setup() {
  Serial.begin(9600);
  mySerial.begin(4000);
  
  pinMode (A, OUTPUT);
  pinMode (B, OUTPUT);
  pinMode (C, OUTPUT);
  pinMode (D, OUTPUT);
  pinMode (E, OUTPUT);
  pinMode (F, OUTPUT);
  pinMode (G, OUTPUT);

  pinMode (R_in, INPUT);
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

void sendINFO(digits data);

void sendINFO(digits data){
  mySerial.write((byte*)&data, sizeof(data));
  delay(20);
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
  
  digits data;
  data.range = 0;
  data.num = 0;
  
  while(1){
    for(int is = 0; is < 10; is++){
      float val = analogRead(R_in);
      data.range = val / 4;
      int i = val * 4 / float(4097 / 10);
      
      if(i > 9){      
        data.num = 9;
      }
      else data.num = i;
      
      numpad(numbers[data.num]);
      sendINFO(data);
      i--;
    }
  }
}
