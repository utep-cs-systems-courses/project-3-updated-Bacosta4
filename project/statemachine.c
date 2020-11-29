#include <msp430.h>
#include "statemachine.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

static char sb = 1;
int state = 0;                /* if button press */

char toggle_red()                 /* always red led! */
{
  red_on = 1;
  green_on = 0;
  led_changed = 1;
  led_update();
}

char toggle_green()              /* always green led!  */
{
  green_on = 1;
  red_on = 0;
  led_changed = 1;
  led_update();
}

char toggle_off() {                /*Turns both led off*/
  red_on = 0;
  green_on = 0;
  led_changed = 1;
  led_update();
}

void button2(){                  /* Dimms the green led */

  static int dim = 1;

  switch(dim++) {

  case 1:

  case 2:
    red_on = 1;
    led_update();
    break;

  case 3:
    red_on = 0;
    led_update();
    dim = 1;
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

void state_advance() {              /* State advance works w/ wdt*/
  static int called = 0;
  switch (state) {

  case 1:
    clearScreen(COLOR_BLACK);
    toggle_off();
    button1();
    break;

  case 2:
    buzzer_set_period(0);
    clearScreen(COLOR_WHITE);
    button2();
    break;
    
  case 3:
    buzzer_set_period(0);
    clearScreen(COLOR_WHITE);
    toggle_off();
    button3();
    break;

  case 4:
    clearScreen(COLOR_BLACK);
    button4();
    break;
  }
}

void button1() {                                /*Button one plays a tune*/
  static int note = 1;
  switch (note++) {

  case 1:
    buzzer_set_period(1480);
    drawChar11x16(42,20,'S',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(53,20,'h',COLOR_VIOLET,COLOR_BLACK);
    break;

  case 2:
    buzzer_set_period(1760);
    drawChar11x16(64,20,'o',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(75,20,'r',COLOR_VIOLET,COLOR_BLACK);
    break;

  case 3:
    buzzer_set_period(1109);
    buzzer_set_period(1760);
    drawChar11x16(86,20,'t',COLOR_VIOLET,COLOR_BLACK);
    break;

  case 4:
    buzzer_set_period(1480);
    drawChar11x16(40,37,'S',COLOR_VIOLET,COLOR_BLACK);
    break;

  case 5:
    buzzer_set_period(1175);
    buzzer_set_period(1757);
    buzzer_set_period(1757);
    drawChar11x16(51,37,'o',COLOR_VIOLET,COLOR_BLACK);
    break;

  case 6:
    buzzer_set_period(1109);
    buzzer_set_period(1175);
    drawChar11x16(62,37,'n',COLOR_VIOLET,COLOR_BLACK);
    drawChar11x16(73,37,'g',COLOR_VIOLET,COLOR_BLACK);
    note = 1;
    break;
  }
}

void button3() {
  static int x = 60;
  static int y = 60;
  static int size = 5;
  fillRectangle(35,35,50,50,COLOR_WHITE);

  for (int i = size;i >= 0;i--){                         /* Draws a diamond that grows in size */
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

void button4() {                             /* Moves diamond side to side*/
  static int move = 0;
  static int x = 60;
  static int y =60;
  static int size = 15;
  fillRectangle(35,35,50,50,COLOR_BLACK);

  for (int j =  size;j >= 0;j--){
    drawPixel(x-j,y-j+size, COLOR_YELLOW);
    drawPixel(x+j,y-j+size, COLOR_YELLOW);
    drawPixel(x-j+size,y-j, COLOR_YELLOW);
    drawPixel(x+j-size,y-j, COLOR_YELLOW);
  }

  switch(move) {                        /* Moves diamond from right to left */
  case 0:
     x = x + 4;
     y = y - 4;
     if(x > 105) {
       move = 1;
  }
  break;

  case 1:                              /* Moves diamond from left to right*/
    x = x - 4;
    y = y + 4;
    if (x < 10) {
      move = 0;
    }
  }
}
