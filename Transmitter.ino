
#include <esp_now.h>
#include <WiFi.h>
uint8_t broadcastAddress[] = {0xA0,0xB7,0x65,0x64,0x36,0x48};
esp_now_peer_info_t peerInfo; //peer info
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
int ButtonState[4];
int Button[4];
int poten = 34;
int timerAdjust = 16;
float v1=0,v2=0;
void setup() {
Serial.begin(115200);
//naming all the Buttons
Button[0] = 13;
Button[1] = 14;
Button[2] = 12;
Button[3] = 27;
//ESP NOW setup
  //setitng esp as wifi station
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK){
    return;
  }
  //register peer
  memcpy(peerInfo.peer_addr,broadcastAddress,6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  //adding peer
  if(esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
//setting up all the Buttons mode
  pinMode(Button[0],INPUT);
  pinMode(Button[1],INPUT);
  pinMode(Button[2],INPUT);
  pinMode(Button[3],INPUT);
  pinMode(poten,INPUT);
  pinMode(timerAdjust,INPUT);

}

void loop() {
  //setting up all the ButtonState
  ButtonState[0] = digitalRead(Button[0]);
  ButtonState[1] = digitalRead(Button[1]);
  ButtonState[2] = digitalRead(Button[2]);
  ButtonState[3] = digitalRead(Button[3]);
//setting PWM potentiometer
  v1 = (5./4095.)*analogRead(poten);
//setting timer potentiometer
  v2 = (100./4095.)*analogRead(timerAdjust);
  
  float Data[6] = {ButtonState[0],ButtonState[1],ButtonState[2],ButtonState[3],v1,v2};
  //sending data
  esp_err_t result = esp_now_send(broadcastAddress,(uint8_t*)&Data,sizeof(Data)); 
    if (result == ESP_OK) {
    Serial.println(v1);
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
  delay(100);
}
