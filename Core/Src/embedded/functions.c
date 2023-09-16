

#include "functions.h"



void switchPowerOn(ballonConfigurations* configurations){

	configurations->timeCntModeBtn = 0;
	configurations->activatingSOI = 0; // under mode 4
	configurations->activatingSOIOnModeOver5 = 0;
	configurations->isModeRunning = 0;


	configurations->timeSOI = 0; // under mode 4
	configurations->SOIDelaytime = 0; // under mode 4
	configurations->timeSOIOnModeOver5 = 0;
	configurations->SOIDelaytimeOnModeOver5 = 0;

	configurations->activatingTime = 0;


	configurations->currentModeNo = 0;

	configurations->currentBattery = 0;
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
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9 | GPIO_PIN_10 
						| GPIO_PIN_11 | GPIO_PIN_12,GPIO_PIN_RESET);

}

void runDevice(ballonConfigurations* configurations, unsigned char modeState, ADC_HandleTypeDef* hadc){

	
			
	//checking Battery
	checkBatteryLed(configurations);

	//current mode display
	modeDisplay(modeState, configurations);
	

	
    // checking Mode Button
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) == 0) {
      if(configurations->activatingSOI == 0 && configurations->isModeRunning == 0){
        configurations->timeCntModeBtn++;
      }
    }
    else{
			
		if( configurations->timeCntModeBtn > 0 && configurations->timeCntModeBtn < FRAME_RUN_MODE_FUNC) {
			if(configurations->isModeRunning == 0){
				configurations->isModeRunning = 1;
			}					
		}
		else{
      // motor should operate after finishing aoi
			if(configurations->isModeRunning == 1){
				runMode(modeState, configurations);
			}
      // aoi should operate after finishing motor
			if(configurations->activatingSOI == 1){
				runAOIOnModeUnder4(configurations);
			}

		}
			
		
		configurations->timeCntModeBtn = 0;
					
    }
		
	

}

void runAOIOnModeUnder4(ballonConfigurations* configurations){
	
	
	if(configurations->SOIDelaytime  < SOI_DELAY_TIME_FRAME_ON_MODE_UNDER_4){
		configurations->SOIDelaytime++;
		return;
	}
	
	if(configurations->timeSOI == 0){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	}
	configurations->timeSOI++;
	if(configurations->timeSOI >= FRAME_RUN_AOI_FUNC_MODE_UNDER_4){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		configurations->activatingSOI = 0;
		configurations->timeSOI = 0;
		configurations->SOIDelaytime = 0;
	}
}

void runAOIOnModeOver5(ballonConfigurations* configurations){
	
	
	if(configurations->SOIDelaytimeOnModeOver5  < SOI_DELAY_TIME_FRAME_ON_MODE_OVER_5){
		configurations->SOIDelaytimeOnModeOver5++;
		return;
	}
	
	if(configurations->timeSOIOnModeOver5 == 0){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	}
	configurations->timeSOIOnModeOver5++;
	if(configurations->timeSOIOnModeOver5 >= FRAME_RUN_AOI_FUNC_MODE_OVER_5){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		configurations->activatingSOIOnModeOver5 = 0;
		configurations->timeSOIOnModeOver5 = 0;
		configurations->SOIDelaytimeOnModeOver5 = 0;
	}
}



void runMode(unsigned char ModeNo, ballonConfigurations* configurations){
    

		switch(ModeNo){
			
					case MODE_0:
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
								
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_0_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								
								configurations->activatingTime = 0;
								configurations->isModeRunning = 0;
								configurations->activatingSOI = 1;
							}
							
							break;
					case MODE_1:
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
								
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_1_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								
								configurations->activatingTime = 0;
								configurations->isModeRunning = 0;
								configurations->activatingSOI = 1;
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
								configurations->isModeRunning = 0;
								configurations->activatingSOI = 1;
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
								configurations->isModeRunning = 0;
								configurations->activatingSOI = 1;
							}
							
							break;
							
					case MODE_4:

							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_4_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								configurations->activatingTime = 0;
								configurations->isModeRunning = 0;
								configurations->activatingSOI = 1;
							}
							
							break;

					case MODE_5:
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_5_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								configurations->activatingTime = 0;
								configurations->isModeRunning = 0;
							}
							
							break;
					case MODE_6:
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_6_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								configurations->activatingTime = 0;
								configurations->isModeRunning = 0;
							}
							
							break;
					case MODE_7:
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_7_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								configurations->activatingTime = 0;
								configurations->isModeRunning = 0;
                configurations->activatingSOI = 1;
							}
							
							break;
					case MODE_8:
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_8_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								configurations->activatingTime = 0;
								configurations->isModeRunning = 0;
                configurations->activatingSOI = 1;
							}
							
							break;
					case MODE_9:
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							configurations->activatingTime++;
							if(configurations->activatingTime >= MODE_9_FRAME){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								configurations->activatingTime = 0;
								configurations->isModeRunning = 0;
                configurations->activatingSOI = 1;
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
			case MODE_0:
				// 0
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_4 | GPIO_PIN_5,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 ,GPIO_PIN_RESET);
				break;
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
			case MODE_4:
				// B, C, F, G --> 4
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_7 | GPIO_PIN_4 | GPIO_PIN_3, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_9  ,GPIO_PIN_RESET);
				break;
			case MODE_5:
				// Aa, Ff, Gg, Cc, Dd --> 5
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 | GPIO_PIN_9 | GPIO_PIN_3 | GPIO_PIN_7 | GPIO_PIN_6,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_5 ,GPIO_PIN_RESET);
				break;
			case MODE_6:
				// F, G, C, D, E --> 6
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_3 | GPIO_PIN_7 | GPIO_PIN_6,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_9 ,GPIO_PIN_RESET);
				break;
			case MODE_7:
				// F, A, B, C --> 7
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_4 | GPIO_PIN_7 ,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6,GPIO_PIN_RESET);
				break;
			case MODE_8:
				// A, B, C, D, E, F, G --> 8
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_3 | GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_4 | GPIO_PIN_5,GPIO_PIN_SET);
				break;
			case MODE_9:
				// A, B, C, G, F --> 9
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_3 | GPIO_PIN_7 | GPIO_PIN_4,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6 | GPIO_PIN_5 ,GPIO_PIN_RESET);
				break;
			default:
				break;
			
		}
	}
	
}


