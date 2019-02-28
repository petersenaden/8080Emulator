#include<stdlib.h>
#include<limits.h>
#include<stdio.h>

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
	(stt->memory[addressToUse]) = (*destByte);
}

void INXInstruction(unsigned char* byteOne, unsigned char* byteTwo)
{
	// FIXME: check endianness
	unsigned short int numberToUse = 0;
	numberToUse = (unsigned short int)(*byteOne);
	numberToUse = (unsigned short int)(numberToUse << 8);
	numberToUse = (unsigned short int)(numberToUse + (*byteTwo));
	numberToUse++;
	(*byteOne) = (unsigned char)(numberToUse & 0xFF);
	(*byteTwo) = (unsigned char)(numberToUse >> 8);
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

void MVIInstruction(struct State8080* stt, unsigned char* byteOne)
{
	unsigned char *currOperation = &(stt->memory[stt->pc]);
	*byteOne = currOperation[1];
	stt->pc++;
}

void RLCInstruction(struct State8080* stt, unsigned char* byteOne)
{
	unsigned char seventhBit = (((*byteOne) >> 7) & 1);
	(*byteOne) = (unsigned char)((*byteOne) << 1);
	(*byteOne) = (*byteOne) | seventhBit;
	stt->sf.cy = seventhBit;
}

void DADInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* byteThree, unsigned char* byteFour)
{
	// might have promotion issues
	unsigned short int firstCompositeRegister = 0;
	firstCompositeRegister = (unsigned short int)(*byteOne);
	firstCompositeRegister = (unsigned short int)(firstCompositeRegister << 8);
	firstCompositeRegister = (unsigned short int)(firstCompositeRegister + (*byteTwo));
	
	unsigned short int secondCompositeRegister = 0;
	secondCompositeRegister = (unsigned short int)(*byteThree);
	secondCompositeRegister = (unsigned short int)(secondCompositeRegister << 8);
	secondCompositeRegister = (unsigned short int)(secondCompositeRegister + (*byteFour));
	
	unsigned short additiveResult = (unsigned short )(firstCompositeRegister + secondCompositeRegister);
	(*byteTwo) = (unsigned char)(additiveResult & 0b1111);
	(*byteOne) = (unsigned char)(additiveResult >> 4);
	
	int carryCheck = firstCompositeRegister + secondCompositeRegister;
	if (carryCheck > USHRT_MAX)
	{
		stt->sf.cy = (carryCheck > USHRT_MAX);
	}
}

void LDAXInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* destByte)
{
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(*byteOne);
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (*byteTwo));
	*destByte = stt->memory[addressToUse];
}

void DCXInstruction(unsigned char* byteOne, unsigned char* byteTwo)
{
	// FIXME: check endianness
	unsigned short int numberToUse = 0;
	numberToUse = (unsigned short int)(*byteOne);
	numberToUse = (unsigned short int)(numberToUse << 8);
	numberToUse = (unsigned short int)(numberToUse + (*byteTwo));
	numberToUse--;
	(*byteOne) = (unsigned char)(numberToUse & 0xFF);
	(*byteTwo) = (unsigned char)(numberToUse >> 8);
}

void RRCInstruction(struct State8080* stt, unsigned char* byteOne)
{
	unsigned char zeroBit = ((*byteOne) & 1);
	stt->sf.cy = zeroBit;
	(*byteOne) = (unsigned char)((*byteOne) >> 1);
	(*byteOne) = (*byteOne) & ((unsigned char)(zeroBit << 7));
}

void RALInstruction(struct State8080* stt, unsigned char* byteOne)
{
	unsigned char seventhBit = (((*byteOne) >> 7) & 1);
	(*byteOne) = (unsigned char)((*byteOne) << 1);
	(*byteOne) = (unsigned char)((*byteOne) | stt->sf.cy);
	stt->sf.cy = seventhBit;
}

void RARInstruction(struct State8080* stt, unsigned char* byteOne)
{
	unsigned char seventhBit = (((*byteOne) >> 7) & 1);
	unsigned char zeroBit = ((*byteOne) & 1);
	(*byteOne) = (unsigned char)((*byteOne) >> 1);
	(*byteOne) = (*byteOne) & ((unsigned char)(seventhBit << 7));
	stt->sf.cy = zeroBit;
}

