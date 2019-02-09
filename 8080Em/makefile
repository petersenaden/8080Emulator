#makefile for 8080 Emulator
CCom = gcc
CFlags = -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wswitch-default -Wconversion
OutputFile = -o 8080Emu

#targets
all: mainBuild clean

mainBuild: 8080Disassembler.o 8080Emulation.o
	$(CCom) $(CFlags) $(OutputFile) 8080Disassembler.o 8080Emulation.o

8080Disassembler.o: 8080Disassembler.c
	$(CCom) $(CFlags) -c 8080Disassembler.c
	
8080Emulation.o: 8080Emulation.c 8080Emulation.h
	$(CCom) $(CFlags) -c 8080Emulation.c

clean:
	rm -f 8080Emulation.o 8080Disassembler.o