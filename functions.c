
#include "stm32f0xx_hal.h"
#include "functions.h"
#include "settings.h"
//#include <stdio.h>


void switchPowerOn(void){
    
		//battery check
    
}

void switchPowerOff(void){
    // 25pin off
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
    // 27pin off
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
    // display off
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
						| GPIO_PIN_8 | GPIO_PIN_9,GPIO_PIN_SET);
    // led off
		//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9 | GPIO_PIN_10 
						| GPIO_PIN_11 | GPIO_PIN_12,GPIO_PIN_SET);

}

void runDevice(unsigned char modeState, unsigned char* isConfig){

	
		static unsigned int timeCntModeBtn = 0;
		static unsigned char currentDeviceState = DEVICE_NORMAL;
	
    
    // checking Mode Button
    if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_4) == 0) timeCntModeBtn++;
    else{
				
				if(timeCntModeBtn > FRAME_RUN_MODE_FUNC){
					runMode(modeState, &timeCntModeBtn);
				}
				//timeCntModeBtn = 0;
    }

}


void runMode(unsigned char ModeNo, unsigned int* timeCntModeBtn){
    static unsigned int activatingTime = 0;
    switch(ModeNo){
        case MODE_1:
						if(activatingTime == 0){
							HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
						}
						activatingTime++;
            if(activatingTime == MODE_1_FRAME){
							HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
							activatingTime = 0;
							*timeCntModeBtn = 0;
						}
						
            break;
        case MODE_2:
						if(activatingTime == 0){
							HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
						}
						activatingTime++;
            if(activatingTime == MODE_2_FRAME){
							HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
							activatingTime = 0;
							*timeCntModeBtn = 0;
						}
						
            break;
        case MODE_3:
						if(activatingTime == 0){
							HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
						}
						activatingTime++;
            if(activatingTime == MODE_3_FRAME){
							HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
							activatingTime = 0;
							*timeCntModeBtn = 0;
						}
						
            break;
        default:
            break;            
    }
}


void modeDisplay(unsigned char modeNo){
	
	switch(modeNo){
		case MODE_1:
			// B, C
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_7,GPIO_PIN_RESET);
			break;
		case MODE_2:
			// A, B, G, E, D
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6,GPIO_PIN_RESET);
			break;
		case MODE_3:
			// A, B, C, D, G
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_3 | GPIO_PIN_7 | GPIO_PIN_6,GPIO_PIN_RESET);
			break;
		default:
			break;
		
	}
	
}


void switchMode(unsigned char* modeState){
    if(*modeState == MODE_3){
        *modeState = MODE_1;
    }
    else *modeState += 1;
}



void checkBattery(void){
    // battery check

    // display LED on Battery;



}