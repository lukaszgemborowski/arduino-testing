.PHONY: flash
.PHONY: clean
.PHONY: all

CXX := avr-gcc
HEX := avr-objcopy
DUDE := avrdude
FREQ := 16000000
BAUD := 57600
PORT := /dev/ttyUSB0
MCU_GCC := atmega328p
MCU_DUDE := m328p

main.o : main.c
	$(CXX) -DF_CPU=$(FREQ) -g -mmcu=$(MCU_GCC) -Os -o $@ -c $<

usart.o : usart.c
	$(CXX) -DF_CPU=$(FREQ) -g -mmcu=$(MCU_GCC) -Os -o $@ -c $<

example.elf : main.o usart.o
	$(CXX) main.o usart.o -g -mmcu=$(MCU_GCC) -o example.elf

example.hex : example.elf
	$(HEX) -j .text -j .data -O ihex $< $@

flash : example.hex
	$(DUDE) -p $(MCU_DUDE) -vvvv -c arduino -P $(PORT) -b $(BAUD) -D -U flash:w:$<:i

all : example.hex

clean :
	rm -f example.hex example.elf main.o usart.o