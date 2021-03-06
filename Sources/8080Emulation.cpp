// https://stackoverflow.com/a/14387
#define _CRT_SECURE_NO_DEPRECATE

#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<assert.h>
#include<windows.h>
#include<errno.h>
#include<time.h>
#ifndef EMULATION8080
#define EMULATION8080
#include "8080Emulation.h"
#endif

#ifndef INSTRUCTIONSET8080
#define INSTRUCTIONSET8080
#include "8080InstructionSet.h"
#endif

#define PRINTOP FALSE

int fopen_safe2(FILE **f, const char *name, const char *mode) {
    int ret = 0;
    assert(f);
    *f = fopen(name, mode);
    /* Can't be sure about 1-to-1 mapping of errno and MS' errno_t */
    if (!*f)
        ret = errno;
    return ret;
}

struct StateFlags* InitializeStateFlagsStruct(struct StateFlags *sf)
{
	sf->z  = 0;
	sf->s  = 0;
	sf->p  = 0;
	sf->cy = 0;
	sf->ac = 0;
	return sf;
}

struct State8080* Initialize8080StateStruct(struct State8080 *st)
{
	st->a = 0;
	st->b = 0;
	st->c = 0;
	st->d = 0;
	st->e = 0;
	st->h = 0;
	st->l = 0;
	st->interrupt_enable = 0;
	st->interrupt_value = 0;
	st->sp = 0;
	st->pc = 0;
	st->memory = (unsigned char*)(calloc(65536, sizeof(unsigned char)));
	InitializeStateFlagsStruct(&(st->sf));
	return st;
} 

int y = 0;