void DAAInstruction()
{
	printf("Unimplemented Instruction - DAA");
	exit(0);
}

void SHLDInstruction(struct State8080* stt, unsigned char* destByteOne, unsigned char* destByteTwo)
{
	unsigned char *currOperation = &(stt->memory[stt->pc]);
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(*(currOperation + 1));
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (*(currOperation + 2)));
	*destByteOne = stt->memory[addressToUse];
	*destByteTwo = stt->memory[addressToUse + 1];
	(stt->pc)++;
	(stt->pc)++;
}

void LHLDInstruction(struct State8080* stt, unsigned char* destByteOne, unsigned char* destByteTwo)
{
	unsigned char *currOperation = &(stt->memory[stt->pc]);
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(*(currOperation + 1));
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (*(currOperation + 2)));
	*destByteOne = stt->memory[addressToUse];
	*destByteTwo = stt->memory[addressToUse + 1];
	(stt->pc)++;
	(stt->pc)++;
}

void CMAInstruction(unsigned char* byteOne)
{
	// might be wrong
	(*byteOne) = (unsigned char)(~(*byteOne));
}

void STCInstruction(struct State8080* stt)
{
	stt->sf.cy = 1;
}

void CMCInstruction(struct State8080* stt)
{
	stt->sf.cy = !(stt->sf.cy);
}

void MOVInstruction(unsigned char* byteOne, unsigned char* byteTwo)
{
	(*byteOne) = (*byteTwo);
}

void STAInstruction(struct State8080* stt, unsigned char* byteOne)
{
	unsigned char *currOperation = &(stt->memory[stt->pc]);
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(*(currOperation + 1));
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (*(currOperation + 2)));
	stt->memory[addressToUse] = (*byteOne);
	(stt->pc)++;
	(stt->pc)++;
}

void INRMInstruction(struct State8080* stt)
{
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(stt->h);
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (stt->l));
	unsigned char* charToManipulate = &(stt->memory[addressToUse]);
	++(*charToManipulate);
	CheckFlags(stt, (*charToManipulate), true, true, true);
	// Carry flag
	if ((*charToManipulate) == 0)
	{
		stt->sf.cy = 1;
	}
	bool flipACFlag = true;
	// check endianness
	for (unsigned int i = 0; i < 4; i++)
	{
			if ((((*charToManipulate) >> i) & 1) != 1)
			{
				flipACFlag = false;
			}
	}
	if (flipACFlag)
	{
		stt->sf.ac = 1;
	}
}

void DCRMInstruction(struct State8080* stt)
{
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(stt->h);
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (stt->l));
	unsigned char* charToManipulate = &(stt->memory[addressToUse]);
	--(*charToManipulate);
	CheckFlags(stt, (*charToManipulate), true, true, true);
	// Carry flag
	if ((*charToManipulate) == 0)
	{
		stt->sf.cy = 1;
	}
	bool flipACFlag = true;
	// check endianness
	for (unsigned int i = 0; i < 4; i++)
	{
			if ((((*charToManipulate) >> i) & 1) != 1)
			{
				flipACFlag = false;
			}
	}
	if (flipACFlag)
	{
		stt->sf.ac = 1;
	}
}

void MVIMInstruction(struct State8080* stt)
{
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(stt->h);
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (stt->l));
	unsigned char* charToManipulate = &(stt->memory[addressToUse]);
	unsigned char charToPersist = stt->memory[stt->pc + 1];
	*(charToManipulate) = charToPersist;
	stt->pc++;
}

void LDAInstruction(struct State8080* stt)
{
	unsigned char highByteAddress = stt->memory[stt->sp + 1];
	unsigned char lowByteAddress = stt->memory[stt->sp + 2];
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(highByteAddress);
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (lowByteAddress));
	unsigned char charToManipulate = stt->memory[addressToUse];
	stt->a = charToManipulate;
	stt->pc++;
	stt->pc++;
}












