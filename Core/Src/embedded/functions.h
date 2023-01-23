
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
	unsigned int breakingTime;
	unsigned int breakingCount;
	
	unsigned char currentModeNo;
	
	unsigned int compareBattery;
	unsigned int chekingBatteryTime;
	
	unsigned int chekingBatteryStateOnTime;
	unsigned int chekingBatteryStateOffTime;
	unsigned int chekingBatteryState;
	
		
	
} ballonConfigurations;




void switchPowerOn(ballonConfigurations* configurations);
void switchPowerOff(void);
void runDevice(ballonConfigurations* configurations, unsigned char modeState, ADC_HandleTypeDef* hadc);

void checkBatteryLed(ADC_HandleTypeDef* hadc, ballonConfigurations* configurations);
void checkBattery(ballonConfigurations* configurations);
void switchMode(unsigned char* modeState, ballonConfigurations* configurations);

void runMode(unsigned char ModeNo, ballonConfigurations* configurations);
void runAOIOnModeUnder4(ballonConfigurations* configurations);
void runAOIOnModeOver5(ballonConfigurations* configurations);

void modeDisplay(unsigned char modeNo, ballonConfigurations* configurations);
void runOnlySixMode(unsigned int runningBtn, ballonConfigurations* configurations);


