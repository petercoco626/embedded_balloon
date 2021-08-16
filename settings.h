

// DEVICE CURRENT STATE
#define POWER_OFF_STATE 		0
#define POWER_ON_STATE 			1
#define MODE_SWITCH_STATE 	2

// DEVICE CLOCKS [Hz]
#define FPS_DEVICE_BY_CLOCK 					800000					
#define FPS_MODE_CLOCK 								175000

// MODE STATE CONFIGURATION
#define MODE_1  1
#define MODE_2  2
#define MODE_3  3


/*
---------------------USER SETTING----------------------
*/
// MODE RUNNING TIME EACH STATE[s]
#define MODE_1_TIME_SEC  3
#define MODE_2_TIME_SEC  5
#define MODE_3_TIME_SEC  7

// DEVICE RUNNING TIME EACH FUNCTION[s]
#define POWER_ON_OFF_TOGGLE_TIME_SEC 	2
#define MODE_CHANGE_BUTTON_TIME_SEC 	0.5
#define RUN_MODE_FUNCTION_TIME_SEC		0.5
#define RUN_AOI_TIME_SEC							3

/*
---------------------------------------------------------
*/

// Device Run Frame
#define FRAME_POWER_BUTTON_TOGGLE 		(POWER_ON_OFF_TOGGLE_TIME_SEC * FPS_DEVICE_BY_CLOCK)
#define FRAME_MODE_BUTTON_SWITCH 			(MODE_CHANGE_BUTTON_TIME_SEC * FPS_DEVICE_BY_CLOCK)
#define FRAME_RUN_MODE_FUNC 					(RUN_MODE_FUNCTION_TIME_SEC * FPS_MODE_CLOCK)
#define FRAME_RUN_AOI_FUNC 						(RUN_AOI_TIME_SEC * FPS_MODE_CLOCK)

// Mode Run Frame
#define MODE_1_FRAME 						(MODE_1_TIME_SEC * FPS_MODE_CLOCK)
#define MODE_2_FRAME 						(MODE_2_TIME_SEC * FPS_MODE_CLOCK)
#define MODE_3_FRAME 						(MODE_3_TIME_SEC * FPS_MODE_CLOCK)

// 
#define CHEKING_BATTERY_TIME_SEC 				1
#define CHEKING_BATTERY_TIME_FRAME 			( CHEKING_BATTERY_TIME_SEC * FPS_MODE_CLOCK)


// BATTERY CHECK Configuration
// [V]
#define BATTERY_CHECK_STATE_1_ADC_MIN   0
#define BATTERY_CHECK_STATE_1_ADC_MAX   2988

#define BATTERY_CHECK_STATE_2_ADC_MIN   2988
#define BATTERY_CHECK_STATE_2_ADC_MAX   3320

#define BATTERY_CHECK_STATE_3_ADC_MIN   3320
#define BATTERY_CHECK_STATE_3_ADC_MAX   3874

#define BATTERY_CHECK_STATE_4_ADC_MIN   3874
#define BATTERY_CHECK_STATE_4_ADC_MAX   4095





