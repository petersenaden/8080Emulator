#makefile for 8080 Emulator
CCom = g++
CFlags = -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wswitch-default -Wconversion
OutputFile = -o 8080Emu

#targets
all: clearScr mainBuild clean

mainBuild: 8080Disassembler.o 8080Emulation.o 8080InstructionSet.o
	$(CCom) $(CFlags) $(OutputFile) 8080Disassembler.o 8080Emulation.o 8080InstructionSet.o

8080Disassembler.o: 8080Disassembler.cpp
	$(CCom) $(CFlags) -c 8080Disassembler.cpp
	
8080Emulation.o: 8080Emulation.cpp 8080Emulation.h
	$(CCom) $(CFlags) -c 8080Emulation.cpp
	
8080InstructionSet.o: 8080InstructionSet.cpp 8080InstructionSet.h
	$(CCom) $(CFlags) -c 8080InstructionSet.cpp

clean:
	rm -f 8080Emulation.o 8080Disassembler.o 8080InstructionSet.o
	
clearScr:
	clear