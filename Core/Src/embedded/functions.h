
#include "stm32f0xx_hal.h"
#include "settings.h"

typedef struct _ballonConfigurations{
	
	
	unsigned int timeCntModeBtn;
	unsigned int activatingSOI;
	unsigned int activatingSOIOnModeOver5;
	unsigned int isModeRunning;
	
	unsigned int timeSOI;
	unsigned int SOIDelaytime;
	unsigned int timeSOIOnModeOver5;
	unsigned int SOIDelaytimeOnModeOver5;
	
	unsigned int activatingTime;
	
	unsigned char currentModeNo;
	
	unsigned int currentBattery;
	unsigned int chekingBatteryTime;
	
	unsigned int chekingBatteryStateOnTime;
	unsigned int chekingBatteryStateOffTime;
	unsigned int chekingBatteryState;
	
} ballonConfigurations;




void switchPowerOn(ballonConfigurations* configurations);
void switchPowerOff(void);
void runDevice(ballonConfigurations* configurations, unsigned char modeState, ADC_HandleTypeDef* hadc);

void checkBatteryLed(ballonConfigurations* configurations);
void checkBatteryFor26pin(ballonConfigurations* configurations);
void getBattery(ballonConfigurations* configurations, ADC_HandleTypeDef* hadc);

void switchMode(unsigned char* modeState, ballonConfigurations* configurations);

void runMode(unsigned char ModeNo, ballonConfigurations* configurations);
void runAOIOnModeUnder4(ballonConfigurations* configurations);
void runAOIOnModeOver5(ballonConfigurations* configurations);

void modeDisplay(unsigned char modeNo, ballonConfigurations* configurations);
void runOnlySixMode(unsigned int runningBtn, ballonConfigurations* configurations);


