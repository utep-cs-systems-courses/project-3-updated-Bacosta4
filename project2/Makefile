# makfile configuration
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all:wakedemo.elf

#additional rules for files
wakedemo.elf: ${COMMON_OBJECTS} wakedemo.o wdt_handler.o led.o statemachine.o buzzer.o p2_interrupt_handler.o switches.o button2.o compare.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: wakedemo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

led.o: led.c led.h
statemachine.o: buzzer.h led.h statemachine.h

buzzer.o: buzzer.h buzzer.c
compare.o: compare.s
