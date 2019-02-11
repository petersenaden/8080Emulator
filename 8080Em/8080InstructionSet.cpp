#include<stdlib.h>

#ifndef INSTRUCTIONSET8080
#define INSTRUCTIONSET8080
#include "8080InstructionSet.h"
#endif

void UnimplementedInstruction(struct State8080* stt)
{
	(stt->pc)--;
	// FIXME: sp might need to be reversed
	// FIXME: output to log file
	exit(1);
}

void CheckFlags(unsigned char* resultByte, bool checkCarryFlag, bool checkACFlag, bool checkSignFlag, bool checkZeroFlag, bool checkParityFlag)
{
	if (checkCarryFlag)
	{
	}
	if (checkACFlag)
	{
	}
	if (checkSignFlag)
	{
	}
	if (checkZeroFlag)
	{
	}
	if (checkParityFlag)
	{
	}
	
}

void LXIInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{
	unsigned char *currOperation = &(stt->memory[stt->pc]);
	*byteOne = currOperation[2];
	*byteTwo = currOperation[1];
	stt->pc++;
	stt->pc++;
}

void STAXInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* destByte)
{
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(*byteOne);
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (*byteTwo));
	*destByte = stt->memory[addressToUse];
}

void INXInstruction(unsigned char* byteOne, unsigned char* byteTwo)
{
	// check endianness
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(*byteOne);
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (*byteTwo));
	addressToUse++;
	(*byteOne) = (unsigned char)(addressToUse & 0xFF);
	(*byteTwo) = (unsigned char)(addressToUse >> 8);
}

void INRInstruction(unsigned char* byteOne)
{
	(*byteOne)++;
	CheckFlags
	
}


