void switchMode(unsigned char* modeState, ballonConfigurations* configurations){
	
	if(configurations->isModeRunning == 0 && configurations->activatingSOI == 0){ 

    if(*modeState == MAX_MODE){
      *modeState = MODE_0;
      return;
    }
    else if(*modeState == MODE_0){
      *modeState = MODE_1;
      return;
    }
    else if(*modeState == MODE_1){
      *modeState = MODE_2;
      return;
    }
    else if(*modeState == MODE_2){
      *modeState = MODE_3;
      return;
    }
    else if(*modeState == MODE_3){
      *modeState = MODE_6;
      return;
    }
    else if(*modeState == MODE_4){
      *modeState = MODE_5;
      return;
    }
    else if(*modeState == MODE_5){
      *modeState = MODE_6;
      return;
    }
    else if(*modeState == MODE_6){
      *modeState = MODE_7;
      return;
    }
    else if(*modeState == MODE_7){
      *modeState = MODE_8;
      return;
    }
    else if(*modeState == MODE_8){
      *modeState = MODE_9;
      return;
    }
    else if(*modeState == MODE_9){
      *modeState = MODE_0;
      return;
    }
    else{
      return;
    }
    
	}
}

void getBattery(ballonConfigurations* configurations, ADC_HandleTypeDef* hadc){
  if( configurations->chekingBatteryTime == CHEKING_BATTERY_TIME_FRAME){
				HAL_ADC_Start(hadc);
				HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
				unsigned int value = HAL_ADC_GetValue(hadc);
        configurations->currentBattery = value;
				HAL_ADC_Stop(hadc);	
  }
  if( configurations->chekingBatteryTime > 0 ) configurations->chekingBatteryTime -= 1;
  else configurations->chekingBatteryTime = CHEKING_BATTERY_TIME_FRAME;
}



void checkBatteryFor26pin(ballonConfigurations* configurations){

  if(configurations->currentBattery > BATTERY_CHECK_FOR_PIN_26_TOGGLE){
    if(configurations->chekingBatteryState == 0){
      if(configurations->chekingBatteryStateOnTime == 0){
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
      }
      configurations->chekingBatteryStateOnTime++;
      
      if( configurations->chekingBatteryStateOnTime >= PIN_26_POWER_ON_FRAME){
        configurations->chekingBatteryStateOnTime = 0;
        configurations->chekingBatteryState = 1;
      }
    }
    else{
      if(configurations->chekingBatteryStateOffTime == 0){
        HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
      }
      configurations->chekingBatteryStateOffTime++;
      
      if( configurations->chekingBatteryStateOffTime >= PIN_26_POWER_OFF_FRAME){
        configurations->chekingBatteryStateOffTime = 0;
        configurations->chekingBatteryState = 0;
      }
    }
  }
  else{
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13 ,GPIO_PIN_RESET);
    configurations->chekingBatteryState = 0;
		configurations->chekingBatteryStateOnTime = 0;
		configurations->chekingBatteryStateOffTime = 0;
  }

}

void checkBatteryLed(ballonConfigurations* configurations){
		
  if(configurations->currentBattery > BATTERY_CHECK_STATE_1_ADC_MIN && configurations->currentBattery <= BATTERY_CHECK_STATE_1_ADC_MAX){
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12,GPIO_PIN_RESET);
  }
  else if(configurations->currentBattery > BATTERY_CHECK_STATE_2_ADC_MIN && configurations->currentBattery <= BATTERY_CHECK_STATE_2_ADC_MAX){
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9 | GPIO_PIN_10,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11 | GPIO_PIN_12,GPIO_PIN_RESET);										
  }
  else if(configurations->currentBattery > BATTERY_CHECK_STATE_3_ADC_MIN && configurations->currentBattery <= BATTERY_CHECK_STATE_3_ADC_MAX){
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);										
  }
  else if(configurations->currentBattery > BATTERY_CHECK_STATE_4_ADC_MIN && configurations->currentBattery <= BATTERY_CHECK_STATE_4_ADC_MAX){
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12,GPIO_PIN_SET);					
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9 ,GPIO_PIN_RESET);										
  }
  else{
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12,GPIO_PIN_RESET);
  }

}