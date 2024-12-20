#include <SoftwareSerial.h>

// Ultrasonic sensor pins
#define TRIG1 6
#define ECHO1 7
#define TRIG2 8
#define ECHO2 9
#define TRIG3 10
#define ECHO3 11

// GSM module pins
#define GSM_TX 2
#define GSM_RX 3

// Distance threshold for obstacle detection (in cm)
const int distanceThreshold = 50;

// Initialize SoftwareSerial for GSM module
SoftwareSerial gsm(GSM_TX, GSM_RX);

// Function to measure distance
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration * 0.034) / 2; // Convert to cm
  return distance;
}

// Send SMS alert function
void sendSMS(String message) {
  gsm.println("AT");
  delay(1000);
  gsm.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  gsm.println("AT+CMGS=\"+1234567890\""); // Replace with recipient's number
  delay(1000);
  gsm.println(message);
  delay(1000);
  gsm.write(26); // CTRL+Z to send message
  delay(1000);
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  gsm.begin(9600); // GSM baud rate

  // Initialize ultrasonic sensor pins
  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG3, OUTPUT);
  pinMode(ECHO3, INPUT);

  // GSM Initialization
  sendSMS("System Initialized: Ultrasonic Obstacle Detection Active");
}

void loop() {
  // Measure distances from all sensors
  long distance1 = getDistance(TRIG1, ECHO1);
  long distance2 = getDistance(TRIG2, ECHO2);
  long distance3 = getDistance(TRIG3, ECHO3);

  // Check for obstacles
  if (distance1 > 0 && distance1 < distanceThreshold) {
    sendSMS("Obstacle detected by Sensor 1!");
    Serial.println("Obstacle detected by Sensor 1!");
  }
  if (distance2 > 0 && distance2 < distanceThreshold) {
    sendSMS("Obstacle detected by Sensor 2!");
    Serial.println("Obstacle detected by Sensor 2!");
  }
  if (distance3 > 0 && distance3 < distanceThreshold) {
    sendSMS("Obstacle detected by Sensor 3!");
    Serial.println("Obstacle detected by Sensor 3!");
  }

  delay(2000); // Wait for 2 seconds before next check
}
