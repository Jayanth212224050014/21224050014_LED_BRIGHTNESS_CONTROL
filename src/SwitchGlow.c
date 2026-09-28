#include "SwitchGlow.h"
int current_duty=0;
int direction=1;

void drive(void){
	CLOCK_DRV_Init(&clockMan1_InitConfig0);
    PINS_DRV_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
}

void Brightness_Init(void)
{
    PWM_Init(&pwm_pal_1_instance, &pwm_pal_1_configs);
    PWM_UpdateDuty(&pwm_pal_1_instance, 2U, 0);

}

void Brightness_Control(void)
{
	if((PINS_DRV_ReadPins(PTC) &(1<<12))==0){
		OSIF_TimeDelay(50);
		switch (current_duty)
		{
		case 750:
		    if(direction == 1)
		    {
		        current_duty = 1000;
		        direction = 0;
		    }
		    else
		    {
		        current_duty = 500;
		    }
		    break;

		case 500:
		    if(direction == 1)
		    {
		        current_duty = 750;
		    }
		    else
		    {
		        current_duty = 250;
		    }
		    break;

		case 250:
		    if(direction == 1)
		    {
		        current_duty = 500;
		    }
		    else
		    {
		        current_duty = 0;
		        direction = 1;
		    }
		    break;

		case 0:
		    current_duty = 250;
		    break;

		case 1000:
		    current_duty = 750;
		    break;
		}
		PWM_UpdateDuty(&pwm_pal_1_instance, 2U, current_duty);
		while((PINS_DRV_ReadPins(PTC)&(1<<12))==0)
		{
			OSIF_TimeDelay(10);
		}

}
}
