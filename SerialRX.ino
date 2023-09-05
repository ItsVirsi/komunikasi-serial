#include <Blynk.h>

#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
// #include <BlynkSimpleEsp8266.h>






// WiFi Credentials
const char* ssid = "Proxima Centauri";
const char* password = "";
String newHostname = "PenkIoT-01";
// #define ledPin D3

// Blynk IoT
#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "IoT Project"
#define BLYNK_AUTH_TOKEN ""

	BlynkTimer timer;

  // #define FB_HOST "myiots-b22dc-default-rtdb.firebaseio.com"
  // #define FB_AUTH "yzonrLOlaPz1bcLpadD7nDjLkSBAVMjszXW9YvxD"

// Blynk IoT end

// SoftwareSerial serial(D1,D2); // RX,TX

String arrData[6]; // 6 adalah jumlah sensor
unsigned long previousMillis = 0;
const long interval = 1000;





void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
// serial.begin(9600);
// pinMode(ledPin, OUTPUT);

wifiSetup();
BlynkSetup();

}

void BlynkSetup(){
   Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
   

  //  Firebase.begin(FB_HOST, FB_AUTH);

}

// void sendSensor(){ //Pengaturan Variabel Sensor dan Virtual Pin
//   
// }

void wifiSetup(){
  /* Wifi Setup Begin */

  WiFi.mode(WIFI_STA);

  //Set new hostname
  WiFi.hostname(newHostname.c_str());
  
  
  //Init Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    // digitalWrite(ledPin, LOW);
    delay(500);
  } 

  // digitalWrite(ledPin, HIGH);

  /* Wifi Setup End */
}

// int n = 0;

void loop() {


  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){
    // Update previousMillis
    previousMillis = currentMillis;

    // Baca data serial
    String dataIn = "";
      while(Serial.available()>0){
        dataIn += char(Serial.read());
      }
  
    dataIn.trim(); //Buang spasi data

    if(dataIn != ""){
      // Parsing data
      int index = 0;
      for(int i=0; i<= dataIn.length(); i++){
        char delimiter = '#';
        if (dataIn[i] != delimiter)
          arrData[index] += dataIn[i];
          else
            index++; //Variabel index ditambah 1
      }

       

      // cek kelengkapan data
      // urutan = 
      if(index == 5){
        // Serial.println("Jarak = " + arrData[0] + "cm");
        // Serial.println("X = " + arrData[1]);
        // Serial.println("Y = " + arrData[2]);
        // Serial.println("LDR = " + arrData[3]);
        // Serial.println("Volt = " + arrData[4]);
        // Serial.println("Hujan = " + arrData[5]);
        // Serial.println();
        
        int dataUS, dataX, dataY, dataLDR, dataVolt, dataHujan;
        // dataUS = arrData[0].toInt();
        // dataX  = arrData[1].toInt();
        // dataY  = arrData[2].toInt();
        dataLDR = arrData[3].toInt();
        dataVolt = arrData[4].toInt();
        dataHujan = arrData[5].toInt();


        // Blynk.virtualWrite(V0, dataUS);
        // Blynk.virtualWrite(V1, dataX);
        // Blynk.virtualWrite(V2, dataY);
        Blynk.virtualWrite(V3, dataHujan);
        Blynk.virtualWrite(V4, dataVolt);
        Blynk.virtualWrite(V5, dataLDR);


      }

      // arrData[0] = "";
      // arrData[1] = "";
      // arrData[2] = "";
      arrData[3] = "";
      arrData[4] = "";
      arrData[5] = "";
    }

    // minta data
        // Serial.println("kirim");

    

    
  }

  
  BlynkLoop();
}

void BlynkLoop(){
  Blynk.run();
  timer.run();

//   // Firebase.setString("number", arrData[0]);
}


