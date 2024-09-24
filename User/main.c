#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"

uint8_t KeyNum;
int8_t Speed;

int main(){
	OLED_Init();
	Motor_Init();
	Key_Init();

	OLED_ShowString(1, 1, "Duty:");
	
	while(1){
		KeyNum = Key_GetNum();
		if(KeyNum == 1){
			Speed += 20;
		
			if(Speed > 100){
				Speed = -100;
			}
		}	
		Motor_SetSpeed(Speed);
		
		if(Speed > 0){
			OLED_ShowNum(1, 7, Speed, 3);
			OLED_ShowString(2, 1, "+   ");
		}
		else if(Speed < 0){
			OLED_ShowNum(1, 7, -Speed, 3);
			OLED_ShowString(2, 1, "-   ");
		}
		else if(Speed == 0){
			OLED_ShowNum(1, 7, Speed, 3);
			OLED_ShowString(2, 1, "STOP");
		}
		OLED_ShowChar(1, 10, '%');
	}
}
