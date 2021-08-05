#include "balloonMachine.h"
#include "functions.h"

ballonConfigurations configurations;


void balloonMachine(ADC_HandleTypeDef* hadc){


    static unsigned int timeCnt = 0;
    static unsigned char currentState = POWER_OFF_STATE;
    static unsigned char modeState = MODE_1;

    // Check Power ON or Off
    // power on
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3) == 0) timeCnt++;
    else{
        if(timeCnt >= FRAME_POWER_BUTTON_TOGGLE){
					
						switch(currentState){
							case POWER_ON_STATE:
								switchPowerOff();						
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
        else if (timeCnt > FRAME_MODE_BUTTON_SWITCH && timeCnt < FRAME_POWER_BUTTON_TOGGLE){
						if(currentState == POWER_ON_STATE) currentState = MODE_SWITCH_STATE;
        }
        
				timeCnt = 0;
				
				switch(currentState){
					case POWER_OFF_STATE:
							break;
					case POWER_ON_STATE:
							runDevice(&configurations, modeState, hadc);
							break;
					case MODE_SWITCH_STATE:
							switchMode(&modeState);
							currentState = POWER_ON_STATE;
							break;
					default:
							break;
				}
        
    }


    
}
