/**
 * Basic LED blink example using libopenstm32
 */

#include <libopenstm32/rcc.h>
#include <libopenstm32/gpio.h>

void gpio_setup(void){
	/* Enable GPIOC clock. */
	/* Manually: */
	// RCC_APB2ENR |= IOPCEN;
	/* Using API functions: */
	rcc_peripheral_enable_clock(&RCC_APB2ENR, RCC_APB2ENR_IOPBEN);

	/* Set GPIO12 (in GPIO port C) to 'output push-pull'. */
	/* Manually: */
	// GPIOC_CRH = (GPIO_CNF_OUTPUT_PUSHPULL << (((12 - 8) * 4) + 2));
	// GPIOC_CRH |= (GPIO_MODE_OUTPUT_2_MHZ << ((12 - 8) * 4));
	/* Using API functions: */
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO2);
	gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO5);
}

int main(void){
	volatile int i;

	gpio_setup();

	/* Blink the LED (PC12) on the board. */
	while (1) {
		/* Manually: */
		// GPIOC_BSRR = GPIO12;		/* LED off */
		// for (i = 0; i < 80000; i++);	/* Wait (needs -O0 CFLAGS). */
		// GPIOC_BRR = GPIO12;		/* LED on */
		// for (i = 0; i < 80000; i++);	/* Wait (needs -O0 CFLAGS). */

		/* Using API functions gpio_set()/gpio_clear(): */
		// gpio_set(GPIOC, GPIO12);	/* LED off */
		// for (i = 0; i < 80000; i++);	/* Wait (needs -O0 CFLAGS). */
		// gpio_clear(GPIOC, GPIO12);	/* LED on */
		// for (i = 0; i < 80000; i++);	/* Wait (needs -O0 CFLAGS). */

		/* Using API function gpio_toggle(): */
		gpio_toggle(GPIOB, GPIO2);	/* LED on/off */
		gpio_toggle(GPIOB, GPIO5);	/* LED on/off */
		for (i = 0; i < 80000; i++);	/* Wait (needs -O0 CFLAGS). */
	}

	return 0;
}