void Execute8080Op(struct State8080 *stt)
{
	unsigned char *currOp = &(stt->memory[stt->pc]);
	#ifdef PRINTOP
	fprintf(stdout, "SP: 0x%02X\t"		, stt->sp);
	fprintf(stdout, "PC: 0x%02X\t", stt->pc);
	fprintf(stdout, "Operation: 0x%02X\t", *currOp);
	fprintf(stdout, "A: 0x%02X\t", stt->a);
	fprintf(stdout, "B: 0x%02X\t", stt->b);
	fprintf(stdout, "C: 0x%02X\t", stt->c);
	fprintf(stdout, "D: 0x%02X\t", stt->d);
	fprintf(stdout, "E: 0x%02X\t", stt->e);
	fprintf(stdout, "H: 0x%02X\t", stt->h);
	fprintf(stdout, "L: 0x%02X\t", stt->l);

	fprintf(stdout, "Z: %c\t", stt->sf.z ? '1' : '0');
	fprintf(stdout, "S: %c\t", stt->sf.s ? '1' : '0');
	fprintf(stdout, "P: %c\t", stt->sf.p ? '1' : '0');
	fprintf(stdout, "CY: %c\n", stt->sf.cy ? '1' : '0');
	//fprintf(stdout, "AC: %c\n", stt->sf.ac ? '1' : '0');
	#endif
	switch (*currOp)
	{
		case 0x00:								  break; // NOP
		case 0x01: 										 // LXI B,D16
			LXIInstruction(stt, &(stt->b), &(stt->c));
			break;
		case 0x02: 										 // STAX B
		{
			STAXInstruction(stt, &(stt->b), &(stt->c), &(stt->a));
			break;
		}
		case 0x03: 										 // INX B
		{
			INXInstruction(&(stt->b), &(stt->c));
			break;
		}
		case 0x04: 
		{		
			INRInstruction(stt, &(stt->b));
			break;
		}
		case 0x05: 
		{		
			DCRInstruction(stt, &(stt->b));
			break;
		}
		case 0x06: 
		{		
			MVIInstruction(stt, &(stt->b));
			break;
		}
		case 0x07: 
		{		
			RLCInstruction(stt, &(stt->a));
			break;
		}
		case 0x08: UnimplementedInstruction(stt); break;
		case 0x09: 
		{		
			DADInstruction(stt, &(stt->h), &(stt->l), &(stt->b), &(stt->c));
			break;
		}
		case 0x0a: 
		{		
			LDAXInstruction(stt, &(stt->b), &(stt->c), &(stt->a));
			break;
		}
		case 0x0b: 
		{		
			DCXInstruction(&(stt->b), &(stt->c));
			break;
		}
		case 0x0c: 
		{		
			INRInstruction(stt, &(stt->c));
			break;
		}
		case 0x0d: 
		{		
			DCRInstruction(stt, &(stt->c));
			break;
		}
		case 0x0e: 
		{		
			MVIInstruction(stt, &(stt->c));
			break;
		}
		case 0x0f: 
		{		
			RRCInstruction(stt, &(stt->a));
			break;
		}
		case 0x10: UnimplementedInstruction(stt); break;
		case 0x11: 
		{		
			LXIInstruction(stt, &(stt->d), &(stt->e));
			break;
		}
		case 0x12: 
		{		
			STAXInstruction(stt, &(stt->d), &(stt->e), &(stt->a));
			break;
		}
		case 0x13: 
		{		
			INXInstruction(&(stt->d), &(stt->e));
			break;
		}
		case 0x14: 
		{		
			INRInstruction(stt, &(stt->d));
			break;
		}
		case 0x15: 
		{		
			DCRInstruction(stt, &(stt->d));
			break;
		}
		case 0x16: 
		{		
			MVIInstruction(stt, &(stt->d));
			break;
		}
		case 0x17: 
		{		
			RALInstruction(stt, &(stt->a));
			break;
		}
		case 0x18: UnimplementedInstruction(stt); break;
		case 0x19: 
		{		
			DADInstruction(stt, &(stt->h), &(stt->l), &(stt->d), &(stt->e));
			break;
		}
		case 0x1a: 
		{		
			LDAXInstruction(stt, &(stt->d), &(stt->e), &(stt->a));
			break;
		}
		case 0x1b: 
		{		
			DCXInstruction(&(stt->d), &(stt->e));
			break;
		}
		case 0x1c: 
		{		
			INRInstruction(stt, &(stt->e));
			break;
		}
		case 0x1d:
		{
			DCRInstruction(stt, &(stt->e));
			break;
		}
		case 0x1e:
		{
			MVIInstruction(stt, &(stt->e));
			break;
		}
		case 0x1f:
		{
			RARInstruction(stt, &(stt->a));
			break;
		}
		case 0x20: UnimplementedInstruction(stt); break;
		case 0x21:
		{
			LXIInstruction(stt, &(stt->h), &(stt->l));
			break;
		}
		case 0x22:
		{
			SHLDInstruction(stt, &(stt->h), &(stt->l));
			break;
		}
		case 0x23: 
		{		
			INXInstruction(&(stt->h), &(stt->l));
			break;
		}
		case 0x24: 
		{		
			INRInstruction(stt, &(stt->h));
			break;
		}
		case 0x25: 
		{		
			DCRInstruction(stt, &(stt->h));
			break;
		}
		case 0x26: 
		{		
			MVIInstruction(stt, &(stt->h));
			break;
		}
		case 0x27: 
		{		
			DAAInstruction();
			break;
		}
		case 0x28: UnimplementedInstruction(stt); break;
		case 0x29: 
		{		
			// This could very easily be wrong
			DADInstruction(stt, &(stt->h), &(stt->l), &(stt->h), &(stt->l));
			break;
		}
		case 0x2a: 
		{	
			LHLDInstruction(stt, &(stt->l), &(stt->h));
			break;
		}
		case 0x2b: 
		{		
			DCXInstruction(&(stt->h), &(stt->l));
			break;
		}
		case 0x2c: 
		{		
			INRInstruction(stt, &(stt->l));
			break;
		}
		case 0x2d: 
		{		
			DCRInstruction(stt, &(stt->l));
			break;
		}
		case 0x2e: 
		{		
			MVIInstruction(stt, &(stt->l));
			break;
		}
		case 0x2f: 
		{		
			CMAInstruction(&(stt->l));
			break;
		}
		case 0x30: UnimplementedInstruction(stt); break;
		case 0x31: 
		{
			unsigned char byteThree = stt->memory[stt->pc + 2];
			unsigned char byteTwo 	= stt->memory[stt->pc + 1];
			stt->sp = (unsigned short)(byteThree << 8 | byteTwo);
			stt->pc++;
			stt->pc++;
			break;
		}
		case 0x32: 
		{		
			STAInstruction(stt, &(stt->a));
			break;
		}
		case 0x33:  
		{		
			unsigned char* sPHighByte = (unsigned char*)(&(stt->sp));
			unsigned char* sPLowByte = ((unsigned char*)(&(stt->sp))) + 1;
			INXInstruction(sPHighByte, sPLowByte);
			break;
		}
		case 0x34: 
		{		
			INRMInstruction(stt);
			break;
		}
		case 0x35: 
		{		
			DCRMInstruction(stt);
			break;
		}
		case 0x36: 
		{		
			MVIMInstruction(stt);
			break;
		}
		case 0x37: 
		{		
			STCInstruction(stt);
			break;
		}
		case 0x38: UnimplementedInstruction(stt); break;
		case 0x39: 
		{
			unsigned char* sPHighByte = (unsigned char*)(&(stt->sp));
			unsigned char* sPLowByte = ((unsigned char*)(&(stt->sp))) + 1;
			DADInstruction(stt, &(stt->h), &(stt->l), sPHighByte, sPLowByte);
			break;
		}
		case 0x3a: 
		{
			LDAInstruction(stt);
			break;
		}
		case 0x3b: 
		{
			unsigned char* sPHighByte = (unsigned char*)(&(stt->sp));
			unsigned char* sPLowByte = ((unsigned char*)(&(stt->sp))) + 1;
			DCXInstruction(sPHighByte, sPLowByte);
			break;
		}
		case 0x3c: 
		{
			INRInstruction(stt, &(stt->a));
			break;
		}
		case 0x3d: 
		{
			DCRInstruction(stt, &(stt->a));
			break;
		}
		case 0x3e: 
		{
			MVIInstruction(stt, &(stt->a));
			break;
		}
		case 0x3f: 
		{
			CMCInstruction(stt);
			break;
		}
		case 0x40: 
		{
			MOVInstruction(&(stt->b), &(stt->b));
			break;
		}
		case 0x41: 
		{
			MOVInstruction(&(stt->b), &(stt->c));
			break;
		}
		case 0x42: 
		{
			MOVInstruction(&(stt->b), &(stt->d));
			break;
		}
		case 0x43: 
		{
			MOVInstruction(&(stt->b), &(stt->e));
			break;
		}
		case 0x44: 
		{
			MOVInstruction(&(stt->b), &(stt->d));
			break;
		}
		case 0x45: 
		{
			MOVInstruction(&(stt->b), &(stt->h));
			break;
		}
		case 0x46: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(&(stt->b), charToManipulate);
			break;
		}
		case 0x47: 
		{
			MOVInstruction(&(stt->b), &(stt->a));
			break;
		}
		case 0x48: 
		{
			MOVInstruction(&(stt->c), &(stt->b));
			break;
		}
		case 0x49: 
		{
			MOVInstruction(&(stt->c), &(stt->c));
			break;
		}
		case 0x4a: 
		{
			MOVInstruction(&(stt->c), &(stt->d));
			break;
		}
		case 0x4b: 
		{
			MOVInstruction(&(stt->c), &(stt->e));
			break;
		}
		case 0x4c: 
		{
			MOVInstruction(&(stt->c), &(stt->h));
			break;
		}
		case 0x4d: 
		{
			MOVInstruction(&(stt->c), &(stt->l));
			break;
		}
		case 0x4e: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(&(stt->c), charToManipulate);
			break;
		}
		case 0x4f: 
		{
			MOVInstruction(&(stt->c), &(stt->a));
			break;
		}
		case 0x50: 
		{
			MOVInstruction(&(stt->d), &(stt->b));
			break;
		}
		case 0x51: 
		{
			MOVInstruction(&(stt->d), &(stt->c));
			break;
		}
		case 0x52: 
		{
			MOVInstruction(&(stt->d), &(stt->d));
			break;
		}
		case 0x53: 
		{
			MOVInstruction(&(stt->d), &(stt->e));
			break;
		}
		case 0x54: 
		{
			MOVInstruction(&(stt->d), &(stt->h));
			break;
		}
		case 0x55: 
		{
			MOVInstruction(&(stt->d), &(stt->l));
			break;
		}
		case 0x56: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(&(stt->d), charToManipulate);
			break;
		}
		case 0x57: 
		{
			MOVInstruction(&(stt->d), &(stt->a));
			break;
		}
		case 0x58: 
		{
			MOVInstruction(&(stt->e), &(stt->b));
			break;
		}
		case 0x59: 
		{
			MOVInstruction(&(stt->e), &(stt->c));
			break;
		}
		case 0x5a: 
		{
			MOVInstruction(&(stt->e), &(stt->d));
			break;
		}
		case 0x5b: 
		{
			MOVInstruction(&(stt->e), &(stt->e));
			break;
		}
		case 0x5c: 
		{
			MOVInstruction(&(stt->e), &(stt->h));
			break;
		}
		case 0x5d: 
		{
			MOVInstruction(&(stt->e), &(stt->l));
			break;
		}
		case 0x5e: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(&(stt->e), charToManipulate);
			break;
		}
		case 0x5f: 
		{
			MOVInstruction(&(stt->e), &(stt->a));
			break;
		}
		case 0x60: 
		{
			MOVInstruction(&(stt->h), &(stt->b));
			break;
		}
		case 0x61: 
		{
			MOVInstruction(&(stt->h), &(stt->c));
			break;
		}
		case 0x62: 
		{
			MOVInstruction(&(stt->h), &(stt->d));
			break;
		}
		case 0x63: 
		{
			MOVInstruction(&(stt->h), &(stt->e));
			break;
		}
		case 0x64: 
		{
			MOVInstruction(&(stt->h), &(stt->h));
			break;
		}
		case 0x65: 
		{
			MOVInstruction(&(stt->h), &(stt->l));
			break;
		}
		case 0x66: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(&(stt->h), charToManipulate);
			break;
		}
		case 0x67: 
		{
			MOVInstruction(&(stt->h), &(stt->a));
			break;
		}
		case 0x68: 
		{
			MOVInstruction(&(stt->l), &(stt->b));
			break;
		}
		case 0x69: 
		{
			MOVInstruction(&(stt->l), &(stt->c));
			break;
		}
		case 0x6a: 
		{
			MOVInstruction(&(stt->l), &(stt->d));
			break;
		}
		case 0x6b: 
		{
			MOVInstruction(&(stt->l), &(stt->e));
			break;
		}
		case 0x6c: 
		{
			MOVInstruction(&(stt->l), &(stt->h));
			break;
		}
		case 0x6d: 
		{
			MOVInstruction(&(stt->l), &(stt->l));
			break;
		}
		case 0x6e: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(&(stt->l), charToManipulate);
			break;
		}
		case 0x6f: 
		{
			MOVInstruction(&(stt->l), &(stt->a));
			break;
		}
		case 0x70: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(charToManipulate, &(stt->b));
			break;
		}
		case 0x71: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(charToManipulate, &(stt->c));
			break;
		}
		case 0x72: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(charToManipulate, &(stt->d));
			break;
		}
		case 0x73: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(charToManipulate, &(stt->e));
			break;
		}
		case 0x74: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(charToManipulate, &(stt->h));
			break;
		}
		case 0x75: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(charToManipulate, &(stt->l));
			break;
		}
		case 0x76: 
		{
			HLTInstruction();
			break;
		}
		case 0x77: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse | (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(charToManipulate, &(stt->a));
			break;
		}
		case 0x78:
		{
			MOVInstruction(&(stt->a), &(stt->b));
			break;
		}
		case 0x79: 
		{
			MOVInstruction(&(stt->a), &(stt->c));
			break;
		}
		case 0x7a: 
		{
			MOVInstruction(&(stt->a), &(stt->d));
			break;
		}
		case 0x7b: 
		{
			MOVInstruction(&(stt->a), &(stt->e));
			break;
		}
		case 0x7c: 
		{
			MOVInstruction(&(stt->a), &(stt->h));
			break;
		}
		case 0x7d: 
		{
			MOVInstruction(&(stt->a), &(stt->l));
			break;
		}
		case 0x7e: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			MOVInstruction(&(stt->a), charToManipulate);
			break;
		}
		case 0x7f: 
		{
			MOVInstruction(&(stt->a), &(stt->a));
			break;
		}
		case 0x80: 
		{
			ADDInstruction(stt, &(stt->a), &(stt->a), &(stt->b));
			break;
		}
		case 0x81: 
		{
			ADDInstruction(stt, &(stt->a), &(stt->a), &(stt->c));
			break;
		}
		case 0x82: 
		{
			ADDInstruction(stt, &(stt->a), &(stt->a), &(stt->d));
			break;
		}
		case 0x83: 
		{
			ADDInstruction(stt, &(stt->a), &(stt->a), &(stt->e));
			break;
		}
		case 0x84: 
		{
			ADDInstruction(stt, &(stt->a), &(stt->a), &(stt->h));
			break;
		}
		case 0x85: 
		{
			ADDInstruction(stt, &(stt->a), &(stt->a), &(stt->l));
			break;
		}
		case 0x86: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			ADDInstruction(stt, &(stt->a), &(stt->a), charToManipulate);
			break;
		}
		case 0x87: 
		{
			ADDInstruction(stt, &(stt->a), &(stt->a), &(stt->a));
			break;
		}
		case 0x88: 
		{
			ADCInstruction(stt, &(stt->a), &(stt->a), &(stt->b));
			break;
		}
		case 0x89: 
		{
			ADCInstruction(stt, &(stt->a), &(stt->a), &(stt->c));
			break;
		}
		case 0x8a: 
		{
			ADCInstruction(stt, &(stt->a), &(stt->a), &(stt->d));
			break;
		}
		case 0x8b: 
		{
			ADCInstruction(stt, &(stt->a), &(stt->a), &(stt->e));
			break;
		}
		case 0x8c: 
		{
			ADCInstruction(stt, &(stt->a), &(stt->a), &(stt->h));
			break;
		}
		case 0x8d: 
		{
			ADCInstruction(stt, &(stt->a), &(stt->a), &(stt->l));
			break;
		}
		case 0x8e: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			ADCInstruction(stt, &(stt->a), &(stt->a), charToManipulate);
			break;
		}
		case 0x8f: 
		{
			ADCInstruction(stt, &(stt->a), &(stt->a), &(stt->a));
			break;
		}
		case 0x90: 
		{
			SUBInstruction(stt, &(stt->a), &(stt->a), &(stt->b));
			break;
		}
		case 0x91: 
		{
			SUBInstruction(stt, &(stt->a), &(stt->a), &(stt->c));
			break;
		}
		case 0x92: 
		{
			SUBInstruction(stt, &(stt->a), &(stt->a), &(stt->d));
			break;
		}
		case 0x93: 
		{
			SUBInstruction(stt, &(stt->a), &(stt->a), &(stt->e));
			break;
		}
		case 0x94: 
		{
			SUBInstruction(stt, &(stt->a), &(stt->a), &(stt->h));
			break;
		}
		case 0x95: 
		{
			SUBInstruction(stt, &(stt->a), &(stt->a), &(stt->l));
			break;
		}
		case 0x96: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			SUBInstruction(stt, &(stt->a), &(stt->a), charToManipulate);
			break;
		}
		case 0x97: 
		{
			SUBInstruction(stt, &(stt->a), &(stt->a), &(stt->a));
			break;
		}
		case 0x98: 
		{
			SBBInstruction(stt, &(stt->a), &(stt->a), &(stt->b));
			break;
		}
		case 0x99: 
		{
			SBBInstruction(stt, &(stt->a), &(stt->a), &(stt->c));
			break;
		}
		case 0x9a: 
		{
			SBBInstruction(stt, &(stt->a), &(stt->a), &(stt->d));
			break;
		}
		case 0x9b: 
		{
			SBBInstruction(stt, &(stt->a), &(stt->a), &(stt->e));
			break;
		}
		case 0x9c: 
		{
			SBBInstruction(stt, &(stt->a), &(stt->a), &(stt->h));
			break;
		}
		case 0x9d: 
		{
			SBBInstruction(stt, &(stt->a), &(stt->a), &(stt->l));
			break;
		}
		case 0x9e: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			SBBInstruction(stt, &(stt->a), &(stt->a), charToManipulate);
			break;
		}
		case 0x9f: 
		{
			SBBInstruction(stt, &(stt->a), &(stt->a), &(stt->a));
			break;
		}
		case 0xa0: 
		{
			ANAInstruction(stt, &(stt->a), &(stt->a), &(stt->b));
			break;
		}
		case 0xa1: 
		{
			ANAInstruction(stt, &(stt->a), &(stt->a), &(stt->c));
			break;
		}
		case 0xa2: 
		{
			ANAInstruction(stt, &(stt->a), &(stt->a), &(stt->d));
			break;
		}
		case 0xa3: 
		{
			ANAInstruction(stt, &(stt->a), &(stt->a), &(stt->e));
			break;
		}
		case 0xa4: 
		{
			ANAInstruction(stt, &(stt->a), &(stt->a), &(stt->h));
			break;
		}
		case 0xa5: 
		{
			ANAInstruction(stt, &(stt->a), &(stt->a), &(stt->l));
			break;
		}
		case 0xa6: 
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			ANAInstruction(stt, &(stt->a), &(stt->a), charToManipulate);
			break;
		}
		case 0xa7:
		{
			ANAInstruction(stt, &(stt->a), &(stt->a), &(stt->a));
			break;
		}
		case 0xa8:
		{
			XRAInstruction(stt, &(stt->a), &(stt->a), &(stt->b));
			break;
		}
		case 0xa9:
		{
			XRAInstruction(stt, &(stt->a), &(stt->a), &(stt->c));
			break;
		}
		case 0xaa:
		{
			XRAInstruction(stt, &(stt->a), &(stt->a), &(stt->d));
			break;
		}
		case 0xab:
		{
			XRAInstruction(stt, &(stt->a), &(stt->a), &(stt->e));
			break;
		}
		case 0xac:
		{
			XRAInstruction(stt, &(stt->a), &(stt->a), &(stt->h));
			break;
		}
		case 0xad:
		{
			XRAInstruction(stt, &(stt->a), &(stt->a), &(stt->l));
			break;
		}
		case 0xae:
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			XRAInstruction(stt, &(stt->a), &(stt->a), charToManipulate);
			break;
		}
		case 0xaf:
		{
			XRAInstruction(stt, &(stt->a), &(stt->a), &(stt->a));
			break;
		}
		case 0xb0:
		{
			ORAInstruction(stt, &(stt->a), &(stt->a), &(stt->b));
			break;
		}
		case 0xb1:
		{
			ORAInstruction(stt, &(stt->a), &(stt->a), &(stt->c));
			break;
		}
		case 0xb2:
		{
			ORAInstruction(stt, &(stt->a), &(stt->a), &(stt->d));
			break;
		}
		case 0xb3:
		{
			ORAInstruction(stt, &(stt->a), &(stt->a), &(stt->e));
			break;
		}
		case 0xb4:
		{
			ORAInstruction(stt, &(stt->a), &(stt->a), &(stt->h));
			break;
		}
		case 0xb5:
		{
			ORAInstruction(stt, &(stt->a), &(stt->a), &(stt->l));
			break;
		}
		case 0xb6:
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			ORAInstruction(stt, &(stt->a), &(stt->a), charToManipulate);
			break;
		}
		case 0xb7:
		{
			ORAInstruction(stt, &(stt->a), &(stt->a), &(stt->a));
			break;
		}
		case 0xb8:
		{
			CMPInstruction(stt, &(stt->a), &(stt->b));
			break;
		}
		case 0xb9:
		{
			CMPInstruction(stt, &(stt->a), &(stt->c));
			break;
		}
		case 0xba:
		{
			CMPInstruction(stt, &(stt->a), &(stt->d));
			break;
		}
		case 0xbb:
		{
			CMPInstruction(stt, &(stt->a), &(stt->e));
			break;
		}
		case 0xbc:
		{
			CMPInstruction(stt, &(stt->a), &(stt->h));
			break;
		}
		case 0xbd:
		{
			CMPInstruction(stt, &(stt->a), &(stt->l));
			break;
		}
		case 0xbe:
		{
			unsigned short int addressToUse = 0;
			addressToUse = (unsigned short int)(stt->h);
			addressToUse = (unsigned short int)(addressToUse << 8);
			addressToUse = (unsigned short int)(addressToUse + (stt->l));
			unsigned char* charToManipulate = &(stt->memory[addressToUse]);
			CMPInstruction(stt, &(stt->a), charToManipulate);
			break;
		}
		case 0xbf:
		{
			CMPInstruction(stt, &(stt->a), &(stt->a));
			break;
		}
		case 0xc0:
		{
			if (!(stt->sf.z))
			{
				RETInstruction(stt);
			}
			break;
		}
		case 0xc1:
		{
			POPInstruction(stt, &(stt->c), &(stt->b));
			break;
		}
		case 0xc2:
		{
			JNZInstruction(stt);
			return;
			break;
		}
		case 0xc3:
		{
			JMPInstruction(stt);
			return;
			break;
		}
		case 0xc4:
		{
			if (!(stt->sf.z))
			{
				CALLInstruction(stt);
				return; 
			}
			else
			{
				stt->pc++;
				stt->pc++;
			}
			break;
		}
		case 0xc5:
		{
			PUSHInstruction(stt, &(stt->c), &(stt->b));
			break;
		}
		case 0xc6:
		{
			ADIInstruction(stt, &(stt->a), &(stt->a));
			break;
		}
		case 0xc7:
		{
			CALLDirectInstruction(stt, 0);
			return;
			break;
		}
		case 0xc8:
		{
			if (stt->sf.z)
			{
				RETInstruction(stt);
			}
			break;
		}
		case 0xc9:
		{
			RETInstruction(stt);
			break;
		}
		case 0xca:
		{
			JZInstruction(stt);
			return;
			break;
		}
		case 0xcb: UnimplementedInstruction(stt); break;
		case 0xcc:
		{
			if (stt->sf.z)
			{
				CALLInstruction(stt);
				return; 
			}
			else
			{
				stt->pc++;
				stt->pc++;
			}
			break;
		}
		case 0xcd:
		{
			CALLInstruction(stt);
			return;
			break;
		}
		case 0xce: 
		{
			ACIInstruction(stt, &(stt->a), &(stt->a));
			break;
		}
		case 0xcf:
		{
			CALLDirectInstruction(stt, 0x8);
			return;
			break;
		}
		case 0xd0:
		{
			if (!(stt->sf.cy))
			{
				RETInstruction(stt);
			}
			break;
		}
		case 0xd1:
		{
			POPInstruction(stt, &(stt->e), &(stt->d));
			break;
		}
		case 0xd2:
		{
			JNCInstruction(stt);
			return;
		}
		case 0xd3:
		{
			OUTInstruction(stt);
			break;
		}
		case 0xd4:
		{
			if (!(stt->sf.cy))
			{
				CALLInstruction(stt);
				return; 
			}
			else
			{
				stt->pc++;
				stt->pc++;
			}
			break;
		}
		case 0xd5:
		{
			PUSHInstruction(stt, &(stt->e), &(stt->d));
			break;
		}
		case 0xd6:
		{
			SUIInstruction(stt, &(stt->a), &(stt->a));
			break;
		}
		case 0xd7:
		{
			CALLDirectInstruction(stt, 0x10);
			return;
			break;
		}
		case 0xd8:
		{
			if (stt->sf.cy)
			{
				RETInstruction(stt);
			}
			break;
		}
		case 0xd9: UnimplementedInstruction(stt); break;
		case 0xda:
		{
			JCInstruction(stt);
			return;
		}
		case 0xdb:
		{
			INInstruction(stt, &(stt->a));
			break;
		}
		case 0xdc:
		{
			if (stt->sf.cy)
			{
				CALLInstruction(stt);
				return; 
			}
			else
			{
				stt->pc++;
				stt->pc++;
			}
			break;
		}
		case 0xdd: UnimplementedInstruction(stt); break;
		case 0xde:
		{
			SBIInstruction(stt, &(stt->a), &(stt->a));
			break;
		}
		case 0xdf:
		{
			CALLDirectInstruction(stt, 0x18);
			return;
			break;
		}
		case 0xe0:
		{
			if (stt->sf.p == 0)
			{
				RETInstruction(stt);
			}
			break;
		}
		case 0xe1:
		{
			POPInstruction(stt, &(stt->l), &(stt->h));
			break;
		}
		case 0xe2:
		{
			JPOInstruction(stt);
			return;
			break;
		}
		case 0xe3:
		{
			unsigned char* firstByte = &(stt->memory[stt->sp]);
			unsigned char* secondByte = &(stt->memory[stt->sp + 1]);
			EXCHANGEInstruction(&(stt->l), firstByte, &(stt->h), secondByte);
			break;
		}
		case 0xe4:
		{
			if (stt->sf.p == 0)
			{
				CALLInstruction(stt);
				return; 
			}
			else
			{
				stt->pc++;
				stt->pc++;
			}
			break;
		}
		case 0xe5:
		{
			PUSHInstruction(stt, &(stt->l), &(stt->h));
			break;
		}
		case 0xe6:
		{
			ANIInstruction(stt, &(stt->a), &(stt->a));
			break;
		}
		case 0xe7:
		{
			CALLDirectInstruction(stt, 0x20);
			return;
			break;
		}
		case 0xe8:
		{
			if (stt->sf.p)
			{
				RETInstruction(stt);
			}
			break;
		}
		case 0xe9:
		{
			PCHLInstruction(stt);
			return;
			break;
		}
		case 0xea:
		{
			JPEInstruction(stt);
			return;
			break;
		}
		case 0xeb:
		{
			EXCHANGEInstruction(&(stt->h), &(stt->d), &(stt->l), &(stt->e));
			break;
		}
		case 0xec:
		{
			if (stt->sf.p)
			{
				CALLInstruction(stt);
				return; 
			}
			else
			{
				stt->pc++;
				stt->pc++;
			}
			break;
		}
		case 0xed: UnimplementedInstruction(stt); break;
		case 0xee:
		{
			XRIInstruction(stt, &(stt->a), &(stt->a));
			break;
		}
		case 0xef:
		{
			CALLDirectInstruction(stt, 0x28);
			return;
			break;
		}
		case 0xf0:
		{
			if (stt->sf.s == 0)
			{
				RETInstruction(stt);
			}
			break;
		}
		case 0xf1:
		{
			POPPSWInstruction(stt);
			break;
		}
		case 0xf2:
		{
			JPInstruction(stt);
			return;
			break;
		}
		case 0xf3:
		{
			DIInstruction(stt);
			break;
		}
		case 0xf4:
		{
			CPInstruction(stt);
			return;
			break;
		}
		case 0xf5:
		{
			// might be wrong
			PUSHPSWInstruction(stt);
			break;
		}
		case 0xf6:
		{
			ORIInstruction(stt, &(stt->a), &(stt->a));
			break;
		}
		case 0xf7:
		{
			CALLDirectInstruction(stt, 0x030);
			return;
			break;
		}
		case 0xf8:
		{
			if (stt->sf.s)
			{
				RETInstruction(stt);
			}
			break;
		}
		case 0xf9:
		{
			SPHLInstruction(stt);
			break;
		}
		case 0xfa:
		{
			JMInstruction(stt);
			return;
			break;
		}
		case 0xfb:
		{
			EIInstruction(stt);
			break;
		}
		case 0xfc:
		{
			if (stt->sf.s)
			{
				CALLInstruction(stt);
				return; 
			}
			else
			{
				stt->pc++;
				stt->pc++;
			}
			break;
		}
		case 0xfd: UnimplementedInstruction(stt); break;
		case 0xfe:
		{
			CPIInstruction(stt, &(stt->a));
			break;
		}
		case 0xff:
		{
			CALLDirectInstruction(stt, 0x038);
			return;
			break;
		}
		default: UnimplementedInstruction(stt); break;
	}
	stt->pc++;
}

