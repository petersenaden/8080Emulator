/*
From :https://www.romhacking.net/forum/index.php?topic=16663.0
 LDA #$09
Here, the value of 9 gets loaded into the accumulator. This is called "Immediate."
LDA $09
Here, whatever is being held in $09 will be loaded into the accumulator. If this is NES, this is called loading from "Zero Page." If it's SNES, it's called loading from "Direct Page." Perhaps a better example:
LDA $0009
This is called "Absolute." If this is SNES, and DP was set to 0000 in the previous example, both of these would load from the same location. The DP load would be slightly faster, though.
*/

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
			sprintf(outputString, "%-7s", "NOP");
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
			sprintf(outputString, "%-7s", "NOP");
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
			sprintf(outputString, "%-7s", "NOP");
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
			sprintf(outputString, "%-7s", "RAL");
			break;
		case 0x18: 
			sprintf(outputString, "%-7s", "NOP");
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
			sprintf(outputString, "%-7s$%02X%02X", "SHLD", byte2, byte1);
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
			sprintf(outputString, "%-7s$%02X%02X", "LHLD", byte2, byte1);
			break;
		case 0x2b: 
			sprintf(outputString, "%-7sH", "DCX");
			break;
		case 0x2c: 
			sprintf(outputString, "%-7sL", "INR");
			break;
		case 0x2d: 
			sprintf(outputString, "%-7sL", "DCR");
			break;
		case 0x2e: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sL,#$%02X", "MVI", byte1);
			break;
		case 0x2f: 
			sprintf(outputString, "%-7s", "CMA");
			break;
		case 0x30:
			sprintf(outputString, "%-7s", "SIM");
			break;
		case 0x31: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sSP,#$%02X%02X", "LXI", byte2, byte1);
			break;
		case 0x32: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "STA", byte2, byte1);
			break;
		case 0x33: 
			sprintf(outputString, "%-7sSP", "INX");
			break;
		case 0x34: 
			sprintf(outputString, "%-7sM", "INR");
			break;
		case 0x35: 
			sprintf(outputString, "%-7sM", "DCR");
			break;
		case 0x36: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sM,#$%02X", "MVI", byte1);
			break;
		case 0x37: 
			sprintf(outputString, "%-7s", "STC");
			break;
		case 0x38: 
			sprintf(outputString, "%-7s", "NOP");
			break;
		case 0x39: 
			sprintf(outputString, "%-7sSP", "DAD");
			break;
		case 0x3a: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "LDA", byte2, byte1);
			break;
		case 0x3b: 
			sprintf(outputString, "%-7sSP", "DCX");
			break;
		case 0x3c: 
			sprintf(outputString, "%-7sA", "INR");
			break;
		case 0x3d: 
			sprintf(outputString, "%-7sA", "DCR");
			break;
		case 0x3e: 
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7sA,#$%02X", "MVI", byte1);
			break;
		case 0x3f: 
			sprintf(outputString, "%-7s", "CMC");
			break;
		case 0x40: 
			sprintf(outputString, "%-7sB,B", "MOV");
			break;
		case 0x41: 
			sprintf(outputString, "%-7sB,C", "MOV");
			break;
		case 0x42: 
			sprintf(outputString, "%-7sB,D", "MOV");
			break;
		case 0x43: 
			sprintf(outputString, "%-7sB,E", "MOV");
			break;
		case 0x44: 
			sprintf(outputString, "%-7sB,H", "MOV");
			break;
		case 0x45:
			sprintf(outputString, "%-7sB,L", "MOV");
			break;
		case 0x46:
			sprintf(outputString, "%-7sB,M", "MOV");
			break;
		case 0x47:
			sprintf(outputString, "%-7sB,A", "MOV");
			break;
		case 0x48:
			sprintf(outputString, "%-7sC,B", "MOV");
			break;
		case 0x49:
			sprintf(outputString, "%-7sC,C", "MOV");
			break;
		case 0x4a:
			sprintf(outputString, "%-7sC,D", "MOV");
			break;
		case 0x4b:
			sprintf(outputString, "%-7sC,E", "MOV");
			break;
		case 0x4c:
			sprintf(outputString, "%-7sC,H", "MOV");
			break;
		case 0x4d:
			sprintf(outputString, "%-7sC,L", "MOV");
			break;
		case 0x4e:
			sprintf(outputString, "%-7sC,M", "MOV");
			break;
		case 0x4f:
			sprintf(outputString, "%-7sC,A", "MOV");
			break;
		case 0x50:
			sprintf(outputString, "%-7sD,B", "MOV");
			break;
		case 0x51:
			sprintf(outputString, "%-7sD,C", "MOV");
			break;
		case 0x52:
			sprintf(outputString, "%-7sD,D", "MOV");
			break;
		case 0x53:
			sprintf(outputString, "%-7sD,E", "MOV");
			break;
		case 0x54:
			sprintf(outputString, "%-7sD,H", "MOV");
			break;
		case 0x55:
			sprintf(outputString, "%-7sD,L", "MOV");
			break;
		case 0x56:
			sprintf(outputString, "%-7sD,M", "MOV");
			break;
		case 0x57:
			sprintf(outputString, "%-7sD,A", "MOV");
			break;
		case 0x58:
			sprintf(outputString, "%-7sE,B", "MOV");
			break;
		case 0x59:
			sprintf(outputString, "%-7sE,C", "MOV");
			break;
		case 0x5a:
			sprintf(outputString, "%-7sE,D", "MOV");
			break;
		case 0x5b:
			sprintf(outputString, "%-7sE,E", "MOV");
			break;
		case 0x5c:
			sprintf(outputString, "%-7sE,H", "MOV");
			break;
		case 0x5d:
			sprintf(outputString, "%-7sE,L", "MOV");
			break;
		case 0x5e:
			sprintf(outputString, "%-7sE,M", "MOV");
			break;
		case 0x5f:
			sprintf(outputString, "%-7sE,A", "MOV");
			break;
		case 0x60:
			sprintf(outputString, "%-7sH,B", "MOV");
			break;
		case 0x61:
			sprintf(outputString, "%-7sH,C", "MOV");
			break;
		case 0x62:
			sprintf(outputString, "%-7sH,D", "MOV");
			break;
		case 0x63:
			sprintf(outputString, "%-7sH,E", "MOV");
			break;
		case 0x64:
			sprintf(outputString, "%-7sH,H", "MOV");
			break;
		case 0x65:
			sprintf(outputString, "%-7sH,L", "MOV");
			break;
		case 0x66:
			sprintf(outputString, "%-7sH,M", "MOV");
			break;
		case 0x67:
			sprintf(outputString, "%-7sH,A", "MOV");
			break;
		case 0x68:
			sprintf(outputString, "%-7sL,B", "MOV");
			break;
		case 0x69:
			sprintf(outputString, "%-7sL,C", "MOV");
			break;
		case 0x6a:
			sprintf(outputString, "%-7sL,D", "MOV");
			break;
		case 0x6b:
			sprintf(outputString, "%-7sL,E", "MOV");
			break;
		case 0x6c:
			sprintf(outputString, "%-7sL,H", "MOV");
			break;
		case 0x6d:
			sprintf(outputString, "%-7sL,L", "MOV");
			break;
		case 0x6e:
			sprintf(outputString, "%-7sL,M", "MOV");
			break;
		case 0x6f:
			sprintf(outputString, "%-7sL,A", "MOV");
			break;
		case 0x70:
			sprintf(outputString, "%-7sM,B", "MOV");
			break;
		case 0x71:
			sprintf(outputString, "%-7sM,C", "MOV");
			break;
		case 0x72:
			sprintf(outputString, "%-7sM,D", "MOV");
			break;
		case 0x73:
			sprintf(outputString, "%-7sM,E", "MOV");
			break;
		case 0x74:
			sprintf(outputString, "%-7sM,H", "MOV");
			break;
		case 0x75:
			sprintf(outputString, "%-7sM,L", "MOV");
			break;
		case 0x76:
			sprintf(outputString, "%-7s", "HLT");
			break;
		case 0x77:
			sprintf(outputString, "%-7sM,A", "MOV");
			break;
		case 0x78:
			sprintf(outputString, "%-7sA,B", "MOV");
			break;
		case 0x79:
			sprintf(outputString, "%-7sA,C", "MOV");
			break;
		case 0x7a:
			sprintf(outputString, "%-7sA,D", "MOV");
			break;
		case 0x7b:
			sprintf(outputString, "%-7sA,E", "MOV");
			break;
		case 0x7c:
			sprintf(outputString, "%-7sA,H", "MOV");
			break;
		case 0x7d:
			sprintf(outputString, "%-7sA,L", "MOV");
			break;
		case 0x7e:
			sprintf(outputString, "%-7sA,M", "MOV");
			break;
		case 0x7f:
			sprintf(outputString, "%-7sA,A", "MOV");
			break;
		case 0x80:
			sprintf(outputString, "%-7sB", "ADD");
			break;
		case 0x81:
			sprintf(outputString, "%-7sC", "ADD");
			break;
		case 0x82:
			sprintf(outputString, "%-7sD", "ADD");
			break;
		case 0x83:
			sprintf(outputString, "%-7sE", "ADD");
			break;
		case 0x84:
			sprintf(outputString, "%-7sH", "ADD");
			break;
		case 0x85:
			sprintf(outputString, "%-7sL", "ADD");
			break;
		case 0x86:
			sprintf(outputString, "%-7sM", "ADD");
			break;
		case 0x87:
			sprintf(outputString, "%-7sA", "ADD");
			break;
		case 0x88:
			sprintf(outputString, "%-7sB", "ADC");
			break;
		case 0x89:
			sprintf(outputString, "%-7sC", "ADC");
			break;
		case 0x8a:
			sprintf(outputString, "%-7sD", "ADC");
			break;
		case 0x8b:
			sprintf(outputString, "%-7sE", "ADC");
			break;
		case 0x8c:
			sprintf(outputString, "%-7sH", "ADC");
			break;
		case 0x8d:
			sprintf(outputString, "%-7sL", "ADC");
			break;
		case 0x8e:
			sprintf(outputString, "%-7sM", "ADC");
			break;
		case 0x8f:
			sprintf(outputString, "%-7sA", "ADC");
			break;
		case 0x90:
			sprintf(outputString, "%-7sB", "SUB");
			break;
		case 0x91:
			sprintf(outputString, "%-7sC", "SUB");
			break;
		case 0x92:
			sprintf(outputString, "%-7sD", "SUB");
			break;
		case 0x93:
			sprintf(outputString, "%-7sE", "SUB");
			break;
		case 0x94:
			sprintf(outputString, "%-7sH", "SUB");
			break;
		case 0x95:
			sprintf(outputString, "%-7sL", "SUB");
			break;
		case 0x96:
			sprintf(outputString, "%-7sM", "SUB");
			break;
		case 0x97:
			sprintf(outputString, "%-7sA", "SUB");
			break;
		case 0x98:
			sprintf(outputString, "%-7sB", "SBB");
			break;
		case 0x99:
			sprintf(outputString, "%-7sC", "SBB");
			break;
		case 0x9a:
			sprintf(outputString, "%-7sD", "SBB");
			break;
		case 0x9b:
			sprintf(outputString, "%-7sE", "SBB");
			break;
		case 0x9c:
			sprintf(outputString, "%-7sH", "SBB");
			break;
		case 0x9d:
			sprintf(outputString, "%-7sL", "SBB");
			break;
		case 0x9e:
			sprintf(outputString, "%-7sM", "SBB");
			break;
		case 0x9f:
			sprintf(outputString, "%-7sA", "SBB");
			break;
		case 0xa0:
			sprintf(outputString, "%-7sB", "ANA");
			break;
		case 0xa1:
			sprintf(outputString, "%-7sC", "ANA");
			break;
		case 0xa2:
			sprintf(outputString, "%-7sD", "ANA");
			break;
		case 0xa3:
			sprintf(outputString, "%-7sE", "ANA");
			break;
		case 0xa4:
			sprintf(outputString, "%-7sH", "ANA");
			break;
		case 0xa5:
			sprintf(outputString, "%-7sL", "ANA");
			break;
		case 0xa6:
			sprintf(outputString, "%-7sM", "ANA");
			break;
		case 0xa7:
			sprintf(outputString, "%-7sA", "XRA");
			break;
		case 0xa8:
			sprintf(outputString, "%-7sB", "XRA");
			break;
		case 0xa9:
			sprintf(outputString, "%-7sC", "XRA");
			break;
		case 0xaa:
			sprintf(outputString, "%-7sD", "XRA");
			break;
		case 0xab:
			sprintf(outputString, "%-7sE", "XRA");
			break;
		case 0xac:
			sprintf(outputString, "%-7sH", "XRA");
			break;
		case 0xad:
			sprintf(outputString, "%-7sL", "XRA");
			break;
		case 0xae:
			sprintf(outputString, "%-7sM", "XRA");
			break;
		case 0xaf:
			sprintf(outputString, "%-7sA", "XRA");
			break;
		case 0xb0:
			sprintf(outputString, "%-7sB", "ORA");
			break;
		case 0xb1:
			sprintf(outputString, "%-7sC", "ORA");
			break;
		case 0xb2:
			sprintf(outputString, "%-7sD", "ORA");
			break;
		case 0xb3:
			sprintf(outputString, "%-7sE", "ORA");
			break;
		case 0xb4:
			sprintf(outputString, "%-7sH", "ORA");
			break;
		case 0xb5:
			sprintf(outputString, "%-7sL", "ORA");
			break;
		case 0xb6:
			sprintf(outputString, "%-7sM", "ORA");
			break;
		case 0xb7:
			sprintf(outputString, "%-7sA", "ORA");
			break;
		case 0xb8:
			sprintf(outputString, "%-7sB", "CMP");
			break;
		case 0xb9:
			sprintf(outputString, "%-7sC", "CMP");
			break;
		case 0xba:
			sprintf(outputString, "%-7sD", "CMP");
			break;
		case 0xbb:
			sprintf(outputString, "%-7sE", "CMP");
			break;
		case 0xbc:
			sprintf(outputString, "%-7sH", "CMP");
			break;
		case 0xbd:
			sprintf(outputString, "%-7sL", "CMP");
			break;
		case 0xbe:
			sprintf(outputString, "%-7sM", "CMP");
			break;
		case 0xbf:
			sprintf(outputString, "%-7sA", "CMP");
			break;
		case 0xc0:
			sprintf(outputString, "%-7s", "RNZ");
			break;
		case 0xc1:
			sprintf(outputString, "%-7sB", "POP");
			break;
		case 0xc2:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "JNZ", byte2, byte1);
			break;
		case 0xc3:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "JMP", byte2, byte1);
			break;
		case 0xc4:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "CNZ", byte2, byte1);
			break;
		case 0xc5:
			sprintf(outputString, "%-7sB", "PUSH");
			break;
		case 0xc6:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s#$%02X", "ADI", byte1);
			break;
		case 0xc7:
			sprintf(outputString, "%-7s0", "RST");
			break;
		case 0xc8:
			sprintf(outputString, "%-7s", "RZ");
			break;
		case 0xc9:
			sprintf(outputString, "%-7s", "RET");
			break;
		case 0xca:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "JZ", byte2, byte1);
			break;
		case 0xcb:
			sprintf(outputString, "%-7s", "NOP");
			break;
		case 0xcc:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "CZ", byte2, byte1);
			break;
		case 0xcd:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "CALL", byte2, byte1);
			break;
		case 0xce:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s#$%02X", "ACI", byte1);
			break;
		case 0xcf:
			sprintf(outputString, "%-7s1", "RST");
			break;
		case 0xd0:
			sprintf(outputString, "%-7s", "RNC");
			break;
		case 0xd1:
			sprintf(outputString, "%-7sD", "POP");
			break;
		case 0xd2:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "JNC", byte2, byte1);
			break;
		case 0xd3:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s#$%02X", "OUT", byte1);
			break;
		case 0xd4:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "CNC", byte2, byte1);
			break;
		case 0xd5:
			sprintf(outputString, "%-7sD", "PUSH");
			break;
		case 0xd6:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s#$%02X", "SUI", byte1);
			break;
		case 0xd7:
			sprintf(outputString, "%-7s2", "RST");
			break;
		case 0xd8:
			sprintf(outputString, "%-7s", "RC");
			break;
		case 0xd9:
			sprintf(outputString, "%-7s", "NOP");
			break;
		case 0xda:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "JC", byte2, byte1);
			break;
		case 0xdb:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s#$%02X", "IN", byte1);
			break;
		case 0xdc:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "CC", byte2, byte1);
			break;
		case 0xdd:
			sprintf(outputString, "%-7s", "NOP");
			break;
		case 0xde:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s#$%02X", "SBI", byte1);
			break;
		case 0xdf:
			sprintf(outputString, "%-7s3", "RST");
			break;
		case 0xe0:
			sprintf(outputString, "%-7s", "RPO");
			break;
		case 0xe1:
			sprintf(outputString, "%-7sH", "POP");
			break;
		case 0xe2:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "JPO", byte2, byte1);
			break;
		case 0xe3:
			sprintf(outputString, "%-7s3", "XTHL");
			break;
		case 0xe4:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "CPO", byte2, byte1);
			break;
		case 0xe5:
			sprintf(outputString, "%-7sH", "PUSH");
			break;
		case 0xe6:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s#$%02X", "ANI", byte1);
			break;
		case 0xe7:
			sprintf(outputString, "%-7s4", "RST");
			break;
		case 0xe8:
			sprintf(outputString, "%-7s", "RPE");
			break;
		case 0xe9:
			sprintf(outputString, "%-7s", "PCHL");
			break;
		case 0xea:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "JPE", byte2, byte1);
			break;
		case 0xeb:
			sprintf(outputString, "%-7s", "XCHG");
			break;
		case 0xec:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "CPE", byte2, byte1);
			break;
		case 0xed:
			sprintf(outputString, "%-7s", "NOP");
			break;
		case 0xee:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s#$%02X", "XRI", byte1);
			break;
		case 0xef:
			sprintf(outputString, "%-7s5", "RST");
			break;
		case 0xf0:
			sprintf(outputString, "%-7s", "RP");
			break;
		case 0xf1:
			sprintf(outputString, "%-7sPSW", "POP");
			break;
		case 0xf2:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "JP", byte2, byte1);
			break;
		case 0xf3:
			sprintf(outputString, "%-7s", "DI");
			break;
		case 0xf4:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "CP", byte2, byte1);
			break;
		case 0xf5:
			sprintf(outputString, "%-7sPSW", "PUSH");
			break;
		case 0xf6:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s#$%02X", "ORI", byte1);
			break;
		case 0xf7:
			sprintf(outputString, "%-7s6", "RST");
			break;
		case 0xf8:
			sprintf(outputString, "%-7s", "RM");
			break;
		case 0xf9:
			sprintf(outputString, "%-7s", "SPHL");
			break;
		case 0xfa:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "JM", byte2, byte1);
			break;
		case 0xfb:
			sprintf(outputString, "%-7s", "EI");
			break;
		case 0xfc:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			byte2 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s$%02X%02X", "CM", byte2, byte1);
			break;
		case 0xfd:
			sprintf(outputString, "%-7s", "NOP");
			break;
		case 0xfe:
			byte1 = GetNextByte(rom);
			(*programCounter)++;
			sprintf(outputString, "%-7s#$%02X", "CPI", byte1);
			break;
		case 0xff:
			sprintf(outputString, "%-7s7", "RST");
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
		char* outputString = ProcessByte(currByte, rom, &programCounter);
		OutputByte(outputString);
	}

	fclose(rom);
    return 0;
}