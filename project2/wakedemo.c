#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "led.h"
#include "switches.h"
#include "statemachine.h"
#include "buzzer.h"

#define LED_GREEN BIT6             // P1.6

short redrawScreen = 1;
u_int fontFgColor = COLOR_BLACK;

void wdt_c_handler()
{
  static int secCount = 0;

    if (++secCount == 125 && state == 1 ) {
    secCount = 0;
    redrawScreen = 1;
  }
    else if((secCount == 10) && state == 2) {
    secCount = 0;
    redrawScreen = 1;
  }
    else if ((++secCount == 125) && state == 3) {
    secCount = 0;
    redrawScreen = 1;
  }
    else if ((secCount == 30) && state == 4) {
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

  P1DIR |= LED_GREEN;/**< Green led on when CPU on */
  P1OUT |= LED_GREEN;

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLACK);

  while (1){                 /* forever */
    if (redrawScreen) {
      switch (state) {

      case 1:                           /* S1 turns screen black & plays a tune and shoews txt*/
	clearScreen(COLOR_BLACK);
	toggle_off();
	button1();
	break;

      case 2:                           /* S2 turns buzzer off, screen to green and dims lights */
	buzzer_set_period(0);
	clearScreen(COLOR_SEA_GREEN);
	button2();
	break;

      case 3:                          /* S3 turns buzzer off, screen to white and creates a diamond */
	buzzer_set_period(0);
	clearScreen(COLOR_WHITE);
	toggle_off();
	button3();
	break;

      case 4:                        /* S4 buzzer off, screen black ,moves diamond right to left*/
	buzzer_set_period(0);
	clearScreen(COLOR_BLACK);
	button4();
	break;
	
      default:                        /* When make load show when device has been loaded */
	clearScreen(COLOR_BLACK);
	drawChar11x16(30,50,'R',COLOR_WHITE,COLOR_BLACK);
	drawChar11x16(41,50,'e',COLOR_WHITE,COLOR_SEA_GREEN);
	drawChar11x16(52,50,'a',COLOR_WHITE,COLOR_HOT_PINK);
	drawChar11x16(63,50,'d',COLOR_WHITE,COLOR_CYAN);
	drawChar11x16(74,50,'y',COLOR_WHITE,COLOR_MAGENTA);
	drawChar11x16(85,50,'!',COLOR_WHITE,COLOR_GOLDENROD);
      }
	  redrawScreen = 0;
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