unsigned char GetNextByteForMemory(FILE* rom)
{
	unsigned char returnVar = 0;
	if (feof(rom))
	{
		return returnVar;
	}
	int readByte = fgetc(rom);
	returnVar = (unsigned char)readByte;
	return returnVar;
}

void ReadFileIntoMemory(struct State8080* stt, FILE* rom, int startingAddress)
{
	
	fseek(rom, 0, SEEK_END);
	long int fSize = ftell(rom);
	fseek(rom, 0, SEEK_SET);
	fread(&(stt->memory[startingAddress]), fSize, 1, rom);
	fclose(rom);
	// for(;;)
	// {
		// if (feof(rom))
		// {
			// break;
		// }
		// unsigned char currByte = GetNextByteForMemory(rom);
		
	// }
	
}

int enterMain(int argc, char**argv)
{
	(void)argc;
	struct State8080* gameState = Initialize8080StateStruct((struct State8080*)calloc(1, sizeof(struct State8080)));
	assert(argc % 2 == 1);
	for (int i = 1; i < argc; i += 2)
	{
		FILE* rom;
		int offset = (int)strtol(argv[i + 1], NULL, 16);
		if (fopen_safe2(&rom, argv[i], "rb") != 0)
		{
			exit(EXIT_FAILURE);
		}
		ReadFileIntoMemory(gameState, rom, offset);

	}
	time_t lastInterrupt = 0;
 	for (;;)
	{
		printf("things");//%lld", (long long)time(NULL));
		if (time(NULL) - lastInterrupt > 1.0/60.0)
		{
			PerformInterrupt(gameState, 2);
			lastInterrupt = time(NULL);
		}
		Execute8080Op(gameState);
	}

	return 0;
}

















