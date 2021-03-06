#include<stdlib.h>
#include<limits.h>
#include<windows.h>
#include<stdio.h>

#ifndef INSTRUCTIONSET8080
#define INSTRUCTIONSET8080
#include "8080InstructionSet.h"
#endif

void UnimplementedInstruction(struct State8080* stt)
{
	unsigned char *currOp = &(stt->memory[stt->pc]);
	printf("PC: 0x%02X\t", stt->pc);
	printf("Operation: 0x%02X\n", *currOp);
	// FIXME: output to log file
	printf("UNIMPLEMENTED INSTRUCTION\n");
	exit(1);
}

/* 
  To avoid dereferencing a null pointer, we'll just keep the secondByte to be a value variable.
  Also, I'm implementing the AC and C flags by hand because implementing the instructions here
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
		else
		{
			stt->sf.s = 0;
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
		stt->sf.p = (totalOdds % 2 == 0);
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
	++numberToUse;
	*byteOne = ((unsigned char)(numberToUse >> 8));
	*byteTwo = ((unsigned char)numberToUse);
}

// Probably busted based on the AC flag
void INRInstruction(struct State8080* stt, unsigned char* byteOne)
{
	++(*byteOne);
	CheckFlags(stt, (*byteOne), true, true, true);
	//// Carry flag
	//if ((*byteOne) == 0)
	//{
	//	stt->sf.cy = 1;
	//}
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
	//// Carry flag
	//if (1 > (*byteOne))
	//{
	//	stt->sf.cy = 1;
	//}
	(*byteOne) -= 1;
	CheckFlags(stt, (*byteOne), true, true, true);
	// check endianness
	// Only way AC can be set if is LS 4 bits are zero. 
	bool flipACFlag = ((*byteOne) & 0xF) > 0;
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
	(*byteTwo) = (unsigned char)(additiveResult & 0b11111111);
	(*byteOne) = (unsigned char)(additiveResult >> 8);
	
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
	addressToUse = (unsigned short int)(addressToUse | (*byteTwo));
	*destByte = stt->memory[addressToUse];
}

void DCXInstruction(unsigned char* byteOne, unsigned char* byteTwo)
{
	// FIXME: check endianness
	unsigned short int numberToUse = 0;
	numberToUse = (unsigned short int)(*byteOne);
	numberToUse = (unsigned short int)(numberToUse << 8);
	numberToUse = (unsigned short int)(numberToUse + (*byteTwo));
	numberToUse = (unsigned short int)(numberToUse + 0b1111111111111111);
	(*byteOne) = (unsigned char)(numberToUse & 0xFF);
	(*byteTwo) = (unsigned char)(numberToUse >> 8);
}

void RRCInstruction(struct State8080* stt, unsigned char* byteOne)
{
	unsigned char zeroBit = ((*byteOne) & 1);
	stt->sf.cy = zeroBit;
	zeroBit = ((unsigned char)(zeroBit << 7) & 0b11111111);
	(*byteOne) = (unsigned char)((*byteOne) >> 1);
	(*byteOne) = (*byteOne) & zeroBit;
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
	// printf("Unimplemented Instruction - DAA");
	// exit(0);
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
	//unsigned char *currOperation = &(stt->memory[stt->pc]);
	unsigned short int addressToUse = (unsigned short)((stt->memory[stt->pc + 2] << 8) | stt->memory[stt->pc + 1]);
	// addressToUse = (unsigned short int)(*(currOperation + 1));
	// addressToUse = (unsigned short int)(addressToUse << 8);
	// addressToUse = (unsigned short int)(addressToUse + (*(currOperation + 2)));
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
	(*charToManipulate) = (unsigned char)((*charToManipulate) + 0b11111111);
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
	addressToUse = (unsigned short int)(addressToUse | (stt->l));
	unsigned char* charToManipulate = &(stt->memory[addressToUse]);
	unsigned char charToPersist = stt->memory[stt->pc + 1];
	*(charToManipulate) = charToPersist;
	stt->pc++;
}

void LDAInstruction(struct State8080* stt)
{
	unsigned char highByteAddress = stt->memory[stt->pc + 2];
	unsigned char lowByteAddress = stt->memory[stt->pc + 1];
	unsigned short int addressToUse = 0;
	addressToUse = (unsigned short int)(highByteAddress);
	addressToUse = (unsigned short int)(addressToUse << 8);
	addressToUse = (unsigned short int)(addressToUse + (lowByteAddress));
	//fprintf(stdout, "AddressToUse: 0x%02X\n", addressToUse);
	unsigned char charToManipulate = stt->memory[addressToUse];
	stt->a = charToManipulate;
	stt->pc++;
	stt->pc++;
}

void HLTInstruction()
{
	Sleep(50000);
}

void ADDInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* byteThree)
{
	(*byteOne) = (unsigned char)((*byteTwo) + (*byteThree));
	CheckFlags(stt, (*byteOne), true, true, true);
	if ((0xFF - (*byteTwo)) < (*byteThree))
	{
		stt->sf.cy = true;
	}
	unsigned char maskedByteTwo = (unsigned char)((*byteTwo) & 0b1111);
	unsigned char maskedByteThree = (unsigned char)((*byteThree) & 0b1111);
	if ((maskedByteTwo + maskedByteThree) > 0b1111)
	{
		stt->sf.ac = true;
	}
}

void ADCInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* byteThree)
{
	unsigned char intermediateValue = (unsigned char)(*byteThree);
	if (stt->sf.cy)
	{
		++(intermediateValue);
	}
	(*byteOne) = (unsigned char)((*byteTwo) + intermediateValue);
	CheckFlags(stt, (*byteOne), true, true, true);
	if ((0xFF - (*byteTwo)) < intermediateValue)
	{
		stt->sf.cy = true;
	}
	unsigned char maskedByteTwo = (unsigned char)((*byteTwo) & 0b1111);
	unsigned char maskedByteThree = (unsigned char)(intermediateValue & 0b1111);
	if ((maskedByteTwo + maskedByteThree) > 0b1111)
	{
		stt->sf.ac = true;
	}
}

void ACIInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{
	unsigned char* byteThree = &(stt->memory[stt->pc + 1]);
	unsigned char intermediateValue = (unsigned char)(*byteThree);
	if (stt->sf.cy)
	{
		++(intermediateValue);
	}
	(*byteOne) = (unsigned char)((*byteTwo) + intermediateValue);
	CheckFlags(stt, (*byteOne), true, true, true);
	if ((0xFF - (*byteTwo)) < intermediateValue)
	{
		stt->sf.cy = true;
	}
	unsigned char maskedByteTwo = (unsigned char)((*byteTwo) & 0b1111);
	unsigned char maskedByteThree = (unsigned char)(intermediateValue & 0b1111);
	if ((maskedByteTwo + maskedByteThree) > 0b1111)
	{
		stt->sf.ac = true;
	}
	stt->pc++;
}

void SUBInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* byteThree)
{
	unsigned char intermediateValue = (unsigned char)((~(*byteThree)) + 1);
	(*byteOne) = (unsigned char)((*byteTwo) + intermediateValue);
	CheckFlags(stt, (*byteOne), true, true, true);
	if ((0xFF - (*byteTwo)) < intermediateValue)
	{
		stt->sf.cy = true;
	}
	unsigned char maskedByteTwo = (unsigned char)((*byteTwo) & 0b1111);
	unsigned char maskedByteThree = (unsigned char)(intermediateValue & 0b1111);
	if ((maskedByteTwo + maskedByteThree) > 0b1111)
	{
		stt->sf.ac = true;
	}
}

void SUIInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{
	unsigned char* byteThree = &(stt->memory[stt->pc + 1]);
	unsigned char intermediateValue = (unsigned char)((~(*byteThree)) + 1);
	(*byteOne) = (unsigned char)((*byteTwo) + intermediateValue);
	CheckFlags(stt, (*byteOne), true, true, true);
	if ((0xFF - (*byteTwo)) < intermediateValue)
	{
		stt->sf.cy = true;
	}
	unsigned char maskedByteTwo = (unsigned char)((*byteTwo) & 0b1111);
	unsigned char maskedByteThree = (unsigned char)(intermediateValue & 0b1111);
	if ((maskedByteTwo + maskedByteThree) > 0b1111)
	{
		stt->sf.ac = true;
	}
	stt->pc++;
}

void SBBInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* byteThree)
{
	unsigned char intermediateValue = (unsigned char)((~(*byteThree)) + 1);
	if (stt->sf.cy)
	{
		intermediateValue = (unsigned char)(intermediateValue + 0b11111111);
	}
	(*byteOne) = (unsigned char)((*byteTwo) + intermediateValue);
	CheckFlags(stt, (*byteOne), true, true, true);
	if ((0xFF - (*byteTwo)) < intermediateValue)
	{
		stt->sf.cy = true;
	}
	unsigned char maskedByteTwo = (unsigned char)((*byteTwo) & 0b1111);
	unsigned char maskedByteThree = (unsigned char)(intermediateValue & 0b1111);
	if ((maskedByteTwo + maskedByteThree) > 0b1111)
	{
		stt->sf.ac = true;
	}
}

void SBIInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{
	unsigned char* byteThree = &(stt->memory[stt->pc + 1]);
	unsigned char intermediateValue = (unsigned char)((~(*byteThree)) + 1);
	if (stt->sf.cy)
	{
		intermediateValue = (unsigned char)(intermediateValue + 0b11111111);
	}
	(*byteOne) = (unsigned char)((*byteTwo) + intermediateValue);
	CheckFlags(stt, (*byteOne), true, true, true);
	if ((0xFF - (*byteTwo)) < intermediateValue)
	{
		stt->sf.cy = true;
	}
	unsigned char maskedByteTwo = (unsigned char)((*byteTwo) & 0b1111);
	unsigned char maskedByteThree = (unsigned char)(intermediateValue & 0b1111);
	if ((maskedByteTwo + maskedByteThree) > 0b1111)
	{
		stt->sf.ac = true;
	}
	stt->pc++;
}

void ANAInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* byteThree)
{
	(*byteOne) = (unsigned char)((*byteTwo) & (*byteThree));
	CheckFlags(stt, (*byteOne), true, true, true);
	stt->sf.cy = false;
}

void XRAInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* byteThree)
{
	(*byteOne) = (unsigned char)((*byteTwo) ^ (*byteThree));
	CheckFlags(stt, (*byteOne), true, true, true);
	stt->sf.cy = false;
}

void XRIInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{
	unsigned char* byteThree = &(stt->memory[stt->pc + 1]);
	(*byteOne) = (unsigned char)((*byteTwo) ^ (*byteThree));
	CheckFlags(stt, (*byteOne), true, true, true);
	stt->sf.cy = false;
	stt->pc++;
}

void ORAInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* byteThree)
{
	(*byteOne) = (unsigned char)((*byteTwo) | (*byteThree));
	CheckFlags(stt, (*byteOne), true, true, true);
	stt->sf.cy = false;
}

void ORIInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{
	unsigned char* byteThree = &(stt->memory[stt->pc + 1]);
	(*byteOne) = (unsigned char)((*byteTwo) | (*byteThree));
	CheckFlags(stt, (*byteOne), true, true, true);
	stt->sf.cy = false;
	stt->pc++;
}

void CMPInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{
	unsigned char firstRegister = (*byteOne);
	unsigned char secondRegister = (unsigned char)((~(*byteTwo)) + 1);
	unsigned char result = (unsigned char)(firstRegister + secondRegister);
	CheckFlags(stt, (*byteOne), true, true, true);
	stt->sf.z = (firstRegister == (*byteTwo));
	stt->sf.cy = (char)(result >> 7);
	//do aux carry
}

void POPInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{
	(*byteOne) = stt->memory[stt->sp];
	(*byteTwo) = stt->memory[(stt->sp) + 1];
	++stt->sp;
	++stt->sp;
}

void JNZInstruction(struct State8080* stt)
{
	if (stt->sf.z == 0)
	{
		// unsigned char *currOperation = &(stt->memory[stt->pc]);
		// unsigned short int addressToUse = (unsigned short int)((currOperation[2] << 8) | currOperation[1]);
		// printf("%x", addressToUse);
		stt->pc = (short unsigned int)(((&(stt->memory[stt->pc]))[2] << 8) | (&(stt->memory[stt->pc]))[1]);
	}
	else
	{
		stt->pc++;
		stt->pc++;
		stt->pc++;
	}
}

void JNCInstruction(struct State8080* stt)
{
	if (stt->sf.cy == 0)
	{
		// unsigned char *currOperation = &(stt->memory[stt->pc]);
		// unsigned short int addressToUse = (unsigned short int)((currOperation[2] << 8) | currOperation[1]);
		// printf("%x", addressToUse);
		stt->pc = (short unsigned int)(((&(stt->memory[stt->pc]))[2] << 8) | (&(stt->memory[stt->pc]))[1]);
	}
	else
	{
		stt->pc++;
		stt->pc++;
		stt->pc++;
	}
}

void JCInstruction(struct State8080* stt)
{
	if (stt->sf.cy)
	{
		// unsigned char *currOperation = &(stt->memory[stt->pc]);
		// unsigned short int addressToUse = (unsigned short int)((currOperation[2] << 8) | currOperation[1]);
		// printf("%x", addressToUse);
		stt->pc = (short unsigned int)(((&(stt->memory[stt->pc]))[2] << 8) | (&(stt->memory[stt->pc]))[1]);
	}
	else
	{
		stt->pc++;
		stt->pc++;
		stt->pc++;
	}
}

void JPEInstruction(struct State8080* stt)
{
	if (stt->sf.p)
	{
		// unsigned char *currOperation = &(stt->memory[stt->pc]);
		// unsigned short int addressToUse = (unsigned short int)((currOperation[2] << 8) | currOperation[1]);
		// printf("%x", addressToUse);
		stt->pc = (short unsigned int)(((&(stt->memory[stt->pc]))[2] << 8) | (&(stt->memory[stt->pc]))[1]);
	}
	else
	{
		stt->pc++;
		stt->pc++;
		stt->pc++;
	}
}

void JMInstruction(struct State8080* stt)
{
	if (stt->sf.s)
	{
		// unsigned char *currOperation = &(stt->memory[stt->pc]);
		// unsigned short int addressToUse = (unsigned short int)((currOperation[2] << 8) | currOperation[1]);
		// printf("%x", addressToUse);
		stt->pc = (short unsigned int)(((&(stt->memory[stt->pc]))[2] << 8) | (&(stt->memory[stt->pc]))[1]);
	}
	else
	{
		stt->pc++;
		stt->pc++;
		stt->pc++;
	}
}

void JPInstruction(struct State8080* stt)
{
	if (stt->sf.s == 0)
	{
		// unsigned char *currOperation = &(stt->memory[stt->pc]);
		// unsigned short int addressToUse = (unsigned short int)((currOperation[2] << 8) | currOperation[1]);
		// printf("%x", addressToUse);
		stt->pc = (short unsigned int)(((&(stt->memory[stt->pc]))[2] << 8) | (&(stt->memory[stt->pc]))[1]);
	}
	else
	{
		stt->pc++;
		stt->pc++;
		stt->pc++;
	}
}

void CPInstruction(struct State8080* stt)
{
	if (stt->sf.s == 0)
	{
		// unsigned char *currOperation = &(stt->memory[stt->pc]);
		// unsigned short int addressToUse = (unsigned short int)((currOperation[2] << 8) | currOperation[1]);
		// printf("%x", addressToUse);
		stt->pc = (short unsigned int)(((&(stt->memory[stt->pc]))[2] << 8) | (&(stt->memory[stt->pc]))[1]);
	}
	else
	{
		stt->pc++;
		stt->pc++;
		stt->pc++;
	}
}

void JPOInstruction(struct State8080* stt)
{
	if (stt->sf.p == 0)
	{
		// unsigned char *currOperation = &(stt->memory[stt->pc]);
		// unsigned short int addressToUse = (unsigned short int)((currOperation[2] << 8) | currOperation[1]);
		// printf("%x", addressToUse);
		stt->pc = (short unsigned int)(((&(stt->memory[stt->pc]))[2] << 8) | (&(stt->memory[stt->pc]))[1]);
	}
	else
	{
		stt->pc++;
		stt->pc++;
		stt->pc++;
	}
}

void JZInstruction(struct State8080* stt)
{
	if (stt->sf.z)
	{
		// unsigned char *currOperation = &(stt->memory[stt->pc]);
		// unsigned short int addressToUse = (unsigned short int)((currOperation[2] << 8) | currOperation[1]);
		// printf("%x", addressToUse);
		stt->pc = (short unsigned int)(((&(stt->memory[stt->pc]))[2] << 8) | (&(stt->memory[stt->pc]))[1]);
	}
	else
	{
		stt->pc++;
		stt->pc++;
		stt->pc++;
	}
}

void JMPInstruction(struct State8080* stt)
{
	unsigned char *currOperation = &(stt->memory[stt->pc]);
	unsigned short int addressToUse = (short unsigned int)((currOperation[2] << 8) | currOperation[1]);
	stt->pc = addressToUse;
}

void PUSHInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{
	unsigned short firstAddress = (short unsigned int)(stt->sp - 2);
	unsigned short secondAddress = (short unsigned int)(stt->sp - 1);
	stt->memory[firstAddress] = (*byteOne);
	stt->memory[secondAddress] = (*byteTwo);
	stt->sp--;
	stt->sp--;
}

void ADIInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{			
	unsigned char byteToUse = stt->memory[stt->pc + 1];
	(*byteOne) = (unsigned char)((*byteTwo) + (byteToUse));
	CheckFlags(stt, (*byteOne), true, true, true);
	if ((0xFF - (*byteTwo)) < (byteToUse))
	{
		stt->sf.cy = true;
	}
	unsigned char maskedByteTwo = (unsigned char)((*byteTwo) & 0b1111);
	unsigned char maskedByteThree = (unsigned char)((byteToUse) & 0b1111);
	if ((maskedByteTwo + maskedByteThree) > 0b1111)
	{
		stt->sf.ac = true;
	}
	stt->pc++;
}

void RETInstruction(struct State8080* stt)
{
	stt->pc = (unsigned short)((stt->memory[stt->sp + 1] << 8) | stt->memory[stt->sp]);
	stt->sp++;
	stt->sp++;
}

// 8080 manual doc is weak on this instruction
void CALLInstruction(struct State8080* stt)
{
 	stt->memory[stt->sp - 1] = (unsigned char)(((stt->pc+2) >> 8) & 0xff);
	stt->memory[stt->sp - 2] = (unsigned char)((stt->pc+2) & 0b11111111);
	stt->pc = (unsigned short)((( stt->memory[stt->pc + 2]) << 8) | (stt->memory[stt->pc + 1]));
	stt->sp--;
	stt->sp--;
}

// 8080 manual doc is weak on this instruction
void CALLDirectInstruction(struct State8080* stt, unsigned short addressToCallTo )
{
 	stt->memory[stt->sp - 1] = (unsigned char)(((stt->pc+2) >> 8) & 0xff);
	stt->memory[stt->sp - 2] = (unsigned char)((stt->pc+2) & 0b11111111);
	stt->pc = addressToCallTo;
	stt->sp--;
	stt->sp--;
}

void ANIInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo)
{
	unsigned char dataToAnd = stt->memory[stt->pc + 1];
	(*byteOne) = (unsigned char)((*byteTwo) & (dataToAnd));
	CheckFlags(stt, (*byteOne), true, true, true);
	stt->sf.cy = false;
	stt->pc++;
}

void EXCHANGEInstruction(unsigned char* byteOne, unsigned char* byteTwo, unsigned char* byteThree, unsigned char* byteFour)
{
	unsigned char firstByte = (*byteOne);
	unsigned char secondByte = (*byteTwo);
	unsigned char thirdByte = (*byteThree);
	unsigned char fourthByte = (*byteFour);
	(*byteOne) = secondByte;
	(*byteTwo) = firstByte;
	(*byteThree) = fourthByte;
	(*byteFour) = thirdByte;
}

void POPPSWInstruction(struct State8080* stt)
{
	unsigned char stackPointerMemoryValue = stt->memory[stt->sp];
	unsigned char stackPointerMemoryValueForA = stt->memory[stt->sp + 1];
	stt->sf.z = (stackPointerMemoryValue >> 7) & 1;
	stt->sf.s = (stackPointerMemoryValue >> 6) & 1;
	stt->sf.p = (stackPointerMemoryValue >> 5) & 1;
	stt->sf.cy = (stackPointerMemoryValue >> 4) & 1;
	stt->sf.ac = (stackPointerMemoryValue >> 3) & 1;
	// might fail depending on how padding was treated
	// in the original 8080 spec
	stt->a = stackPointerMemoryValueForA;
	++stt->sp;
	++stt->sp;
}

void PUSHPSWInstruction(struct State8080* stt)
{
	unsigned char aggregateFlags =(unsigned char)(
		(stt->sf.z << 7) |
		(stt->sf.s << 6) |
		(stt->sf.p << 5) |
		(stt->sf.cy << 4) |
		(stt->sf.ac << 3));
	stt->memory[stt->sp - 2] = aggregateFlags;
	stt->memory[stt->sp - 1] = stt->a;
	--(stt->sp);
	--(stt->sp);
}

void EIInstruction(struct State8080* stt)
{
	stt->interrupt_enable = true;
}

void DIInstruction(struct State8080* stt)
{
	stt->interrupt_enable = false;
}

void CPIInstruction(struct State8080* stt, unsigned char* byteOne)
{
	unsigned char byteTwo = stt->memory[stt->pc + 1];
	unsigned char firstRegister = (*byteOne);
	unsigned char secondRegister = (unsigned char)((~(byteTwo)) + 1);
	unsigned char result = (unsigned char)(firstRegister + secondRegister);
	CheckFlags(stt, result, true, true, true);
	stt->sf.z = (firstRegister == (byteTwo));
	stt->sf.cy = (char)(result >> 7);
	//do aux carry
	
	(stt->pc)++;
}

void SPHLInstruction(struct State8080* stt)
{
	stt->sp = (unsigned short)((stt->h << 8) | stt->l);
}

void INInstruction(struct State8080* stt, unsigned char* byteOne)
{
	unsigned short parameterOne = stt->interrupt_value;
	stt->interrupt_value = 0;	
	(*byteOne) = ProcessInput((unsigned char)(parameterOne));
	stt->pc++;
}

void OUTInstruction(struct State8080* stt)
{
	unsigned char parameterOne = stt->memory[stt->pc + 1];	
	ProcessOutput(parameterOne);
	stt->pc++;
}

void PCHLInstruction(struct State8080* stt)
{
	unsigned short newPC = (unsigned short)((stt->h << 8) | stt->l);
	stt->pc = newPC;
}

unsigned char ProcessInput(unsigned char byteOne)
{
	return byteOne;
}

unsigned char ProcessOutput(unsigned char byteOne)
{
	return byteOne;
}

void PerformInterrupt(struct State8080* stt, int interruptId)
{
	unsigned short firstAddress = (short unsigned int)(stt->sp - 2);
	unsigned short secondAddress = (short unsigned int)(stt->sp - 1);
	stt->memory[firstAddress] = (unsigned char)(stt->pc >> 8);
	stt->memory[secondAddress] = (unsigned char)(stt->pc);
	stt->sp--;
	stt->sp--;
	
	//The setup of the 8080 is such that the interrupts are always
	//multiples of 8.
	stt->pc = (unsigned short)(interruptId * 8);
}




