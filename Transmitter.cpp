const int ledPin = 13;
const int buzzerPin = 12;
const int ldrPin = A0;
const int ldrPin2 = A1;
const String PHONE = "+916382799541";
#include <SoftwareSerial.h>
#include <RH_ASK.h>
#include <SPI.h> 
//Alarm reciever's phone number with country code

//GSM Module RX pin to Arduino 3
//GSM Module TX pin to Arduino 2
#define rxPin 3
#define txPin 2
SoftwareSerial sim800(rxPin,txPin);

RH_ASK rf_driver;

void setup () {

  
    rf_driver.init();
          delay(1000);
  Serial.begin(115200);
  sim800.begin(9600);
//      delay(1000);
//  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);
    pinMode(ldrPin2, INPUT);


//  Serial.println("SIM800L software serial initialize");

  sim800.println("AT");
      delay(1500);
      }

void loop() {
  
  int ldrStatus = analogRead(ldrPin);  //read the state of the LDR value
  int ldrStatus2 = analogRead(ldrPin2);
      const char *msg = "be alert someone came";
  if (ldrStatus >= 400 &&  ldrStatus2 >=400) {

    noTone(buzzerPin);
    digitalWrite(ledPin, LOW);    
//    Serial.println("----------- ALARM off ACTIVATED -----------"); 
  }
  else {
       
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
       delay(1500);
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    delay(1500);
    
    tone(buzzerPin, 100);
    digitalWrite(ledPin, HIGH);
     delay(5000);


    Serial.println("----------- ALARM ACTIVATED -----------"); 
    sim800.println("AT");
    delay(500);
  
      sim800.println("ATD"+PHONE+";");
  delay(20000);
  sim800.println("ATH");
  delay(1500);
   sim800.print("AT+CMGF=1\r");
    delay(500);
    sim800.print("AT+CMGS=\"+916382799541\"\r");
    delay(500);
    sim800.print("SIM800l is working");
    delay(500);
    sim800.print((char)26);// (required according to the datasheet)
    delay(500);
        noTone(buzzerPin);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
};
