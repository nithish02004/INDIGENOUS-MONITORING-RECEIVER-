#include <AESLib.h> // Include AES library for decryption

// AES Decryption Key (16-byte key)
#define KEY "1234567890123456"
AESLib aesLib;

// Pins for HC-12
#define TX_PIN 3 // HC-12 TX
#define RX_PIN 2 // HC-12 RX

// SoftwareSerial for HC-12 communication
#include <SoftwareSerial.h>
SoftwareSerial hc12(RX_PIN, TX_PIN);

char decryptedMessage[64]; // Buffer for decrypted data

void setup() {
  Serial.begin(9600);  // Debugging
  hc12.begin(9600);    // HC-12 baud rate
  Serial.println("Receiver Ready");
}

void decryptMessage(const char *encryptedText, char *plainText) {
  aesLib.decrypt64(encryptedText, strlen(encryptedText), plainText, KEY);
}

void loop() {
  // Check if data is received
  if (hc12.available()) {
    char encryptedMessage[64];
    hc12.readBytesUntil('\n', encryptedMessage, sizeof(encryptedMessage));

    // Decrypt the received message
    decryptMessage(encryptedMessage, decryptedMessage);
    Serial.print("Received: ");
    Serial.println(decryptedMessage);
  }
}
