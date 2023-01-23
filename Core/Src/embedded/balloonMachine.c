#include "balloonMachine.h"
#include "functions.h"

ballonConfigurations configurations;

unsigned int timeCnt = 0;
unsigned char currentState = POWER_OFF_STATE;
unsigned char modeState = MODE_1;
unsigned char batteryConfig = 0;

void balloonMachine(ADC_HandleTypeDef* hadc){



	// check battery

	if(batteryConfig == 0){

		configurations.chekingBatteryState = 0;
		configurations.chekingBatteryStateOnTime = 0;
		configurations.chekingBatteryStateOffTime = 0;
		batteryConfig = 1;
	}
	
	checkBattery(&configurations);

    // Check Power ON or Off
    // power on
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) == 0) timeCnt++;
    else{
        if(timeCnt >= FRAME_POWER_BUTTON_TOGGLE){
					
			switch(currentState){
				case POWER_ON_STATE:
						if(modeState == MODE_5 || modeState == MODE_6){
							configurations.activatingSOI = 1;
						}
						modeState = MODE_1;
						currentState = POWER_OFF_STATE;
					break;
				case POWER_OFF_STATE:
					switchPowerOn(&configurations);
					currentState = POWER_ON_STATE;
					break;
				default:
					break;
			}

            
        }
        else if (timeCnt > 0 && timeCnt < FRAME_MODE_BUTTON_SWITCH){
			if(currentState == POWER_ON_STATE) currentState = MODE_SWITCH_STATE;
        }
        
			timeCnt = 0;
			
			switch(currentState){
				case POWER_OFF_STATE:
						if(configurations.activatingSOI == 1){
							runAOI(&configurations);
						}
						if(configurations.activatingSOI == 0){
							switchPowerOff();
						}	
				
						break;
				case POWER_ON_STATE:
						runDevice(&configurations, modeState, hadc);
						
						break;
				case MODE_SWITCH_STATE:
						switchMode(&modeState, &configurations);
						currentState = POWER_ON_STATE;
						break;
				default:
						break;
			}
        
    }
  
  
}



void resetDeviceOnVoltage(void){
	
		timeCnt = 0;
		currentState = POWER_OFF_STATE;
		modeState = MODE_1;
	
		configurations.timeCntModeBtn = 0;
		configurations.activatingSOI = 0;
		configurations.isModeRunning = 0;
	
		configurations.timeSOI = 0;
	
		configurations.activatingTime = 0;
	
		configurations.currentModeNo = 0;
	
		configurations.compareBattery = 0;
		configurations.chekingBatteryTime = CHEKING_BATTERY_TIME_FRAME;
	
		configurations.chekingBatteryStateOnTime = 0;
		configurations.chekingBatteryStateOffTime = 0;
		configurations.chekingBatteryState = 0;
	
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
					| GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

		/*Configure GPIO pin Output Level */
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
														|GPIO_PIN_12, GPIO_PIN_SET);
		
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	
}


