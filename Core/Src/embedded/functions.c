

#include "functions.h"



void switchPowerOn(ballonConfigurations* configurations){
    
		configurations->timeCntModeBtn = 0;
		configurations->activatingSOI = 0;
		configurations->isModeRunning = 0;
	
	
		configurations->timeSOI = 0;
	
		configurations->activatingTime = 0;
		configurations->breakingTime = 0;
		configurations->breakingCount = 0;

	
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
	
	
	if(configurations->timeSOI == 0){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	}
	configurations->timeSOI++;
	if(configurations->timeSOI == FRAME_RUN_AOI_FUNC){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
		configurations->activatingSOI = 0;
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
								configurations->activatingSOI = 1;
								configurations->isModeRunning = 0;
							}
							
							break;
							
					case MODE_4:

							// 모터 동작 ! 
								if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}

							if(configurations->breakingCount == 0){
								if(configurations->activatingTime < MODE_4_1_FRAME) configurations->activatingTime++;

								// 모터 동작 휴식
								if(configurations->activatingTime >= MODE_4_1_FRAME && configurations->breakingTime == 0){
									HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
									
								}
								
								if(configurations->activatingTime >= MODE_4_1_FRAME && configurations->breakingTime < MODE_4_BREAKING_FRAME) configurations->breakingTime++;

								if(configurations->breakingTime >= MODE_4_BREAKING_FRAME){
									configurations->breakingCount++;
									configurations->breakingTime = 0;
									configurations->activatingTime = 0;
								}
							}
							else if(configurations->breakingCount == 1){
								if(configurations->activatingTime < MODE_4_2_FRAME) configurations->activatingTime++;

								// 모터 동작 휴식
								if(configurations->activatingTime >= MODE_4_2_FRAME && configurations->breakingTime == 0){
									HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
									
								}

								if(configurations->activatingTime >= MODE_4_2_FRAME && configurations->breakingTime < MODE_4_BREAKING_FRAME) configurations->breakingTime++;
								
								if(configurations->breakingTime >= MODE_4_BREAKING_FRAME){
									configurations->breakingCount++;
									configurations->breakingTime = 0;
									configurations->activatingTime = 0;
								}
							}
							else{
								if(configurations->activatingTime < MODE_4_3_FRAME) configurations->activatingTime++;

								// 모터 동작 휴식
								if(configurations->activatingTime >= MODE_4_3_FRAME && configurations->breakingTime == 0){
									HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
									
								}
								
								if(configurations->activatingTime >= MODE_4_3_FRAME && configurations->breakingTime < MODE_4_BREAKING_FRAME) configurations->breakingTime++;

								if(configurations->breakingTime >= MODE_4_BREAKING_FRAME){
									configurations->activatingTime = 0;
									configurations->activatingSOI = 1;
									configurations->isModeRunning = 0;
									configurations->breakingCount = 0;
									configurations->breakingTime = 0;
								}
							}
							break;	

					case MODE_5:
							// 모터 동작 ! 
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							if(configurations->activatingTime < MODE_5_FRAME) configurations->activatingTime++;

							// 모터 동작 휴식
							if(configurations->activatingTime >= MODE_5_FRAME && configurations->breakingTime == 0){
								
								// mode 4의 경우 총 3번쉬어야 하기 때문에 3번이 아니면 breaking Time 동안 쉬기
								if(configurations->breakingCount < MODE_5_BREAKING_COUNT){
									HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								}
							}
							
							if(configurations->activatingTime >= MODE_5_FRAME && configurations->breakingTime < MODE_5_BREAKING_FRAME) configurations->breakingTime++;
							// 쉬는 시간이 끝나면 쉬는시간 리셋, 카운트 +1, 모터 동작시간 리셋
							if(configurations->breakingTime >= MODE_5_BREAKING_FRAME){
								configurations->breakingCount++;
								configurations->breakingTime = 0;
								configurations->activatingTime = 0;
							}

							// 모터 동작시간이 꽉찼는데, 쉰 횟수또한 조건을 만족했다면 동작 루틴 스탑
							if(configurations->breakingCount >= MODE_5_BREAKING_COUNT ){
								
								configurations->activatingTime = 0;
								configurations->activatingSOI = 1;
								configurations->isModeRunning = 0;
								configurations->breakingCount = 0;
								configurations->breakingTime = 0;
							}
							break;		
					case MODE_6:
							// 모터 동작 ! 
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							if(configurations->activatingTime < MODE_6_FRAME) configurations->activatingTime++;

							// 모터 동작 휴식
							if(configurations->activatingTime >= MODE_6_FRAME && configurations->breakingTime == 0){
								
								// mode 4의 경우 총 3번쉬어야 하기 때문에 3번이 아니면 breaking Time 동안 쉬기
								if(configurations->breakingCount < MODE_6_BREAKING_COUNT){
									HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
									
								}
							}
							
							if(configurations->activatingTime >= MODE_6_FRAME && configurations->breakingTime < MODE_6_BREAKING_FRAME) configurations->breakingTime++;
							
							// 쉬는 시간이 끝나면 쉬는시간 리셋, 카운트 +1, 모터 동작시간 리셋
							if(configurations->breakingTime >= MODE_6_BREAKING_FRAME){
								configurations->breakingCount++;
								configurations->breakingTime = 0;
								configurations->activatingTime = 0;
							}

							// 모터 동작시간이 꽉찼는데, 쉰 횟수또한 조건을 만족했다면 동작 루틴 스탑
							if(configurations->breakingCount >= MODE_6_BREAKING_COUNT ){
								
								configurations->activatingTime = 0;
								configurations->activatingSOI = 1;
								configurations->isModeRunning = 0;
								configurations->breakingCount = 0;
								configurations->breakingTime = 0;
							}
							break;	
					case MODE_7:
							// mode 7부터는 반복기능이 필요함 !! 
							// 모터 동작 ! 
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							if(configurations->activatingTime < MODE_7_FRAME) configurations->activatingTime++;

							// 모터 동작 휴식
							if(configurations->activatingTime >= MODE_7_FRAME && configurations->breakingTime == 0){
								
								// mode 7의 경우, 1초동작, 1초휴식이 무한 반복이다 
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								
							}
							
							if(configurations->activatingTime >= MODE_7_FRAME && configurations->breakingTime < MODE_7_BREAKING_FRAME) configurations->breakingTime++;
							
							// 모드 7에서는 무한반복이므로 솔레노이드를 돌릴필요가 없다. 계속 무한 반복이다.
							if(configurations->breakingTime >= MODE_7_BREAKING_FRAME){
								configurations->breakingTime = 0;
								configurations->activatingTime = 0;
							}

							
							break;

					case MODE_8:
							// mode 8은 휴식시간이 각각 다름.
							// 모터 동작 ! 
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}

							if(configurations->breakingCount == 0){
								if(configurations->activatingTime < MODE_8_1_FRAME) configurations->activatingTime++;

								// 모터 동작 휴식
								if(configurations->activatingTime >= MODE_8_1_FRAME && configurations->breakingTime == 0){
									HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
									
								}
								
								if(configurations->activatingTime >= MODE_8_1_FRAME && configurations->breakingTime < MODE_8_1_BREAKING_FRAME) configurations->breakingTime++;

								if(configurations->breakingTime >= MODE_8_1_BREAKING_FRAME){
									configurations->breakingCount++;
									configurations->breakingTime = 0;
									configurations->activatingTime = 0;
								}
							}
							else if(configurations->breakingCount == 1){
								if(configurations->activatingTime < MODE_8_2_FRAME) configurations->activatingTime++;

								// 모터 동작 휴식
								if(configurations->activatingTime >= MODE_8_2_FRAME && configurations->breakingTime == 0){
									HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
									
								}

								if(configurations->activatingTime >= MODE_8_2_FRAME && configurations->breakingTime < MODE_8_2_BREAKING_FRAME) configurations->breakingTime++;
								
								if(configurations->breakingTime >= MODE_8_2_BREAKING_FRAME){
									configurations->breakingCount++;
									configurations->breakingTime = 0;
									configurations->activatingTime = 0;
								}
							}
							else{
								if(configurations->activatingTime < MODE_8_3_FRAME) configurations->activatingTime++;

								// 모터 동작 휴식
								if(configurations->activatingTime >= MODE_8_3_FRAME && configurations->breakingTime == 0){
									HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
									
								}
								
								if(configurations->activatingTime >= MODE_8_3_FRAME && configurations->breakingTime < MODE_8_3_BREAKING_FRAME) configurations->breakingTime++;

								if(configurations->breakingTime >= MODE_8_3_BREAKING_FRAME){
									configurations->breakingCount = 0;
									configurations->breakingTime = 0;
									configurations->activatingTime = 0;
								}
							}

							
							break;
					case MODE_9:
							// mode 7부터는 반복기능이 필요함 !! 
							// mode 9는 mode 7과 흡사
							// 모터 동작 ! 
							if(configurations->activatingTime == 0){
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
							}
							if(configurations->activatingTime < MODE_9_FRAME) configurations->activatingTime++;

							// 모터 동작 휴식
							if(configurations->activatingTime >= MODE_9_FRAME && configurations->breakingTime == 0){
								
								HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
								
							}
							
							if(configurations->activatingTime >= MODE_9_FRAME && configurations->breakingTime < MODE_9_BREAKING_FRAME) configurations->breakingTime++;
							
							if(configurations->breakingTime >= MODE_9_BREAKING_FRAME){
								configurations->breakingTime = 0;
								configurations->activatingTime = 0;
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
		switch(*modeState){
			case MODE_1:
				*modeState = MODE_2;
				break;
			case MODE_2:
				*modeState = MODE_3;
				break;
			case MODE_3:
				*modeState = MODE_4;
				break;
			case MODE_4:
				*modeState = MODE_5;
				break;
			case MODE_5:
				*modeState = MODE_6;
				break;
			case MODE_6:
				*modeState = MODE_7;
				break;
			case MODE_7:
				*modeState = MODE_8;
				break;
			case MODE_8:
				*modeState = MODE_9;
				break;
			case MODE_9:
				*modeState = MODE_1;
				break;
			default:
				break;
		}
    
	}
}



