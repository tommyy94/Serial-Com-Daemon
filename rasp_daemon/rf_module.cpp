#include "rf_module.h"


/* Local defines */
#define DATA_IN     (14)
#define DATA_OUT    (15)
#define ENABLE      (17)
#define TXRX        (18)


/* Define operational modes for the RF module. */
enum OperationalModes
{
    POWERDOWN_MODE,
    IDLE_MODE,
    TRANSMISSION_MODE,
    RECEIVER_MODE
};


/* Function descriptions */
RF_Module::RF_Module(void)
{
    
}


/**
 * Initialize pins used for RF module.
 */
void RF_Module::Init(void)
{
    /* Set ENABLE as output */
    INP_GPIO(ENABLE);
    OUT_GPIO(ENABLE);
    
    /* Set TXRX as output */
    INP_GPIO(TXRX);
    OUT_GPIO(TXRX);
    
    /* Set ALT0 (RX) for GPIO14 */
    INP_GPIO(DATA_OUT);
    SET_GPIO_ALT(DATA_OUT, 0);
    
    /* Set ALT0 (TX) for GPIO15 */
    INP_GPIO(DATA_IN);
    SET_GPIO_ALT(DATA_IN, 0);
    
    SetIdleMode();
}


/* Not used since receiver needs to be ON 24/7 */
/* Power consumption 1.2 uA */
void RF_Module::SetPowerdownMode(void)
{
    GPIO_CLR = (1 << TXRX);
    GPIO_CLR = (1 << ENABLE);
    CurrentMode = POWERDOWN_MODE;
}


/* Power consumption 4.7  mA */
void RF_Module::SetIdleMode(void)
{
    GPIO_SET = (1 << ENABLE);
    GPIO_SET = (1 << TXRX);
    CurrentMode = IDLE_MODE;
}


/* Power consumption 16.2 mA */
void RF_Module::SetTransmissionMode(void)
{
    if (CurrentMode == POWERDOWN_MODE)
    {
        GPIO_SET = (1 << ENABLE);
        DELAY_NS(20000UL);
        GPIO_SET = (1 << TXRX);
        DELAY_NS(400000UL);
    }
    else if (CurrentMode == IDLE_MODE)
    {
        /* No action needed as DATA_IN is driven high during transmission */
    }
    else if (CurrentMode == RECEIVER_MODE)
    {
        GPIO_SET = (1 << TXRX);
        DELAY_NS(400000UL);
    }
    else
    {
        std::cerr << "Error switching RF mode\n" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    CurrentMode = TRANSMISSION_MODE;
}


/* Power consumption 6.8 mA */
void RF_Module::SetReceiverMode(void)
{
    if (CurrentMode == POWERDOWN_MODE)
    {
        GPIO_SET = (1 << ENABLE);
        DELAY_NS(200000UL);
        GPIO_SET = (1 << TXRX);
        DELAY_NS(200000UL);
        GPIO_CLR = (1 << TXRX);
        DELAY_NS(40000UL);
        GPIO_CLR = (1 << ENABLE);
        DELAY_NS(20000UL);
        GPIO_SET = (1 << ENABLE);
        DELAY_NS(200000UL);
    }
    else if (CurrentMode == IDLE_MODE)
    {
        GPIO_CLR = (1 << TXRX);
        GPIO_SET = (1 << ENABLE);
    }
    else if (CurrentMode == TRANSMISSION_MODE)
    {
        /* Make sure TX is done */
        DELAY_NS(3000000UL);
        
        GPIO_CLR = (1 << TXRX);
        DELAY_NS(40000UL);
        GPIO_CLR = (1 << ENABLE);
        DELAY_NS(20000UL);
        GPIO_SET = (1 << ENABLE);
        DELAY_NS(200000UL);
    }
    else
    {
        std::cerr << "Error switching RF mode\n" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    
    CurrentMode = RECEIVER_MODE;
}
