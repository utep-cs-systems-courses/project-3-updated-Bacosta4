#include <msp430.h>
#include "led.h"

void button2() {                   /* Dims light to 25%, 50% and 75% */
  static char select = 0;
  switch(select) {
  case 0:
    toggle_on();
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

  default:
    break;
  }
}
