#define BLYNK_TEMPLATE_ID "TMPL2n1e29Jbh"
#define BLYNK_TEMPLATE_NAME "Baby"
#define BLYNK_AUTH_TOKEN "TqsNSsLixUEqzhjR78mmhr2FFibhrudw"
 
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

//BLYNK APP AND INTENET CONNECTIONS
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Amiin";
char pass[] = "1234567888";
///////////////////////////////
#include<DHT.h>
#define Type DHT22
int teMP_Pin =27;
DHT dht(teMP_Pin,Type);
float humd;
float tempC;
float tempF;
int read_data;

#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include<ESP32Servo.h>
//#include <Servo_ESP32.h>
Servo Myservo;

int Sound_pin=12;
int waterPin=14;
int relay=26; 
int Switch=33;


void setup(){ // put your setup code here, to run once
     lcd.begin();
 lcd.clear();
// lcd.init();
 lcd.backlight();
 lcd.setCursor(2,0);
 lcd.print("Crirdy Baby");
 lcd.setCursor(3,1);
 lcd.print("Monitoring...");
 delay(2000);
 lcd.clear();
 Myservo.attach(32);
pinMode(Sound_pin,INPUT);
pinMode(waterPin,INPUT);
pinMode(Switch,INPUT);
pinMode(relay,OUTPUT);
Serial.begin(115200);
dht.begin();

 Blynk.begin(auth, ssid, pass);

  WiFi.begin(ssid, pass);
  {
    delay(1000);
    Serial.print(".");
//    lcd.clear();
  }
  Serial.println("WiFi connected");
  
    Serial.println("Ready");    //Test the serial monitor
  timer.setInterval(100L, Temperature);
    timer.setInterval(100L, WaterSensor);
  timer.setInterval(100L, Sound);
  

}

void loop(){
  int statesw=digitalRead(Switch);
  if(statesw==1){
    Myservo.write(45);
  delay(150);
    Myservo.write(0);
  delay(150); 
  }
  else{
    Myservo.write(0);
  }
    Blynk.run();
  timer.run();
  
}// END OF VOID LOOP


 void Sound(){
  int state=digitalRead(Sound_pin);
Serial.println(state);
 Blynk.virtualWrite(V0, state);
if(state==LOW){
Blynk.logEvent("sound","sound Detect !"); //Enter your Event Name
}
else if(state==HIGH){
// digitalWrite(13,LOW);
}
}// end of sound sensor

void WaterSensor(){
  int Water=digitalRead(waterPin);
Serial.println(Water);
 Blynk.virtualWrite(V1, Water);
if(Water==LOW){
 Blynk.logEvent("water","water Detect !"); //Enter your Event Name
}
else if(Water==HIGH){

}
}// end of water sensor

void Temperature(){

  tempC=dht.readTemperature();
tempF=dht.readTemperature(true);
humd=dht.readHumidity();

 Blynk.virtualWrite(V2, tempC);
Serial.print("temperaturei =");
Serial.println(tempC);
Serial.println(tempF);

 lcd.setCursor(0,0);
 lcd.print("Temp");
  lcd.setCursor(0,1);
 lcd.print(tempC);
  lcd.setCursor(9,0);
 lcd.print("Humd");
  lcd.setCursor(8,1);
 lcd.print(humd);
 
if(tempC>35){
  Blynk.logEvent("temp","High Temperature Detect !"); //Enter your Event Name
}
else{
    digitalWrite(relay,LOW);
}
}
