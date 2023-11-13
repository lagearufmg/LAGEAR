#include <DFPlayerMini_Fast.h>

#if !defined(UBRR1H)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(16, 17); // RX, TX
#endif

DFPlayerMini_Fast myMP3;

const int sensorPin = 15;
const int relayPin = 27;

bool presenceDetection() {
  // Use sensorPin to detect presence
  bool sensorValue = digitalRead(sensorPin);
  return sensorValue == HIGH; // Reference value for touch detection (adjust as needed)
}


void setup() {

 Serial.begin(115200);

#if !defined(UBRR1H)
  mySerial.begin(9600);
  myMP3.begin(mySerial, true);
#else
  Serial2.begin(9600);
  myMP3.begin(Serial1, true);
#endif
  

  myMP3.volume(25); // Set the volume to 20 (adjust as needed)
  pinMode(sensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); //Turn on relay
}

void loop() {
  // Check for presence
  if (presenceDetection()) {
    delay(1000);
      if (!myMP3.isPlaying()) {
        // Play the main audio
        myMP3.play(1);
        delay(10000);
        digitalWrite(relayPin, HIGH); //Turn on relay
        Serial.print("LIGOU");
        delay(15000);
        digitalWrite(relayPin, LOW);
        myMP3.stop();

      }
  }
  delay(100);
}



