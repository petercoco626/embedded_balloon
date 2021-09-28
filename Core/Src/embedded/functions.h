
#include "stm32f0xx_hal.h"
#include "settings.h"

typedef struct _ballonConfigurations{
	
	
	unsigned int timeCntModeBtn;
	unsigned int activatingSOI;
	unsigned int isModeRunning;
	
	unsigned int timeSOI;
	
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
void checkBattery(ADC_HandleTypeDef* hadc, ballonConfigurations* configurations);
void switchMode(unsigned char* modeState, ballonConfigurations* configurations);

void runMode(unsigned char ModeNo, ballonConfigurations* configurations);
void runAOI(ballonConfigurations* configurations);

void modeDisplay(unsigned char modeNo, ballonConfigurations* configurations);



