#include<stdio.h>
#include<stdlib.h>
#include<string.h>

unsigned char GetNextByte(FILE* rom);

void OutputByte(char* outputString)
{
	printf("%s\n", outputString);
}

char* ProcessByte(unsigned char currByte, FILE* rom, int* programCounter)
{
	// [] notation only stays on stack for duration of function
	unsigned char byte1;
	unsigned char byte2;
	char *programCounterPrefixString = malloc(200 * sizeof(char));
	sprintf(programCounterPrefixString, "%04x ", *programCounter);
	char *outputString = malloc(100 * sizeof(char));
	switch(currByte)
	{
		case 0x00: 
			sprintf(outputString, "NOP");
			break;
		case 0x01: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sB,#$%02X%02X", "LXI", byte2, byte1);
			break;
		case 0x02: 
			sprintf(outputString, "%-7sB", "STAX");
			break;
		case 0x03: 
			sprintf(outputString, "%-7sB", "INX");
			break;
		case 0x04: 
			sprintf(outputString, "%-7sB", "INR");
			break;
		case 0x05: 
			sprintf(outputString, "%-7sB", "DCR");
			break;
		case 0x06: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sB,#$%02X", "MVI", byte1);
			break;
		case 0x07: 
			sprintf(outputString, "%-7s", "RLC");
			break;
		case 0x08: 
			sprintf(outputString, "--");
			break;
		case 0x09: 
			sprintf(outputString, "%-7sB", "DAD");
			break;
		case 0x0a: 
			sprintf(outputString, "%-7sB", "LDAX");
			break;
		case 0x0b: 
			sprintf(outputString, "%-7sB", "DCX");
			break;
		case 0x0c: 
			sprintf(outputString, "%-7sC", "INR");
			break;
		case 0x0d: 
			sprintf(outputString, "%-7sC", "DCR");
			break;
		case 0x0e: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sC,#$%02X", "MVI", byte1);
			break;
		case 0x0f: 
			sprintf(outputString, "%-7s", "RRC");
			break;
		case 0x10: 
			sprintf(outputString, "--");
			break;
		case 0x11: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sD,#$%02X%02X", "LXI", byte2, byte1);
			break;//here
		case 0x12: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x13: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x14: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x15: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x16: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x17: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x18: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x19: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x1a: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x1b: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x1c: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x1d: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x1e: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x1f: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x20: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		default:
			sprintf(outputString, "UNKNOWN OP");
			break;
	}
	(*programCounter)++;
	strncat_s(programCounterPrefixString, 200, outputString, 100);
	return programCounterPrefixString;
}	

unsigned char GetNextByte(FILE* rom)
{
	unsigned char returnVar;
	if (feof(rom))
	{
		return returnVar;
	}
	int readByte = fgetc(rom);
	returnVar = (unsigned char)readByte;
	return returnVar;
}

int main(int argc, char**argv)
{
	int fileSizeInChars = 0;
	int programCounter = 0;
	FILE* rom;
	if (fopen_s(&rom, argv[1], "rb") != 0)
	{
		exit(EXIT_FAILURE);
	}
	
	fseek(rom, 0, SEEK_END);
	fileSizeInChars = ftell(rom);
	fseek(rom, 0, SEEK_SET);
	for(;;)
	{
		if (feof(rom))
		{
			break;
		}
		unsigned char currByte = GetNextByte(rom);
		programCounter++;
		char* outputString = ProcessByte(currByte, rom, &programCounter);
		OutputByte(outputString);
	}

	fclose(rom);
    return 0;
}