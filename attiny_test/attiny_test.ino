/*
  Blink (modified slightly for ATTiny84/44 ICs
  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

// ATTIny84 / 44 does not have Pin 13, so we use pin 7 instead.
// A current limiting resistor should be connected in line with the LED.
int led = 7;
int detection_led = 0;

bool state = false;
long last_detection_time;

// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  pinMode(detection_led, OUTPUT);

  delay(20000);
  
  attachInterrupt(0, blink, FALLING);
  digitalWrite(led, LOW);
  last_detection_time = millis();

}

// the loop routine runs over and over again forever:
void loop() {
  if (isReadyToDetectAgain(last_detection_time)) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  
  if (state) {
    state = false;
  }
}

bool isReadyToDetectAgain(long last_detection_time) {
  return (millis() - last_detection_time) > 10000;
}

void blink() {  
  if (isReadyToDetectAgain(last_detection_time)) {
    state = true;
    last_detection_time = millis();
    for (int i = 0; i < 5; ++i) {
      digitalWrite(detection_led, HIGH);
      delayMicroseconds(20000);
      digitalWrite(detection_led, LOW);
      delayMicroseconds(60000);
    }
  }
}
