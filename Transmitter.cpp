#include <AESLib.h> // Include AES library for encryption

// AES Encryption Key (16-byte key)
#define KEY "1234567890123456"
AESLib aesLib;

// Pins for HC-12
#define TX_PIN 3 // HC-12 TX
#define RX_PIN 2 // HC-12 RX

// SoftwareSerial for HC-12 communication
#include <SoftwareSerial.h>
SoftwareSerial hc12(RX_PIN, TX_PIN);

char encryptedMessage[64]; // Buffer for encrypted data

void setup() {
  Serial.begin(9600);  // Debugging
  hc12.begin(9600);    // HC-12 baud rate
  Serial.println("Transmitter Ready");
}

void encryptMessage(const char *plainText, char *encryptedText) {
  aesLib.encrypt64(plainText, strlen(plainText), encryptedText, KEY);
}

void loop() {
  // Prepare data
  String message = "Signal Detected at Lat:10.1234 Lon:76.5678";
  char plainText[64];
  message.toCharArray(plainText, 64);

  // Encrypt the message
  encryptMessage(plainText, encryptedMessage);

  // Send the encrypted message over HC-12
  hc12.println(encryptedMessage);
  Serial.print("Sent: ");
  Serial.println(encryptedMessage);

  delay(5000); // Send every 5 seconds
}
