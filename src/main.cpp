#include <Arduino.h>
#include "rangefinder.hpp"

#define SLEEP_INTERVAL_MS 1000
#define SERIAL_SPEED 9600

#define RNGF_PIN_TRIG 5
#define RNGF_PIN_ECHO 4
#define RNGF_READ_DELAY_USEC 10

#define LED_PIN 8
#define DISTANCE_MIN_CM 150

RangeFinder rangefinder = RangeFinder(RNGF_PIN_TRIG, RNGF_PIN_ECHO);
bool led_open = false;

void setup()
{
  Serial.begin(SERIAL_SPEED);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  rangefinder.init();
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  unsigned int distance = rangefinder.read_distance();
  Serial.print(distance);
  Serial.println(" cm");
  bool is_close = distance <= DISTANCE_MIN_CM;
  if (is_close != led_open) {
    led_open = is_close;
    Serial.print("LED status: ");
    Serial.println(led_open);
    digitalWrite(LED_PIN, led_open ? HIGH : LOW);
  }

  digitalWrite(LED_BUILTIN, LOW);
  delay(SLEEP_INTERVAL_MS);
}
