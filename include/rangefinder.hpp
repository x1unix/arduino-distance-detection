#pragma once

#include <Arduino.h>

#define RNGF_READ_DELAY_USEC 10

class RangeFinder
{
private:
    uint8_t p_trigger;
    uint8_t p_echo;

    /**
     * Probes rangefinder sensor and returns signal duration
     */
    unsigned int probe();

public:
    RangeFinder(uint8_t pin_trigger, uint8_t pin_echo);

    /**
     * Initialize trigger and sensor pins
     */
    void init();

    /**
     * Polls sensor and returns distance in centimiters
     */
    unsigned int read_distance();
};
