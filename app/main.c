#include "bsp.h"
//#include "bsp_leds.h"
#include "mrfi.h"
#include "radios/family1/mrfi_spi.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"

//#include "../include.h"  //Conflict
#include "../Config.h"
#include "../Timer/Timer.h"
#include "../ConfigPWM.h"

//#include "../mavlink_lib_1_0_c/common/mavlink.h"

volatile uint16_t x;
mrfiPacket_t packet;
/*
 * System Analysis:
 * Date 07/03/17:
 * -> 25ms system time affected by RF_Transmit & RF_delay
 * -> CC1101 transmit time:
 * ===============
 * Date: 01/09/17:
 * - Change to SNSH_PilotCape Hardware
 */

#define RF_DELAY_TIME			3.3			//1.84ms

#define RESET_SYSTEM_TIME 		 30           // 25--> max 5m: delayed by RF_delay
#define SYSTEM_TIME_OFFSET		-5.5 			// offset System_timer value, affected by CC1101 protocol, RF delay time

#define STOP_PWM_TIME			10 			// not use, replaced by I/O PWM
#define PWM_TIME_OFFSET			0

TIMER_ID timer,stop_timer;

void Timer_reset_all(void);
void Stop_pwm_timer(void);
void config_gpio(void);

void Stop_pwm_timer(void)
{
	if(stop_timer != INVALID_TIMER_ID)
		TIMER_UnregisterEvent(stop_timer);
	stop_timer = INVALID_TIMER_ID;

	StopPWM();
}

void Timer_reset_all(void)
{
	if(timer != INVALID_TIMER_ID)
		TIMER_UnregisterEvent(timer);
	timer = INVALID_TIMER_ID;

	timer = TIMER_RegisterEvent(&Timer_reset_all, RESET_SYSTEM_TIME+SYSTEM_TIME_OFFSET);
	config_gpio();
}

//void onButtonDown(void) {
//	if (GPIOIntStatus(GPIO_PORTE_BASE, false) & GPIO_PIN_4) {
//		GPIOIntClear(GPIO_PORTE_BASE, GPIO_PIN_4);
//		GPIOIntDisable(GPIO_PORTE_BASE, GPIO_PIN_4);
//		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4,GPIO_PIN_3 | GPIO_PIN_4);
//		stop_timer = TIMER_RegisterEvent(&Stop_pwm_timer, STOP_PWM_TIME+PWM_TIME_OFFSET);
//	}
//}

int main()
{
	ConfigSystem();
	Timer_Init();
	ConfigPWM();
//	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
//	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_2, 0);  //disable PWM1, PWM2
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_3, 0); //disable PWM_EN1,2

	BSP_Init();
	MRFI_Init();
	mrfiSpiWriteReg(PA_TABLE0,0xC0);
	MRFI_WakeUp();
	MRFI_RxOn();
	packet.frame[0]=8+5;
	//config timer
	timer = TIMER_RegisterEvent(&Timer_reset_all, RESET_SYSTEM_TIME+SYSTEM_TIME_OFFSET);
	config_gpio();

	while (1)
	{
	}
}
void config_gpio(void)
{

	MRFI_Transmit(&packet, MRFI_TX_TYPE_FORCED); // send package
//	BSP_TOGGLE_LED2();

//	MRFI_DelayMs(RF_DELAY_TIME);
	SysCtlDelay(SysCtlClockGet()/6000*RF_DELAY_TIME);

	// Enable PWM
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_3, GPIO_PIN_1 | GPIO_PIN_3);
	SetPWM();
	stop_timer = TIMER_RegisterEvent(&Stop_pwm_timer, STOP_PWM_TIME+PWM_TIME_OFFSET);
}

void MRFI_RxCompleteISR()
{
	//MRFI_Transmit(&packet, MRFI_TX_TYPE_FORCED);
//	BSP_TOGGLE_LED2();

}
