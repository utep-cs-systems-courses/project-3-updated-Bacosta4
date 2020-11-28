#include <msp430.h>
#include "statemachine.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

static char sb = 1;
int state = 0;                /* if button press */

char toggle_red()		/* always red led! */
{
  red_on = 1;
  green_on = 0;
  led_changed = 1;
  led_update();
}

char toggle_green()	       /* always green led!  */
{
  green_on = 1;
  red_on = 0;
  led_changed = 1;
  led_update();
}

char toggle_both() {         /*turn both green & red on */
  green_on = 1;
  red_on = 1;
  led_changed = 1;
  led_update();
}

void toggle_led()           /* Turns green then red vise versa */
{  
  switch(state) {

  case 0:
    toggle_red();
    state = 1;
    break;

  case 1:
    toggle_green();
    state = 0;
    break;
  }
}

void led25()               /* Led at 25% */
 {   
    switch(state) {
      
      case 0:
	red_on = 0;
	state = 1;
	break;

      case 1:
	red_on = 0;
	state = 2;
	break;

      case 2:
	red_on = 1;
	state = 0;
	break;
    }
    led_update();
}

void led50()             /* Led at 50% */
{ 
  switch(state) {
    case 0:
      red_on = 1;
      state = 1;
      break;

    case 1:
      red_on = 0;
      state = 0;
      break;
    }
  led_update();
}

void led75()            /* Led at 75% */
{ 
  switch(state) {
    
  case 0:
    red_on = 1;
    state = 1;
    break;
    
  case 1:
    red_on = 1;
    state = 2;
    break;
    
  case 2:
    red_on = 0;
    state = 0;
    break;
  }
  led_update();
}

void button2() {                    /* Dims the Led lights 25% to 50% to 75% */
  static char st = 0;            // st is used for switch/ case
  switch (st){

  case 0:
    led50();
    led50();
    st = 1;
    break;
    
  case 1:
    led75();
    led75();
    st = 2; 
    break;

  case 2:
    led25();
    led25();
    st = 0;
    break;
 }
}

void buzzer() {              
  static int x = 500;
  if(sb) {                        /* Goes up for buzzer */
    toggle_red();
    x += 225;
  }
  else { 
    toggle_green();               /* Goes down for buzzer */
    x -= 450;
  }
  short cycles = 2000000 / x;
  buzzer_set_period(cycles);
}

void siren() {

  switch(state) {

  case 0:
    sb = 1;
    state++;
    break;
    
  case 1:
    sb = 0;
    state = 0;
    break;
    
  default:
    break;
  }
}

void state_advance() {
  switch (state) {

  case 1:
    // button1();
    break;

  case 2:
    //button2();
    break;
    
  case 3:
    clearScreen(COLOR_WHITE);
    button3();
    break;
  }
}

void button1() {
  static int note = 1;
  switch (note++) {
  case 1: buzzer_set_period(185);
    break;

  case 2: buzzer_set_period(220);
    break;

  case 3: buzzer_set_period(277.18);
    buzzer_set_period(220);
    break;

  case 4: buzzer_set_period(185);
    break;

  case 5: buzzer_set_period(293.66);
    buzzer_set_period(293.66);
    buzzer_set_period(293.66);
    note = 1;
    break;
  }
}

void button3() {
  static int x = 60;
  static int y = 60;
  static int size = 5;
  fillRectangle(35,35,50,50,COLOR_WHITE);

  for (int i = size;i >= 0;i--){                                    /* Draws a diamon that grows*/
    drawPixel(x - i, y - i +size, COLOR_BLACK);                             /* Bottom left*/
    drawPixel(x + i, y - i +size, COLOR_BLACK);                             /* Bottom right*/
    drawPixel(x - i +size, y -i, COLOR_BLACK);                             /* Top right*/
    drawPixel(x + i -size, y -i, COLOR_BLACK);                             /* Top left*/
  }
  if (size > 20){
    size = 5;
  }
  else{
    size++;
  }
}
