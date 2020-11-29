#ifndef stateMachine_included
#define stateMachine_included
#include "led.h"
#include "buzzer.h"
#include "switches.h"

void state_advance();

extern int state;

void dim25();
void dim50();
void dim75();

void state_advance();
void button1();
void button2();
void button3();
void button4();

#endif // included
