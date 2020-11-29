#include <msp430.h>
#include "statemachine.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "lcdutils.h"
#include "lcddraw.h"

int state = 0;                /* if button press */
static char dim = 0;           /* used for dims switch case */

char toggle_off() {                /*Turns both led off*/
  red_on = 0;
  green_on = 0;
  led_changed = 1;
  led_update();
}
  
void dim25() {                      /* Dims leds to 25% */
  switch(dim) {

  case 0:
    red_on = 1;
    dim++;
    break;
  case 1:
  case 2:
  case 3:
    red_on = 0;
    dim++;
    break;
  default:
    dim = 0;
  }
  led_changed = 1;
  led_update();
}
 
void dim50() {                        /* Dims leds to 50% */
  switch(dim){
  case 0:
  case 1:
    red_on = 1;
    dim++;
    break;
  case 2:
  case 3:
    red_on = 0;
    dim++;
  default:
    dim = 0;
  }
  led_changed = 1;
  led_update();
}

void dim75() {                       /* Dims leds to 75% */
  switch(dim) {
  case 0:
    red_on = 0;
    dim++;
    break;
  case 1:
  case 2:
  case 3:
    red_on = 1;
    dim++;
    break;
  default:
    dim = 0;
  }
  led_changed = 1;
  led_update();
}

void button2() {                   /* Dims light to 25%, 50% and 75% */
  static int select = 0;
  switch(select) {
    case 0:
      red_on = 1;
      led_update();
      select++;
      break;
    case 1:
      dim25();
      select++;
      break;
    case 2:
      dim50();
      select++;
      break;
    case 3:
      dim75();
      select = 0;
      break;
  }
  led_changed = 1;
  led_update();
}

void state_advance() {              /* State advance works w/ wdt */

  
  switch (state) {

  case 1:
    clearScreen(COLOR_BLACK);
    toggle_off();
    button1();
    break;

  case 2:
    buzzer_set_period(0);
    clearScreen(COLOR_SEA_GREEN);
    button2();
    break;
    
  case 3:
    buzzer_set_period(0);
    clearScreen(COLOR_WHITE);
    toggle_off();
    button3();
    break;

  case 4:
    buzzer_set_period(0);
    clearScreen(COLOR_BLACK);
    button4();
    break;

  default:
    clearScreen(COLOR_BLACK);
    drawChar11x16(30,50,'R',COLOR_WHITE,COLOR_BLACK);
    drawChar11x16(41,50,'e',COLOR_WHITE,COLOR_SEA_GREEN);
    drawChar11x16(52,50,'a',COLOR_WHITE,COLOR_HOT_PINK);
    drawChar11x16(63,50,'d',COLOR_WHITE,COLOR_CYAN);
    drawChar11x16(74,50,'y',COLOR_WHITE,COLOR_MAGENTA);
    drawChar11x16(85,50,'!',COLOR_WHITE,COLOR_GOLDENROD);
  }
}

void button1() {                                /* Button one plays a tune and writes a text */
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

void button4() {                             /* Moves diamond side to side */
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

  case 1:                              /* Moves diamond from left to right */
    x = x - 4;
    y = y + 4;
    if (x < 10) {
      move = 0;
    }
  }
}
