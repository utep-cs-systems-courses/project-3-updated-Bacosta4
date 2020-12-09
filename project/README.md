## Description
This toy flashes the LED's, plays buzzing sounds, and has a graphical LCD screen. Depending on which button is pressed.

## How to Use
The Makefile in this direcory contains rules to run the Makefile in the directory. Use **make all** in this directory to build all demo programs and the timer library. Once the programs are built, inside the project file you can **make all** to build the toy programs and to load the program onto the MSP430 by changing into the corresponding demo directory and using **make load**.

You may use **mspdebug rf2500 "erase"** to clear a program from the MSP430.

## Button Functions:
The green board contains 4 buttons (s1-s4). Each button contains a different method.
- S1: This will toggle green led and turns screen black & plays a tune and shoews txt
- S2: This will turn the screen to green and dims lights
- S3: This will create a diamond that will grow in size
- S4: This will create a diamond the move left to right and vise versa.
