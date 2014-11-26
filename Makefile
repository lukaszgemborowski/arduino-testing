.PHONY: flash
.PHONY: clean

CXX := avr-gcc
HEX := avr-objcopy
DUDE := avrdude
FREQ := 16000000
BAUD := 57600
PORT := /dev/ttyUSB0
MCU_GCC := atmega328p
MCU_DUDE := m328p

main.elf : main.c
	$(CXX) -DF_CPU=$(FREQ) -g -mmcu=$(MCU_GCC) -Os -o $@ $<
	
main.hex : main.elf
	$(HEX) -j .text -j .data -O ihex $< $@
	
flash : main.hex
	$(DUDE) -p $(MCU_DUDE) -c arduino -P $(PORT) -b $(BAUD) -D -U flash:w:$<:i
	
clean :
	rm main.hex main.elf