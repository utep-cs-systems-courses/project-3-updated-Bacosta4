## Description
This directory contains demo programs that demonstrate basic I/O using timer and button interrupts.

Program | Description
------- | -----------
Blink   | Uses timer interrupts to flash the LEDs in a silly pattern.
Button  | Uses interrupts to detect when a switch is pressed or released.
Buzzer  | Emits a single continuous note from the buzzer.

## How to Use

The Makefile in this direcory contains rules to run the Makefile in each demo directory. Use **make** in this directory to build all demo programs and the timer library. Once the programs are built, you can load the program onto the MSP430 by changing into the corresponding demo directory and using **make load**.

You may use **mspdebug rf2500 "erase"** to clear a program from the MSP430.

## Button Functions:
The green board contains 4 buttons (s1-s4). Each button contains a different method.
- S1: This will toggle between red and green.
- S2: This will pay a siren, hold toggle to go from high to low buzzer ho
- S3: This will dim the led while hold.
- S4: This will turn both green and red led and turn off the buzzer.
