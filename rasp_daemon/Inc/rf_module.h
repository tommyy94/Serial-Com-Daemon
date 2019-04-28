/**
 * rf_module.h
 * This header handles Aurel Wireless TX-MID-3V radio module.
 * This module uses pins PTA0, PTA1, PTA2, PTA3.
 */
# pragma once

/* Headers */
#include <iostream>
#include <stdint.h>
#include <time.h>
#include <errno.h>

#include "io.h"


#define DELAY_NS(ns)            ((const struct timespec[]){ { 0, (ns) } }, NULL);


class RF_Module
{
private:
    uint8_t CurrentMode;
    
public:
    RF_Module(void) {};
    void Init(void);
    void SetPowerdownMode(void);
    void SetIdleMode(void);
    void SetTransmissionMode(void);
    void SetReceiverMode(void);
};


/* Global variables */

/* Global function prototypes */
