#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <LiquidCrystal.h>
int Contrast=145;
LiquidCrystal lcd(12, 10, 5, 4, 3, 2);  

RH_ASK driver;

void setup()
{
    Serial.begin(9600);  // Debugging only
    if (!driver.init())
         Serial.println("init failed");
        analogWrite(6,Contrast);
          lcd.begin(20, 4);
}

void loop()
{
    uint8_t buf[50];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      //Serial.print();
      lcd.clear();
      lcd.setCursor(0, 0);
      Serial.print("Message: ");
      lcd.println((char*)buf);    
     
      delay(1000);    
    }
}
