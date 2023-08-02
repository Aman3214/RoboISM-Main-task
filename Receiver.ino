#include <esp_now.h>
#include <WiFi.h>
#include<math.h>
float Data[6];
int led[5];
int poten,u;
int i= 0; 
unsigned long elapsed_time,start_time,current_time;
//when data is recieved
void OnDataRecv(const uint8_t *mac,const uint8_t *incomingData,int len){
  memcpy(&Data, incomingData, sizeof(Data));
  if(Data[0]==HIGH){
    digitalWrite(led[0],HIGH);
  }
  if(Data[0]==LOW){
    digitalWrite(led[0],LOW);
  }
  if(Data[1]==HIGH){
    digitalWrite(led[1],HIGH);
  }
  if(Data[1]==LOW){
    digitalWrite(led[1],LOW);
  }
  if(Data[2]==HIGH){
    digitalWrite(led[2],HIGH);
  }
  if(Data[2]==LOW){
    digitalWrite(led[2],LOW);
  }
  if(Data[3]==HIGH){
    digitalWrite(led[3],HIGH);
  }
  if(Data[3]==LOW){
    digitalWrite(led[3],LOW);
  }
  // u = 5*Data[4];
  analogWrite(poten,Data[4]);
  Serial.begin(115200);
  for(i=0;i<6;i++){
    Serial.println(Data[i]);
  }
  Serial.println("--------------------");
  // for(i=0;i<6;i++){
  //   Data[i] = 0;
  // }

}
void setup() {
//starting the timer
start_time = millis();
//setting up leds' pins
led[0] = 13;
led[1] = 12; 
led[2] = 14;
led[3] = 27;
led[4] = 26;
poten = 25;
//esp setup
  //setting esp as wifi station
  WiFi.mode(WIFI_STA);
  //initializing esp now
  if(esp_now_init() != ESP_OK){
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  //Register callback function 
  esp_now_register_recv_cb(OnDataRecv);
  //setting up LED pinmodes
  pinMode(led[0],OUTPUT);
  pinMode(led[1],OUTPUT);
  pinMode(led[2],OUTPUT);
  pinMode(led[3],OUTPUT);
  pinMode(led[4],OUTPUT);
  pinMode(poten,OUTPUT);
}

void loop() {
  //time sleep
  current_time = millis();
  elapsed_time = current_time - start_time;
  if(elapsed_time >= round(Data[4])*6000){
    digitalWrite(led[4],LOW);
  }
  else{
    digitalWrite(led[4],HIGH);
  }
}
