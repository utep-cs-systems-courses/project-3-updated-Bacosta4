#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"
#include "statemachine.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int fontFgColor = COLOR_BLACK;

void wdt_c_handler()
{
  static int secCount = 0;

  if (++secCount == 125) {
    state_advance();
    secCount = 0;
    redrawScreen = 1;
  }

  else if(secCount == 10 && state == 2) {
    state_advance();
    secCount = 0;
    redrawScreen = 1;
  }

  else if(secCount == 30 && state == 4) {
    state_advance();
    secCount = 0;
    redrawScreen = 1;
  }
}
  

void main()
{
  configureClocks();/* setup master oscillator, CPU & peripheral clocks */
  led_init();
  buzzer_init();
  switch_init();
  enableWDTInterrupts();/* enable periodic interrupt */
  lcd_init();
  

  or_sr(0x8);/* CPU off, GIE on */


  
  P1DIR |= LED_GREEN;		/**< Green led on when CPU on */		
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLACK);
  while (1) {			/* forever */
    if (redrawScreen) {
      redrawScreen = 0;
      }
      
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
