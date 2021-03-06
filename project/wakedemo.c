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

  if (++secCount == 125 ) {
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

  P1DIR |= LED_GREEN;/**< Green led on when CPU on */
  P1OUT |= LED_GREEN;

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_BLACK);

  while (1){                 /* forever */

    if (state == 4) {
	  //void button4() {                             /* Moves diamond side to side */
	  static int move = 0;
	  static int x = 60;
	  static int y =60;
	  static int size = 15;
	  //fillRectangle(35,35,50,50,COLOR_BLACK);

	  for (int j =  size;j >= 0;j--){
	    drawPixel(x-j,y-j+size, COLOR_RED);
	    drawPixel(x+j,y-j+size, COLOR_RED);
	    drawPixel(x-j+size,y-j, COLOR_RED);
	    drawPixel(x+j-size,y-j, COLOR_RED);
	  }
	  
	  switch(move) {                        /* Moves diamond from right to left */

	  case 1:
	    x = x + 4;
	    y = y - 4;
	    if(x > 105){
	      move = 0;
	    }
	    break;

	  case 0:                              /* Moves diamond from left to right */
	    x = x - 4;
	    y = y + 4;
	    if (x < 10) {
	      move = 1;
	    }
	  }
	  redrawScreen = 0;
    }
    P1OUT &= ~LED_GREEN;	/* green off */
    or_sr(0x10);		/**< CPU OFF */
    P1OUT |= LED_GREEN;		/* green on */
  }
}
