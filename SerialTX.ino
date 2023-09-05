#include <DHT.h>
// #include <SoftwareSerial.h>
// SoftwareSerial serial (D1,D2);

// DHT Sernsor
// #define DHTPIN 3
// #define DHTTYPE DHT11

// Sernsor ultrasonik
const int trig = 2;
const int echo = 3;

long duration;
long distance;

// Joystik
int statusX, statusY;
int pinX = A4, pinY = A3;


const int ldr = A0;
int dataLDR;

const int vSen = A1;
int voltDataRaw;
float voltData;

const int hSen = A7;
int hSenRaw;
int hSenData;

void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  pinMode(ldr, INPUT);
  pinMode(vSen, INPUT);
  pinMode(hSen, INPUT);
}

void loop() {
//   String minta = "";
//   while(Serial.available()>0){
//     minta += char(Serial.read());
//   }

//   // Hapus Spasi
//   minta.trim();

//   // Test variabel minta
//   if(minta == "kirim"){
//     dataKirim(); // Kirim data dari void dataKirim()
//   }

//   // dataKirim(); 
// // Serial.println(minta);

//   minta = "";

  dataKirim(); // Kirim data dari void dataKirim()
  delay(1000);
}  

void dataKirim(){
  statusX = map(analogRead(pinX),0,1024,0,180);
  statusY = map(analogRead(pinY),0,1024,0,180);

  dataLDR=analogRead(ldr);

  voltDataRaw = analogRead(vSen);
  voltData = map(voltDataRaw,0,1023,0,2500);
  voltData = voltData/100;

  hSenRaw = analogRead(hSen);
  hSenData = map(hSenRaw,0,1023,100,0);

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);

  distance = duration*0.0343/2;

  String data = String(distance) + "#" + String(statusX) + "#" + String(statusY) + "#" + String(dataLDR) + "#" + String(voltData) + "#" + String(hSenData); 
  Serial.println(data);
}

