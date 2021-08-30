

#include "functions.h"



void switchPowerOn(ballonConfigurations* configurations){
    
		configurations->timeCntModeBtn = 0;
		configurations->activatingSOI = 0;
		configurations->isModeRunning = 0;
	
		configurations->timeSOI = 0;
	
		configurations->activatingTime = 0;
	
		configurations->currentModeNo = 0;
	
		configurations->compareBattery = 0;
		configurations->chekingBatteryTime = CHEKING_BATTERY_TIME_FRAME;
	
		
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
    
}

void switchPowerOff(void){
    // 25pin off
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
    // 27pin off
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
    // display off
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
						| GPIO_PIN_8 | GPIO_PIN_9,GPIO_PIN_RESET);
    // led off
		//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9 | GPIO_PIN_10 
						| GPIO_PIN_11 | GPIO_PIN_12,GPIO_PIN_SET);

}

void runDevice(ballonConfigurations* configurations, unsigned char modeState, ADC_HandleTypeDef* hadc){

	
			
    //checking Battery
		checkBattery(hadc, configurations);
	
		//current mode display
		modeDisplay(modeState, configurations);
	
    // checking Mode Button
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) == 0) configurations->timeCntModeBtn++;
    else{
				
			
				if( configurations->timeCntModeBtn > 0 && configurations->timeCntModeBtn < FRAME_RUN_MODE_FUNC) {
					if(configurations->activatingSOI == 0 && configurations->isModeRunning == 0){
						configurations->isModeRunning = 1;
					}					
				}
			
				if(configurations->isModeRunning == 1 && configurations->activatingSOI == 0){
						runMode(modeState, configurations);
				}
				
				if(configurations->activatingSOI == 1 && configurations->isModeRunning == 0){
						runAOI(configurations);
				}	
				
				configurations->timeCntModeBtn = 0;
					
    }
		


}

void runAOI(ballonConfigurations* configurations){
	
	//static unsigned int timeSOI = 0;
	if(configurations->timeSOI == 0){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	}
	configurations->timeSOI++;
	if(configurations->timeSOI == FRAME_RUN_AOI_FUNC){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		configurations->activatingSOI = 0;
		//configurations->isModeRunning = 0;
		configurations->timeSOI = 0;
	}
}



void runMode(unsigned char ModeNo, ballonConfigurations* configurations){
    

		switch(ModeNo){
					case MODE_1:
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
								
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_1_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								
								configurations->activatingTime = 0;
								//configurations->timeCntModeBtn = 0;
								configurations->activatingSOI = 1;
								configurations->isModeRunning = 0;
							}
							
							break;
					case MODE_2:
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_2_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								configurations->activatingTime = 0;
								//configurations->timeCntModeBtn = 0;
								configurations->activatingSOI = 1;
								configurations->isModeRunning = 0;
							}
							
							break;
					case MODE_3:
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_3_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								configurations->activatingTime = 0;
								//configurations->timeCntModeBtn = 0;
								configurations->activatingSOI = 1;
								configurations->isModeRunning = 0;
							}
							
							break;
					default:
							break;            
		}
		
}


void modeDisplay(unsigned char modeNo, ballonConfigurations* configurations){
		
	if(configurations->currentModeNo != modeNo){
		configurations->currentModeNo = modeNo;
		switch(configurations->currentModeNo){
			case MODE_1:
				// B, C ---> 1
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_7,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_9,GPIO_PIN_RESET);
				break;
			case MODE_2:
				// A, B, G, E, D --> 2
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 | GPIO_PIN_7 ,GPIO_PIN_RESET);
				break;
			case MODE_3:
				// A, B, C, D, G --> 3
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_3 | GPIO_PIN_7 | GPIO_PIN_6,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 | GPIO_PIN_5 ,GPIO_PIN_RESET);
				break;
			default:
				break;
			
		}
	}
	
}


void switchMode(unsigned char* modeState, ballonConfigurations* configurations){
	
	if(configurations->isModeRunning == 0 && configurations->activatingSOI == 0){ 
		switch(*modeState){
			case MODE_1:
				*modeState = MODE_2;
				break;
			case MODE_2:
				*modeState = MODE_3;
				break;
			case MODE_3:
				*modeState = MODE_1;
				break;
			default:
				break;
		}
    
	}
}



void checkBattery(ADC_HandleTypeDef* hadc, ballonConfigurations* configurations){
		
			if( configurations->chekingBatteryTime == CHEKING_BATTERY_TIME_FRAME){
				HAL_ADC_Start(hadc);
				HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
				unsigned int value = HAL_ADC_GetValue(hadc);
				
				if( value != configurations->compareBattery){
					if(value > BATTERY_CHECK_STATE_1_ADC_MIN && value <= BATTERY_CHECK_STATE_1_ADC_MAX){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11,GPIO_PIN_SET);
					}
					else if(value > BATTERY_CHECK_STATE_2_ADC_MIN && value <= BATTERY_CHECK_STATE_2_ADC_MAX){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12 | GPIO_PIN_11,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9 | GPIO_PIN_10,GPIO_PIN_SET);
					}
					else if(value > BATTERY_CHECK_STATE_3_ADC_MIN && value <= BATTERY_CHECK_STATE_3_ADC_MAX){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_10,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);
					}
					else if(value > BATTERY_CHECK_STATE_4_ADC_MIN && value <= BATTERY_CHECK_STATE_4_ADC_MAX){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_10 | GPIO_PIN_9,GPIO_PIN_RESET);
					}
				}
				
				configurations->compareBattery = value;
				HAL_ADC_Stop(hadc);
		
			}
		
			if( configurations->chekingBatteryTime > 0 ) configurations->chekingBatteryTime -= 1;
			else configurations->chekingBatteryTime = CHEKING_BATTERY_TIME_FRAME;

}