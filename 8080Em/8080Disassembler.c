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
			break;
		case 0x12: 
			sprintf(outputString, "%-7sD", "STAX");
			break;
		case 0x13: 
			sprintf(outputString, "%-7sD", "INX");
			break;
		case 0x14: 
			sprintf(outputString, "%-7sD", "INR");
			break;
		case 0x15: 
			sprintf(outputString, "%-7sD", "DCR");
			break;
		case 0x16: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sD,#$%02X", "MVI", byte1);
			break;
		case 0x17: 
			sprintf(outputString, "%-7sD", "RAL");
			break;
		case 0x18: 
			sprintf(outputString, "--");
			break;
		case 0x19: 
			sprintf(outputString, "%-7sD", "DAD");
			break;
		case 0x1a: 
			sprintf(outputString, "%-7sD", "LDAX");
			break;
		case 0x1b: 
			sprintf(outputString, "%-7sD", "DCX");
			break;
		case 0x1c: 
			sprintf(outputString, "%-7sE", "INR");
			break;
		case 0x1d: 
			sprintf(outputString, "%-7sE", "DCR");
			break;
		case 0x1e: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sE,#$%02X", "MVI", byte1);
			break;
		case 0x1f: 
			sprintf(outputString, "%-7s", "RAR");
			break;
		case 0x20: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x21: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sH,#$%02X%02X", "LXI", byte2, byte1);
			break;
		case 0x22: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s", "SHLD");
			break;
		case 0x23: 
			sprintf(outputString, "%-7sH", "INX");
			break;
		case 0x24: 
			sprintf(outputString, "%-7sH", "INR");
			break;
		case 0x25: 
			sprintf(outputString, "%-7sH", "DCR");
			break;
		case 0x26: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sH,#$%02X", "MVI", byte1);
			break;
		case 0x27: 
			sprintf(outputString, "%-7s", "DAA");
			break;
		case 0x28: 
			sprintf(outputString, "%-7s", "NOP");
			break;
		case 0x29: 
			sprintf(outputString, "%-7sH", "DAD");
			break;
		case 0x2a: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s,#$%02X%02X", "LHLD", byte2, byte1);
			break;
		case 0x2b: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sSP,#$%02X%02X", "LXI", byte2, byte1);
			break;
		case 0x2c: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s,#$%02X%02X", "STA", byte2, byte1);
			break;
		case 0x2d: 
			sprintf(outputString, "%-7sSP", "INX");
			break;
		case 0x2e: 
			sprintf(outputString, "%-7sM", "INR");
			break;
		case 0x2f: 
			sprintf(outputString, "%-7sM", "DCR");
			break;
		case 0x30: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sM,#$%02X", "MVI", byte1);
			break;
		case 0x31: 
			sprintf(outputString, "%-7s", "STC");
			break;
		case 0x32: 
			sprintf(outputString, "%-7s", "NOP");
			break;
		case 0x33: 
			sprintf(outputString, "%-7sSP", "DAD");
			break;
		case 0x34: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s,#$%02X%02X", "LDA", byte2, byte1);
			break;
		case 0x35: 
			sprintf(outputString, "%-7sSP", "DCX");
			break;
		case 0x36: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x37: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x38: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x39: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x3a: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x3b: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x3c: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x3d: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x3e: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x3f: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x40: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x41: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x42: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x43: 
			sprintf(outputString, "%-7s", "RIM");
			break;
		case 0x44: 
			sprintf(outputString, "%-7s", "RIM");
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