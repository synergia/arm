#include <stdint.h>
#include "inc/stm32f10x.h"

#define CRYSTAL     8000000ul  // quartz crystal resonator which is connected to the chip
#define FREQUENCY	72000000ul // 72MHz

static void pll_start(uint32_t crystal, uint32_t frequency);
void delay(int count);

int main(void){    
	pll_start(CRYSTAL,FREQUENCY);
    
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;  // enable clock for GPIOB
    GPIOB->CRL = 0x00300300; // PB2 and PB5 as output

	while (1){
        delay(1000000);	// delay
        GPIOB->ODR = (1 << 5);
        
        delay(2000000);	// delay
		GPIOB->ODR = (1 << 2);
	}
}

// Simple delay
void delay(int count){
    for (volatile int i = 0; i < count; i++);
}

// Setup speed
// Dont care, copy that
static void pll_start(uint32_t crystal, uint32_t frequency)
{
	uint32_t mul;
				
    // configure Flash latency for desired frequency
	if (frequency < 24000000ul) FLASH->ACR |= 0;  		// 0 wait states for core speed below 24MHz
	else if (frequency < 48000000ul) FLASH->ACR |= 1;	// 1 wait state for core speed between 24MHz and 48MHz
	else FLASH->ACR |= 2;						        // 2 wait states for core speed over 48MHz

	mul = frequency / crystal;				// PLL multiplier calculation

	if (mul > 16)							// max PLL multiplier is 16
		mul = 16;
    
    RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY));				// wait for stable clock

	RCC->CFGR |= ((mul - 2) << 18) | RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PPRE1_DIV2;	// configuration of PLL: HSE x (mul), APB1 clk = /2	
	
	RCC->CR |= RCC_CR_PLLON; // enable PLL
	while (!(RCC->CR & RCC_CR_PLLRDY));	// wait for PLL lock

	RCC->CFGR |= RCC_CFGR_SW_PLL;			// change SYSCLK to PLL
	while (((RCC->CFGR) & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);	// wait for switch
}

