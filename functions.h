
#include "stm32f0xx_hal.h"
#include "settings.h"

void switchPowerOn(void);
void switchPowerOff(void);
void runDevice(unsigned char modeStatem, unsigned char* isConfig);
void checkBattery(ADC_HandleTypeDef* hadc);
void switchMode(unsigned char* modeState);
void runMode(unsigned char ModeNo, unsigned int* timeCntModeBtn);
void modeDisplay(unsigned char modeNo);