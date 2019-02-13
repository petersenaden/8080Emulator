#include<stdlib.h>
#include<limits.h>

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

/* 
  To avoid dereferencing a null pointer, we'll just keep the secondByte to be a value variable.
  Also, I'm impelmenting the AC and C flags by hand because implementing the instructions here
  would cause double the work for virtually every operation.
 */
void CheckFlags(struct State8080* stt, unsigned char checkByte, bool checkSignFlag, bool checkZeroFlag, bool checkParityFlag)
{
	//(n >> k) & 1
	if (checkSignFlag)
	{
		//check this for bit 7
		if ((((checkByte) >> 7) & 1) == 1)
		{
			stt->sf.s = 1;
		}
	}
	if (checkZeroFlag)
	{
		stt->sf.z = (checkByte == 0);
	}
	if (checkParityFlag)
	{
		int totalOdds = 0;
		for (unsigned int i = 0; i < (sizeof(checkByte) * 8); i++)
		{
			if ((((checkByte) >> i) & 1) == 1)
			{
				totalOdds++;
			}
		}
		stt->sf.p = (totalOdds % 2 == 1);
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
	// FIXME: check endianness
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(*byteOne);
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (*byteTwo));
	addressToUse++;
	(*byteOne) = (unsigned char)(addressToUse & 0xFF);
	(*byteTwo) = (unsigned char)(addressToUse >> 8);
}

// Probably busted based on the AC flag
void INRInstruction(struct State8080* stt, unsigned char* byteOne)
{
	(*byteOne)++;
	CheckFlags(stt, (*byteOne), true, true, true);
	// Carry flag
	if ((*byteOne) == 0)
	{
		stt->sf.cy = 1;
	}
	bool flipACFlag = true;
	// check endianness
	for (unsigned int i = 0; i < 4; i++)
	{
			if ((((*byteOne) >> i) & 1) != 1)
			{
				flipACFlag = false;
			}
	}
	if (flipACFlag)
	{
		stt->sf.ac = 1;
	}
}

void DCRInstruction(struct State8080* stt, unsigned char* byteOne)
{
	// Carry flag
	if (1 > (*byteOne))
	{
		stt->sf.cy = 1;
	}
	(*byteOne)--;
	CheckFlags(stt, (*byteOne), true, true, true);
	// check endianness
	// Only way AC can be set if is LS 4 bits are zero. 
	bool flipACFlag = true;
	for (unsigned int i = 0; i < 4; i++)
	{
			if ((((*byteOne) >> i) & 1) != 0)
			{
				flipACFlag = false;
			}
	}
	if (flipACFlag)
	{
		stt->sf.ac = 1;
	}
}

















