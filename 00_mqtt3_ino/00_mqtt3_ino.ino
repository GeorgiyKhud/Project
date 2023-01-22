#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <iarduino_I2C_connect.h>
//USE sample_config.h, insert real params and rename to config.h
#include "config.h"
/* DEFINE YOUR PARAMS */
//#define mqtt_topic_status "rtfbest/status"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#define mqtt_topic_comand "comand"
#define mqtt_topic_obnole "obnole"
#define mqtt_topic_soob "soob"

unsigned long int timer=0;
// How many NeoPixels are attached to the Arduino?
#include <Wire.h>
char pass[6]={'*','*','*','*','*','*'};
char password[6]{'1','2','3','4','5','6'};
int temperatureSet, powerStatus, hysteresis;
char c='0', cold ='0';
String c1;
char com[2];
// NeoPixel brightness, 0 (min) to 255 (max)
iarduino_I2C_connect I2C2;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 1;
int led;
int t,h;
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);
  Serial.println(wifi_pass);
  WiFi.begin(wifi_ssid, wifi_pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
    WiFi.printDiag(Serial);
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
 for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  
  }
   Serial.println();
  if (strcmp(topic, mqtt_topic_comand) == 0) {
    com[0]=(char)payload[0];
       I2C2.writeByte(0x01,1,com[0]);
      Serial.println(com[0]);
//    colorWipe(strip.Color(0,  255,   0)     , 50);}
  }

    
  
  if (strcmp(topic, mqtt_topic_obnole) == 0) {
com[1]=(char)payload[0];
Serial.println(com[1]);
     I2C2.writeByte(0x01,2,com[1]);
      
//    colorWipe(strip.Color(0,  255,   0)     , 50);
 }}
  
  



void reconnect() {
  //String clientId = "58458475844884522";
  bool status = false;

 // while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    Serial.print("Client ID:");
    Serial.print(mqtt_client);
    Serial.print(mqtt_login);
    Serial.print(mqtt_pass);
    if (mqtt_login == "") {
      status = client.connect(mqtt_client);
    } else {
      status = client.connect(mqtt_client, mqtt_login, mqtt_pass);
    }

    if (status) {
      Serial.println("connected");
      //client.publish(mqtt_topic_status, "reconnected");
      client.subscribe(mqtt_topic_comand);
      client.subscribe(mqtt_topic_obnole);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      
    }
  }
//}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);  // Initialize the BUILTIN_LED pin as an output
  //WARNING: BUILTIN_LED has pullup resistor, HIGH = OFF, LOW = ON
  pinMode(18, OUTPUT);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  // Turn OFF all pixels ASAP
  
   // (0x76) (0x77) (также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)
 
   Wire.begin(); //D1(20) - SCL, D2(19)- SDA
    lcd.init();
 lcd.backlight();
 lcd.setCursor(0,0);
 lcd.print("Hello");
  delay(1000);
 lcd.clear();
     client.publish(mqtt_topic_soob, "ничего не происходит");
 reconnect();}
 int g=0;
void loop() {
  t=I2C2.readByte(0x01,11);
   h=I2C2.readByte(0x01,10);
   
   char z = char(I2C2.readByte(0x01,3));
if(z !='*'){
  
   if(g==0){
     lcd.clear();
     g=1;
   }
  lcd.setCursor(0,0);
   lcd.print("vedite parol");
   //delay(2000);
    for(int r=0;r<6;r++){
   lcd.setCursor(r,1);
   Serial.println(char(I2C2.readByte(0x01,r+3)));
   char z = char(I2C2.readByte(0x01,r+3));
   lcd.print(z);
   if(c==5){
     lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ytechka gaza");
       lcd.setCursor(0,1);
      lcd.print("pokinte pomeshen");
    }
   }
}else{
  if(g==1){
     lcd.clear();
     g=0;
   }
   if(c==0||c==1||c==2){
    
   lcd.setCursor(0,0);
   lcd.print("vlajnost");
   lcd.setCursor(10,0);
   lcd.print(h);
   lcd.setCursor(0,1);
   lcd.print("temperat");
   lcd.setCursor(10,1);
   lcd.print(t);}
    if(c==5){
     lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ytechka gaza");
       lcd.setCursor(0,1);
      lcd.print("pokinte pomeshen");
    }
     if(c==3){
      lcd.clear();
       lcd.setCursor(0,0);
   lcd.print("trevoga");}
   if(c==4){
    lcd.clear();
     lcd.setCursor(0,0);
   lcd.print("ytechka voda");}
 if(c==6){
  lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("voda otkach");}
   delay (500);}
  
  if(millis()-timer>5000){
    timer = millis();
   if (!client.connected()) {
    reconnect();
  }}
  client.loop();
  c = I2C2.readByte(0x01,0);
  if(c!=cold){ lcd.clear();
    if(c==0){
   client.publish(mqtt_topic_soob,"ничего не происходит");
   Serial.println("ничего не происходит");
  }
    cold=c;
if(c==1){
   client.publish(mqtt_topic_soob,"дверь закрыта");
  Serial.println("дверь закрыта");}
  if(c==2){
   client.publish(mqtt_topic_soob,"дверь открыта");
  Serial.println("дверь открыта");}
   if(c==3){
   client.publish(mqtt_topic_soob,"кто-то проник в дом");
  Serial.println("кто-то проник в дом");
 
   lcd.print("trevoga");}
   if(c==4){
   client.publish(mqtt_topic_soob,"утечка воды");
  Serial.println("утечка воды");

   lcd.print("ytechka voda");}
  if(c==5){
   client.publish(mqtt_topic_soob,"утечка газа");
 Serial.println("утечка газа"); }
 if(c==6){
   client.publish(mqtt_topic_soob,"вода откачана");
 Serial.println("вода откачана"); 
 
   lcd.print("voda otkach");}
   lcd.clear();}
    long now = millis();
    //delay(500);
    /*char buf[10];
    sprintf(buf, "%f", t);
    client.publish(mqtt_topic_soob, buf);
    delay(1000);
    char buff[5];
    if (led) {
      sprintf(buff, "true");       
    } else {
      sprintf(buff, "false");
    }
    client.publish(mqtt_topic_power, buff);
  }*/

  /* if (now - lastMsg > 30000) {    //TODO: overflow long in 49 days
    lastMsg = now;
    ++value;
    snprintf (msg, sizeof(msg), "status #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish(mqtt_topic_status, msg);
  }*/
}
