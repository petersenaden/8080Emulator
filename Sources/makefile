#makefile for 8080 Emulator
CCom = g++
CFlags = -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wstrict-overflow=5 -Wwrite-strings -Waggregate-return -Wswitch-default -Wconversion
OutputFileWithOFlag = -o 8080Emu
OutputFile = 8080Emu
SIArgs = ./SI_ROM/invaders_h.rom 0x0 ./SI_ROM/invaders_g.rom 0x800 ./SI_ROM/invaders_f.rom 0x1000 ./SI_ROM/invaders_e.rom 0x1800

#targets
all: clearScr mainBuild clean

mainBuild: 8080Disassembler.o 8080Emulation.o 8080InstructionSet.o
	$(CCom) $(CFlags) $(OutputFileWithOFlag) 8080Disassembler.o 8080Emulation.o 8080InstructionSet.o

8080Disassembler.o: 8080Disassembler.cpp
	$(CCom) $(CFlags) -c 8080Disassembler.cpp
	
8080Emulation.o: 8080Emulation.cpp 8080Emulation.h
	$(CCom) $(CFlags) -c 8080Emulation.cpp
	
8080InstructionSet.o: 8080InstructionSet.cpp 8080InstructionSet.h
	$(CCom) $(CFlags) -c 8080InstructionSet.cpp

clean:
	rm -f 8080Emulation.o 8080Disassembler.o 8080InstructionSet.o 8080SpaceInvaders.o SIApp
	
clearScr:
	clear
	
run:
	./$(OutputFile) $(SIArgs)
	
8080SpaceInvaders.o: 8080SpaceInvaders.cpp
	$(CCom) -c 8080SpaceInvaders.cpp -Iusr/include/
	
runSI: 8080SpaceInvaders.o 8080Disassembler.o 8080Emulation.o 8080InstructionSet.o
	$(CCom) 8080SpaceInvaders.o 8080Disassembler.o 8080Emulation.o 8080InstructionSet.o -o SIApp -lsfml-graphics -lsfml-window -lsfml-system
	./SIApp $(SIArgs)
