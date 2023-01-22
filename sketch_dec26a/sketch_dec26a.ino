#include <AmperkaKB.h>
#include <Wire.h>
AmperkaKB KB(8,7,6, 5, 4, 3, 2);
char pass[6]={'*','*','*','*','*','*'};
char password[6]{'1','2','3','4','5','6'};
 int i=0, flag=0, trevoga=0;
 int flagT=0, flagP=0, flagS=0;
#include <iarduino_I2C_connect.h> 
iarduino_I2C_connect I2C2; 
 byte           REG_Array[12];
#include "DHT.h"
float h=0;
float t=0;
int gaz=0;
int prot=0;
#define DHTPIN 10 
bool flagProt=0;
// Инициируем датчик
// Для DHT22 вместо DHT11 вписываем DHT22
DHT dht(DHTPIN, DHT11);
void setup() {
  for(int h=3;h<=8;h++){
     REG_Array[h]="*";
  }
   KB.begin(KB4x3);
  Wire.begin(0x01);                                   // инициируем подключение к шине I2C в качестве ведомого (slave) устройства, с указанием своего адреса на шине.
  I2C2.begin(REG_Array); /* регистрируем запрошенное событие */
 Serial.begin(9600); 
 pinMode(9,INPUT_PULLUP);/* открываем серийный порт для дебаггинга */
 dht.begin();
  pinMode(A0,INPUT);
   pinMode(A1,INPUT);
  pinMode(11,OUTPUT);
  pinMode(17,OUTPUT);
  pinMode(12,INPUT_PULLUP);
   pinMode(16,OUTPUT);}

void loop(){
  if(prot>=200&&flagProt==0){
    Serial.println("TECHET");
  digitalWrite(11,HIGH);//motor otkachki
  digitalWrite(17,HIGH);//kran
 REG_Array[0]=4;
 flagProt=1; }
  if(prot<200&&flagProt==1){
    digitalWrite(11,LOW);
    REG_Array[0]=6; 
 Serial.println("VODA OTKACH"); 
 flagProt=0;   
  }
  if(digitalRead(12)!=1){
   REG_Array[0]=0;  
Serial.println("VODA VKLUCH");
 digitalWrite(17,LOW);
  }
prot = analogRead(A1);
h = dht.readHumidity();

// Считываем температуру
 t = dht.readTemperature();
 REG_Array[10]=h;
  REG_Array[11]=t;
  
 gaz=analogRead(A0);
 if(gaz>=200){//значение получается эксперементально
  REG_Array[0]=5;
  Serial.println("ytechka!!!");
  digitalWrite(16, LOW);
}
  trevoga=digitalRead(9);
  if(trevoga==1&&flagT==0&&flagP==1){Serial.println("Тревога");
  REG_Array[0]=3;
    flagT=1;
  }
  if(flagT==1&&flagP==1){
    for(int i0=0;i0<6; i0++){
    if(pass[i0]==password[i0]){
      flagS++;
    }else {flagS=0;}}
    if( flagS==6){
      flagS=0;
      flagP=0;
      flagT=0;
      Serial.println("Тревоги нет");
       REG_Array[0]=0;
       digitalWrite(16, LOW);
    
     for(int i0=0;i0<6; i0++){
   pass[i0]='*';
   REG_Array[i0+3]=pass[i0];
  } i=0;}
  }
  if(flagT==0&&flagP==0){
    for(int i0=0;i0<6; i0++){
    if(pass[i0]==password[i0]){
      flagS++;
    }else {flagS=0;}}
    if( flagS==6){
      flagT=0;
      flagP=1;
      flagS=0;
       Serial.println("Дом на сигнализации");
       digitalWrite(16, HIGH);
       REG_Array[0]=1;
    for(int i0=0;i0<6; i0++){
   pass[i0]='*';
   REG_Array[i0+3]=pass[i0];
  } i=0; }
  }
   if(flagT==0&&flagP==1){
    for(int i0=0;i0<6; i0++){
    if(pass[i0]==password[i0]){
      flagS++;
    }else {flagS=0;}}
    if( flagS==6&&trevoga==0){
      flagT=0;
      flagP=0;
      flagS=0;
       Serial.println("Дом без сигнализации");
        REG_Array[0]=2;
         digitalWrite(16, LOW);
     for(int i0=0;i0<6; i0++){
   pass[i0]='*';
   REG_Array[i0+3]=pass[i0];
  } i=0;
    }}
  // считывание данных с клавиатуры
  KB.read();
  // опеределяем клик кнопки
  if (KB.justPressed()) {
    // печатаем номер кнопки и её символ в последовательный порт
   // Serial.print("Key is press ");
    //Serial.print(KB.getNum);
   // Serial.print(" = \"");
   // Serial.print(KB.getChar);
   // Serial.println("\"");
   if(flag==0){
    if(KB.getChar!='#' && KB.getChar!='*' ){
    
    pass[i]=KB.getChar;
   
   i++; 
   if(i>=6){i=6;}
   }
  
 if(KB.getChar=='#'){
  i--;
  pass[i]='*';
  REG_Array[i+3]=pass[i];
  if(i==0){
    i=0;
  }}
  if(KB.getChar=='*'){
    i=0;
    for(int i0=0;i0<6; i0++){
pass[i0]='*';
REG_Array[i0+3]=pass[i0];
  }}
  flag=1;
  Serial.println(" ");
 for(int i0=0;i0<6; i0++){
Serial.print(pass[i0]);
REG_Array[i0+3]=pass[i0];
}Serial.println(" ");}
for(int i0=0;i0<6; i0++){
Serial.print(char(REG_Array[i0+3]));
}Serial.println(" ");}
 
  
  // определяем отжатие кнопки
  if (KB.justReleased()) {
    flag=0;
    // печатаем номер кнопки и её символ в последовательный порт
    /*Serial.print("Key is release ");
    Serial.print(KB.getNum);
    Serial.print(" = \"");
    Serial.print(KB.getChar);
    Serial.println("\"");*/
  }
  //Serial.println(REG_Array[1]);
 if( REG_Array[1]==48){
  REG_Array[1]=0;
    flagT=0;
    flagP=0;
    flagS=0;
    Serial.println("Дом без сигнализации");
     digitalWrite(16, LOW);
    REG_Array[0]=2;
    for(int i0=0;i0<6; i0++){
   pass[i0]='*';
   REG_Array[i0+3]=pass[i0];
  } i=0;
 }
  if( REG_Array[1]==49){
  REG_Array[1]=1;
     flagT=0;
      flagP=1;
      flagS=0;
    Serial.println("Дом на сигнализации");
     digitalWrite(16, HIGH);
    REG_Array[0]=1;
    for(int i0=0;i0<6; i0++){
   pass[i0]='*';
   REG_Array[i0+3]=pass[i0];
  } i=0;
 }
// Serial.println(REG_Array[2]);
 if( REG_Array[2]==49){
  REG_Array[2]=0;
   flagS=0;
   flagP=0;
   flagT=0;
   Serial.println("Тревоги нет");
   REG_Array[0]=0;
    
     for(int i0=0;i0<6; i0++){
   pass[i0]='*';
  REG_Array[i0+3]=pass[i0]; 
  } i=0;
  }}

// Функция для извлечения любых принимаемых данных от мастера на шину


 

 
// Функция для извлечения любых принимаемых данных от мастера на шину

 
// Функция для извлечения любых отправляемых данных от мастера на шину