void checkBattery(ADC_HandleTypeDef* hadc, ballonConfigurations* configurations){
		
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
		  
	
			if( configurations->chekingBatteryTime == CHEKING_BATTERY_TIME_FRAME){
				HAL_ADC_Start(hadc);
				HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
				unsigned int value = HAL_ADC_GetValue(hadc);
				
				if( value != configurations->compareBattery){
					if(value > BATTERY_CHECK_STATE_1_ADC_MIN && value <= BATTERY_CHECK_STATE_1_ADC_MAX){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11,GPIO_PIN_SET);
						
						configurations->chekingBatteryState = 0;
					}
					else if(value > BATTERY_CHECK_STATE_2_ADC_MIN && value <= BATTERY_CHECK_STATE_2_ADC_MAX){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12 | GPIO_PIN_11,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9 | GPIO_PIN_10,GPIO_PIN_SET);
						
						configurations->chekingBatteryState = 0;
					}
					else if(value > BATTERY_CHECK_STATE_3_ADC_MIN && value <= BATTERY_CHECK_STATE_3_ADC_MAX){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_10,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);
						
						configurations->chekingBatteryState = 0;
					}
					else if(value > BATTERY_CHECK_STATE_4_ADC_MIN && value <= BATTERY_CHECK_STATE_4_ADC_MAX){
						HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_10 | GPIO_PIN_9,GPIO_PIN_RESET);
						
						// new
						configurations->chekingBatteryState = 2;
						HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
					}
				}
				
				configurations->compareBattery = value;
				HAL_ADC_Stop(hadc);
		
			}
		
			if( configurations->chekingBatteryTime > 0 ) configurations->chekingBatteryTime -= 1;
			else configurations->chekingBatteryTime = CHEKING_BATTERY_TIME_FRAME;

}