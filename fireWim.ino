#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager

#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "spacex"
#define STAPSK  "azharpasha"
#endif

FirebaseData fbdo;

#define TRIGGER_PIN 0 
bool portalRunning = false;

#define lamp1 5
#define lamp2 4
#define lamp3 0
#define lamp4 2
#define FIREBASE_HOST "https://bbbaa-1503c-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "ptu0YLVr2HOeitbRAaZLkYqvK8PTdabBicnWsMMw"
int timeout = 120;
const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "namas.net";
const uint16_t port = 17;

#define PinDigital 4 // mendefinisikan pin yang digunakan adalah pin Digital
int NilaiDigital;

int aa;

WiFiManager wm;

void setup() {
    pinMode(lamp1,OUTPUT);
  pinMode(lamp2,OUTPUT);
  pinMode(lamp3,OUTPUT);
  pinMode(TRIGGER_PIN, INPUT_PULLUP);
  pinMode(lamp4,OUTPUT);
    // WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    // it is a good practice to make sure your code sets wifi mode how you want it.

    // put your setup code here, to run once:
    Serial.begin(115200);
   
    //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
   

}

void loop() {

    if ( digitalRead(TRIGGER_PIN) == LOW) {
    WiFiManager wm;    
 
    //reset settings - for testing
    //wm.resetSettings();
  
    // set configportal timeout
    wm.setConfigPortalTimeout(timeout);
 
    if (!wm.startConfigPortal("WiFISpaceX")) {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.restart();
      delay(5000);
    }
 
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
   
      
  }
   Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
    jalan();
}

void checkButton(){
  // is auto timeout portal running
  if(portalRunning){
    wm.process();
  }

  // is configuration portal requested?
  if(digitalRead(TRIGGER_PIN) == HIGH) {
    delay(50);
    if(digitalRead(TRIGGER_PIN) == HIGH) {
      if(!portalRunning){
        Serial.println("Button Pressed, Starting Portal");
        wm.startWebPortal();
        portalRunning = true;
      }
      else{
        Serial.println("Button Pressed, Stopping Portal");
        wm.stopWebPortal();
        portalRunning = false;
      }
    }
  }
}

void jalan(){

if(Firebase.getString(fbdo,"/Lamp2/L1")){
  Serial.println(fbdo.dataType());
   String val = fbdo.stringData();
  Serial.println(val);
  Serial.println("\n Change the value at firebase");
  delay(100);
  if(val == "true"){
    digitalWrite(lamp1,1);
    }
  else if(val == "false"){
    digitalWrite(lamp1,0);
    
    }
 delay(2500);
}
}
