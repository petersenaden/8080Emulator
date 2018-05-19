#include<stdio.h>
#include<stdlib.h>
#include<string.h>

unsigned char GetNextByte(FILE* rom);

void OutputByte(char* outputString)
{
	printf("%s\n", outputString);
}

char* ProcessByte(unsigned char currByte, FILE* rom)
{
	// [] notation only stays on stack for duration of function
	char *outputString = malloc(100 * sizeof(char));
	switch(currByte)
	{
		case 0x00: 
			sprintf(outputString, "NOP");
			break;
		case 0x01: 
			sprintf(outputString, "LXI    B#$%02X %02X", GetNextByte(rom), GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX   B");
			break;
		case 0x03: 
			sprintf(outputString, "INX    B");
			break;
		case 0x04: 
			sprintf(outputString, "INR    B");
			break;
		case 0x05: 
			sprintf(outputString, "DCR    B");
			break;
		case 0x06: 
			sprintf(outputString, "MVI %02X %02X", GetNextByte(rom), GetNextByte(rom));
			break;
		case 0x07: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x08: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x09: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x0a: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x0b: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x0c: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x0d: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x0e: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x0f: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x10: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		case 0x02: 
			sprintf(outputString, "STAX %02X", GetNextByte(rom));
			break;
		default:
			sprintf(outputString, "UNKNOWN OP");
			break;
	}
	return outputString;
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
		char* outputString = ProcessByte(currByte, rom);
		OutputByte(outputString);
	}

	fclose(rom);
    return 0;
}