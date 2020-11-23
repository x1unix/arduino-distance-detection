#include "rangefinder.hpp"

RangeFinder::RangeFinder(uint8_t pin_trigger, uint8_t pin_echo)
{
    p_trigger = pin_trigger;
    p_echo = pin_echo;
}

void RangeFinder::init()
{
    pinMode(p_trigger, OUTPUT);
    pinMode(p_echo, INPUT);
}

unsigned int RangeFinder::probe()
{
    digitalWrite(p_trigger, LOW);
    delayMicroseconds(2);
    
    // Send signal.
    //
    // Rangefinder expects 10us signal to start working
    digitalWrite(p_trigger, HIGH);
    delayMicroseconds(RNGF_READ_DELAY_USEC);
    digitalWrite(p_trigger, LOW);

    // get high signal duration from sensor
    return pulseIn(p_echo, HIGH);
}

unsigned int RangeFinder::read_distance()
{
    unsigned long duration = probe();

    unsigned int distance;
    // convert distance from m/s to cm/s
    //
    // "distance = duration * 340 m/s = duration * 0.034 m/µms"
    // "distance = duration * 1/29 = duration / 29"
    //
    // Also, sound made a roundtrip - divide distance by two:
    // "distance = duration / (29*3)"
    distance = duration / 58;
    return distance;
}