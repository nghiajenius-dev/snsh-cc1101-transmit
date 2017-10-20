#include "bsp.h"
#include "bsp_leds.h"
#include "mrfi.h"
#include "radios/family1/mrfi_spi.h"
#include "driverlib/sysctl.h"
#include "../include.h"  //Conflict
#include "../Config.h"
#include "../Timer/Timer.h"
#include "../ConfigPWM.h"

volatile uint16_t x;
mrfiPacket_t packet;

#define RF_DELAY_TIME           3.3         //1.84ms
#define RESET_SYSTEM_TIME 50
#define STOP_PWM_TIME	10
#define MAX_RX_BUFF 200

static int16_t rx_count = 0;
static char rx_Buff[MAX_RX_BUFF];
static bool rx_uart_fin = false;
TIMER_ID timer,stop_timer;

void Timer_reset_all(void);
void Stop_pwm_timer(void);
void config_gpio(void);

//void Stop_pwm_timer(void)
//{
//	if(stop_timer != INVALID_TIMER_ID)
//		TIMER_UnregisterEvent(stop_timer);
//		stop_timer = INVALID_TIMER_ID;
//		GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4,0);
//}

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

	 timer = TIMER_RegisterEvent(&Timer_reset_all, RESET_SYSTEM_TIME);
	config_gpio();
}

void onButtonDown(void) {
    if (GPIOIntStatus(GPIO_PORTE_BASE, false) & GPIO_PIN_4) {
    	GPIOIntClear(GPIO_PORTE_BASE, GPIO_PIN_4);
    	GPIOIntDisable(GPIO_PORTE_BASE, GPIO_PIN_4);
    	GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4,GPIO_PIN_3 | GPIO_PIN_4);
    	stop_timer = TIMER_RegisterEvent(&Stop_pwm_timer, STOP_PWM_TIME);
    }
}

static void BB_UART_Handler(void) {
    uint32_t IntStatus;
    char cbyte;
    IntStatus = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, IntStatus);

    if (UARTCharsAvail(UART1_BASE)) {
        cbyte = UARTCharGet(UART1_BASE);
        if ( cbyte != '\n' ){
            rx_Buff[rx_count++] = cbyte;
        } else {
            rx_uart_fin = true;
            rx_count = 0;
        }
    }
}

void UART_BB_Init(void)
{
    uint32_t ui32_SystemClock;

    ui32_SystemClock = 80000000;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART1_BASE, ui32_SystemClock, 115200,
            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                    UART_CONFIG_PAR_NONE));

    //      UARTFIFOEnable(UART0_BASE);
    //      UARTFIFOLevelSet(UART0_BASE, UART_FIFO_TX7_8, UART_FIFO_RX1_8);
    UARTIntRegister(UART1_BASE, &BB_UART_Handler);
    IntEnable(INT_UART1);
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT | UART_INT_TX);
    UARTTxIntModeSet(UART1_BASE, UART_TXINT_MODE_EOT);
}

int main()
{
	// Set the system clock to run at 50Mhz off PLL with external crystal as
	// reference.
	//Config clock
	ConfigSystem();
	Timer_Init();
	ConfigPWM();
//	SetPWM();


	BSP_Init();
	MRFI_Init();
	mrfiSpiWriteReg(PA_TABLE0,0xC0);
	MRFI_WakeUp();
	MRFI_RxOn();
	packet.frame[0]=8+5;
	//config timer
	UART_BB_Init();

//	timer = TIMER_RegisterEvent(&Timer_reset_all, RESET_SYSTEM_TIME);
//	config_gpio();

	while (1)
	{
		//MRFI_DelayMs(200);
		//MRFI_Transmit(&packet, MRFI_TX_TYPE_FORCED);
		//BSP_TOGGLE_LED1();

	    //Handle UART MESSAGE
	    if (rx_uart_fin){
	        rx_uart_fin = false;

	        if (strcmp("{PARAM,TRIGGER_US}",rx_Buff)) {
	            config_gpio();
	        }
	    }
	}
}

//void config_gpio(void)
//{
////     GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2,0); // trigger to RF2500
////     GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4,0); //disable PWM
////
////     GPIOIntDisable(GPIO_PORTE_BASE, GPIO_PIN_4);        // Disable interrupt for PF4 (in case it was enabled)
////     GPIOIntClear(GPIO_PORTE_BASE, GPIO_PIN_4);      // Clear pending interrupts for PF4
////     GPIOIntRegister(GPIO_PORTE_BASE, onButtonDown);     // Register our handler function for port F
////     GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_4,GPIO_FALLING_EDGE);             // Configure PF4 for falling edge trigger
////     GPIOIntEnable(GPIO_PORTE_BASE, GPIO_PIN_4);     // Enable interrupt for PF4
////
////     SysCtlDelay(3200);
////     GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_2,GPIO_PIN_2);
//
//    MRFI_Transmit(&packet, MRFI_TX_TYPE_FORCED); // send package
//    MRFI_DelayMs(2);
//    //Mrfi_DelayUsecSem(200);
//    //receiver received
//    BSP_TOGGLE_LED1();
//    // Enable PWM
//    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3 | GPIO_PIN_4,GPIO_PIN_3 | GPIO_PIN_4);
//
//    stop_timer = TIMER_RegisterEvent(&Stop_pwm_timer, STOP_PWM_TIME);
//}

void config_gpio(void)
{

    MRFI_Transmit(&packet, MRFI_TX_TYPE_FORCED); // send package
    BSP_TOGGLE_LED2();

//  MRFI_DelayMs(RF_DELAY_TIME);
    SysCtlDelay(SysCtlClockGet()/6000*RF_DELAY_TIME);

    // Enable PWM
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_3, GPIO_PIN_1 | GPIO_PIN_3);
    SetPWM();
//    stop_timer = TIMER_RegisterEvent(&Stop_pwm_timer, STOP_PWM_TIME+PWM_TIME_OFFSET);
}

void MRFI_RxCompleteISR()
{
	//MRFI_Transmit(&packet, MRFI_TX_TYPE_FORCED);
	BSP_TOGGLE_LED2();

}
