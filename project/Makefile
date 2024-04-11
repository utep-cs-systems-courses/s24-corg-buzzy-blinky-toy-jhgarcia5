COMMON_OBJECTS = main.o
CPU = msp430g2553
CFLAGS = -mmcu=${CPU} -I ./h
LDFLAGS = -L/opt/ti/msp430_gcc/include

CC = msp430-elf-gcc
AS = msp430-elf-as

all: led.elf

led.elf: ${COMMON_OBJECTS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ ./lib/libTimer.a

load: led.elf
	msp430loader.sh led.elf

clean:
	rm -f *.o *.elf

main.o: led.h

wdInterruptHandler.o: led.h
