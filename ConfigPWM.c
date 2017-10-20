/*
 * ConfigPWM.c
 *
 *  Created on: 03-02-2015
 *      Author: TQS
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "ConfigPWM.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"

void ConfigSystem(void)
{
	//Enable FPU
	//	ROM_FPULazyStackingEnable();
	//	ROM_FPUEnable();
	// Configure clock
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);		//80Mhz
}

void ConfigPWM(void)
{

	//    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
	//    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
	//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	//    GPIOPinConfigure(GPIO_PE4_M0PWM4);
	//    GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_4);
	//    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN |
	//                    PWM_GEN_MODE_NO_SYNC);
	//    //40kHz
	//    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, SysCtlClockGet()/40000-1);
	//    // 50% duty cycles
	//    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,SysCtlClockGet()/40000/2-1);
	//    //
	//    PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
	//    PWMGenDisable(PWM0_BASE, PWM_GEN_2);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	// Unlock Hardware function @PF0
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); //PWM1, PWM2; EN1,2

}

void SetPWM()
{
	// 4 wave cycles
//	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4,GPIO_PIN_3 | GPIO_PIN_4);	// Enable H-Bridge

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_2, GPIO_PIN_0|GPIO_PIN_2);
	SysCtlDelay(SysCtlClockGet()/320000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_2, 0);
	SysCtlDelay(SysCtlClockGet()/320000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_2, GPIO_PIN_0|GPIO_PIN_2);
	SysCtlDelay(SysCtlClockGet()/320000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_2, 0);
	SysCtlDelay(SysCtlClockGet()/320000);

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_2, GPIO_PIN_0|GPIO_PIN_2);
	SysCtlDelay(SysCtlClockGet()/320000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_2, 0);
	SysCtlDelay(SysCtlClockGet()/320000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_2, GPIO_PIN_0|GPIO_PIN_2);
	SysCtlDelay(SysCtlClockGet()/320000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_2, 0);
	SysCtlDelay(SysCtlClockGet()/320000);

//	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4,0);		// Disable H-Bridge


	//	PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
	//	ConfigPWM();
	//    PWMGenEnable(PWM0_BASE, PWM_GEN_2);

}

void StopPWM()
{
	//	PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, false);
	//    PWMGenDisable(PWM0_BASE, PWM_GEN_2);

	//    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);
	//    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
}
uint32_t  GetPWM()
{
	return PWMPulseWidthGet(PWM0_BASE, PWM_OUT_4);
}



