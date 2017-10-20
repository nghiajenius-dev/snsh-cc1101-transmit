/*
 * Config.c
 *
 *  Created on: 22-09-2015
 *      Author: Sang
 */
#include "include.h"
#include "Config.h"

void System_config(void)
{ //config work at 80MHz
	ROM_FPUEnable();
	ROM_FPULazyStackingEnable();
	SysCtlClockSet(SYSCTL_SYSDIV_2_5| SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
}

void WTimer_counter_config(void)
{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);                      // enable peripheral
		SysCtlDelay(5);
		SysCtlPeripheralReset(SYSCTL_PERIPH_WTIMER0);
		SysCtlDelay(5);
		TimerDisable(WTIMER0_BASE, TIMER_A);

		TimerClockSourceSet(WTIMER0_BASE, TIMER_CLOCK_PIOSC);
		TimerConfigure(WTIMER0_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC_UP);        // timer A half width and counting up, periodic

		TimerPrescaleSet(WTIMER0_BASE, TIMER_A , 32 );                         // scaling timer in clk to 5 Mhz
		TimerLoadSet(WTIMER0_BASE,TIMER_A , 0xFFFFFFFF );
		TimerEnable(WTIMER0_BASE, TIMER_A);

		HWREG(WTIMER0_BASE + TIMER_O_TAV) = 0;
}

void WTimer_counter_clear(void)
{
	HWREG(WTIMER0_BASE + TIMER_O_TAV) = 0;
}

void Uart_RF_config(void)
{
	//
	    // Enable GPIO port A which is used for UART0 pins.
	    // TODO: change this to whichever GPIO port you are using.
	    //
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

	    //
	    // Configure the pin muxing for UART0 functions on port A0 and A1.
	    // This step is not necessary if your part does not support pin muxing.
	    // TODO: change this to select the port/pin you are using.
	    //
	    GPIOPinConfigure(GPIO_PA0_U0RX);
	    GPIOPinConfigure(GPIO_PA1_U0TX);

	    //
	    // Enable UART0 so that we can configure the clock.
	    //
	    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

	    //
	    // Use the internal 16MHz oscillator as the UART clock source.
	    //
	    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

	    //
	    // Select the alternate (UART) function for these pins.
	    // TODO: change this to select the port/pin you are using.
	    //
	    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	    //
	    // Initialize the UART for console I/O.
	    //
	    UARTStdioConfig(0, 115200, 16000000);
}


