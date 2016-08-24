#include "main.h"

// ----- prototypes -----------------------------------------------------------
void InitHUD(void);

// ----- main() ---------------------------------------------------------------

int main(int argc, char* argv[]) {
	//Clock reconfigure

	// At this stage the system clock should have already been configured
	// at high speed.

	InitHUD();

	//debug
	//GPIO_SetBits(GPIOC, GPIO_Pin_Led1);
	//GPIO_SetBits(GPIOC, GPIO_Pin_Led2);
	GPIO_SetBits(GPIOC, GPIO_Pin_Led3);
	//GPIO_SetBits(GPIOF, GPIO_Pin_Led4);
	//GPIO_SetBits(GPIOF, GPIO_Pin_Led5);
	//GPIO_SetBits(GPIOA, GPIO_Pin_SLEEP_SCAN);
	//GPIO_SetBits(GPIOA, GPIO_Pin_AMP_ON);

	// Infinite loop
	while (1) {
		// Add your code here.
	}
}

// ------ implementations -----------------------------------------------------
void InitHUD(void) {
	//configure ports
	RCC_AHBPeriphClockCmd(
			RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC
					| RCC_AHBPeriph_GPIOF, ENABLE); //enable ports clock

	GPIO_InitTypeDef gpio;

	//Port A
	//Keys
	gpio.GPIO_Pin = GPIO_Pin_KeyT | GPIO_Pin_KeyPlus | GPIO_Pin_KeyMinus;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio); //init port A Leds

	//AMP_ON & SLEEP_SCAN
	gpio.GPIO_Pin = GPIO_Pin_AMP_ON | GPIO_Pin_SLEEP_SCAN;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &gpio);

	//Port C
	gpio.GPIO_Pin = GPIO_Pin_Led1 | GPIO_Pin_Led2 | GPIO_Pin_Led3
			| GPIO_Pin_Led4 | GPIO_Pin_Led5;
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &gpio);

}
