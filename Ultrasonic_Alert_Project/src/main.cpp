#include <Arduino.h>
#include <NewPing.h>
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     8  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.   
#define BUZZER_PIN   4  // Pin for buzzer
#define ledPin      2 // Pin for onboard LED

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
void setup() {
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
}
void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range)
  Serial.println("cm");
  if (uS / US_ROUNDTRIP_CM <= 20 && uS / US_ROUNDTRIP_CM != 0) { // If an object is detected within 20 cm
    digitalWrite(BUZZER_PIN, HIGH); // Activate buzzer
    digitalWrite(ledPin, HIGH); // Turn on LED
  } else {
    digitalWrite(BUZZER_PIN, LOW); // Deactivate buzzer
    digitalWrite(ledPin, LOW); // Turn off LED
  }
}