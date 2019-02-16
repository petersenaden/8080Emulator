#include<stdlib.h>
#ifndef EMULATION8080
#define EMULATION8080
#include "8080Emulation.h"
#endif

#ifndef INSTRUCTIONSET8080
#define INSTRUCTIONSET8080
#include "8080InstructionSet.h"
#endif

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
	st->sp = 0;
	st->pc = 0;
	st->memory = (unsigned char*)(calloc(16000, sizeof(unsigned char)));
	InitializeStateFlagsStruct(&(st->sf));
	return st;
}

void Execute8080Op(struct State8080 *stt)
{
	unsigned char *currOp = &(stt->memory[stt->pc]);
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
		case 0x12: UnimplementedInstruction(stt); break;
		case 0x13: UnimplementedInstruction(stt); break;
		case 0x14: UnimplementedInstruction(stt); break;
		case 0x15: UnimplementedInstruction(stt); break;
		case 0x16: UnimplementedInstruction(stt); break;
		case 0x17: UnimplementedInstruction(stt); break;
		case 0x18: UnimplementedInstruction(stt); break;
		case 0x19: UnimplementedInstruction(stt); break;
		case 0x1a: UnimplementedInstruction(stt); break;
		case 0x1b: UnimplementedInstruction(stt); break;
		case 0x1c: UnimplementedInstruction(stt); break;
		case 0x1d: UnimplementedInstruction(stt); break;
		case 0x1e: UnimplementedInstruction(stt); break;
		case 0x1f: UnimplementedInstruction(stt); break;
		case 0x20: UnimplementedInstruction(stt); break;
		case 0x21: UnimplementedInstruction(stt); break;
		case 0x22: UnimplementedInstruction(stt); break;
		case 0x23: UnimplementedInstruction(stt); break;
		case 0x24: UnimplementedInstruction(stt); break;
		case 0x25: UnimplementedInstruction(stt); break;
		case 0x26: UnimplementedInstruction(stt); break;
		case 0x27: UnimplementedInstruction(stt); break;
		case 0x28: UnimplementedInstruction(stt); break;
		case 0x29: UnimplementedInstruction(stt); break;
		case 0x2a: UnimplementedInstruction(stt); break;
		case 0x2b: UnimplementedInstruction(stt); break;
		case 0x2c: UnimplementedInstruction(stt); break;
		case 0x2d: UnimplementedInstruction(stt); break;
		case 0x2e: UnimplementedInstruction(stt); break;
		case 0x2f: UnimplementedInstruction(stt); break;
		case 0x30: UnimplementedInstruction(stt); break;
		case 0x31: UnimplementedInstruction(stt); break;
		case 0x32: UnimplementedInstruction(stt); break;
		case 0x33: UnimplementedInstruction(stt); break;
		case 0x34: UnimplementedInstruction(stt); break;
		case 0x35: UnimplementedInstruction(stt); break;
		case 0x36: UnimplementedInstruction(stt); break;
		case 0x37: UnimplementedInstruction(stt); break;
		case 0x38: UnimplementedInstruction(stt); break;
		case 0x39: UnimplementedInstruction(stt); break;
		case 0x3a: UnimplementedInstruction(stt); break;
		case 0x3b: UnimplementedInstruction(stt); break;
		case 0x3c: UnimplementedInstruction(stt); break;
		case 0x3d: UnimplementedInstruction(stt); break;
		case 0x3e: UnimplementedInstruction(stt); break;
		case 0x3f: UnimplementedInstruction(stt); break;
		case 0x40: UnimplementedInstruction(stt); break;
		case 0x41: UnimplementedInstruction(stt); break;
		case 0x42: UnimplementedInstruction(stt); break;
		case 0x43: UnimplementedInstruction(stt); break;
		case 0x44: UnimplementedInstruction(stt); break;
		case 0x45: UnimplementedInstruction(stt); break;
		case 0x46: UnimplementedInstruction(stt); break;
		case 0x47: UnimplementedInstruction(stt); break;
		case 0x48: UnimplementedInstruction(stt); break;
		case 0x49: UnimplementedInstruction(stt); break;
		case 0x4a: UnimplementedInstruction(stt); break;
		case 0x4b: UnimplementedInstruction(stt); break;
		case 0x4c: UnimplementedInstruction(stt); break;
		case 0x4d: UnimplementedInstruction(stt); break;
		case 0x4e: UnimplementedInstruction(stt); break;
		case 0x4f: UnimplementedInstruction(stt); break;
		case 0x50: UnimplementedInstruction(stt); break;
		case 0x51: UnimplementedInstruction(stt); break;
		case 0x52: UnimplementedInstruction(stt); break;
		case 0x53: UnimplementedInstruction(stt); break;
		case 0x54: UnimplementedInstruction(stt); break;
		case 0x55: UnimplementedInstruction(stt); break;
		case 0x56: UnimplementedInstruction(stt); break;
		case 0x57: UnimplementedInstruction(stt); break;
		case 0x58: UnimplementedInstruction(stt); break;
		case 0x59: UnimplementedInstruction(stt); break;
		case 0x5a: UnimplementedInstruction(stt); break;
		case 0x5b: UnimplementedInstruction(stt); break;
		case 0x5c: UnimplementedInstruction(stt); break;
		case 0x5d: UnimplementedInstruction(stt); break;
		case 0x5e: UnimplementedInstruction(stt); break;
		case 0x5f: UnimplementedInstruction(stt); break;
		case 0x60: UnimplementedInstruction(stt); break;
		case 0x61: UnimplementedInstruction(stt); break;
		case 0x62: UnimplementedInstruction(stt); break;
		case 0x63: UnimplementedInstruction(stt); break;
		case 0x64: UnimplementedInstruction(stt); break;
		case 0x65: UnimplementedInstruction(stt); break;
		case 0x66: UnimplementedInstruction(stt); break;
		case 0x67: UnimplementedInstruction(stt); break;
		case 0x68: UnimplementedInstruction(stt); break;
		case 0x69: UnimplementedInstruction(stt); break;
		case 0x6a: UnimplementedInstruction(stt); break;
		case 0x6b: UnimplementedInstruction(stt); break;
		case 0x6c: UnimplementedInstruction(stt); break;
		case 0x6d: UnimplementedInstruction(stt); break;
		case 0x6e: UnimplementedInstruction(stt); break;
		case 0x6f: UnimplementedInstruction(stt); break;
		case 0x70: UnimplementedInstruction(stt); break;
		case 0x71: UnimplementedInstruction(stt); break;
		case 0x72: UnimplementedInstruction(stt); break;
		case 0x73: UnimplementedInstruction(stt); break;
		case 0x74: UnimplementedInstruction(stt); break;
		case 0x75: UnimplementedInstruction(stt); break;
		case 0x76: UnimplementedInstruction(stt); break;
		case 0x77: UnimplementedInstruction(stt); break;
		case 0x78: UnimplementedInstruction(stt); break;
		case 0x79: UnimplementedInstruction(stt); break;
		case 0x7a: UnimplementedInstruction(stt); break;
		case 0x7b: UnimplementedInstruction(stt); break;
		case 0x7c: UnimplementedInstruction(stt); break;
		case 0x7d: UnimplementedInstruction(stt); break;
		case 0x7e: UnimplementedInstruction(stt); break;
		case 0x7f: UnimplementedInstruction(stt); break;
		case 0x80: UnimplementedInstruction(stt); break;
		case 0x81: UnimplementedInstruction(stt); break;
		case 0x82: UnimplementedInstruction(stt); break;
		case 0x83: UnimplementedInstruction(stt); break;
		case 0x84: UnimplementedInstruction(stt); break;
		case 0x85: UnimplementedInstruction(stt); break;
		case 0x86: UnimplementedInstruction(stt); break;
		case 0x87: UnimplementedInstruction(stt); break;
		case 0x88: UnimplementedInstruction(stt); break;
		case 0x89: UnimplementedInstruction(stt); break;
		case 0x8a: UnimplementedInstruction(stt); break;
		case 0x8b: UnimplementedInstruction(stt); break;
		case 0x8c: UnimplementedInstruction(stt); break;
		case 0x8d: UnimplementedInstruction(stt); break;
		case 0x8e: UnimplementedInstruction(stt); break;
		case 0x8f: UnimplementedInstruction(stt); break;
		case 0x90: UnimplementedInstruction(stt); break;
		case 0x91: UnimplementedInstruction(stt); break;
		case 0x92: UnimplementedInstruction(stt); break;
		case 0x93: UnimplementedInstruction(stt); break;
		case 0x94: UnimplementedInstruction(stt); break;
		case 0x95: UnimplementedInstruction(stt); break;
		case 0x96: UnimplementedInstruction(stt); break;
		case 0x97: UnimplementedInstruction(stt); break;
		case 0x98: UnimplementedInstruction(stt); break;
		case 0x99: UnimplementedInstruction(stt); break;
		case 0x9a: UnimplementedInstruction(stt); break;
		case 0x9b: UnimplementedInstruction(stt); break;
		case 0x9c: UnimplementedInstruction(stt); break;
		case 0x9d: UnimplementedInstruction(stt); break;
		case 0x9e: UnimplementedInstruction(stt); break;
		case 0x9f: UnimplementedInstruction(stt); break;
		case 0xa0: UnimplementedInstruction(stt); break;
		case 0xa1: UnimplementedInstruction(stt); break;
		case 0xa2: UnimplementedInstruction(stt); break;
		case 0xa3: UnimplementedInstruction(stt); break;
		case 0xa4: UnimplementedInstruction(stt); break;
		case 0xa5: UnimplementedInstruction(stt); break;
		case 0xa6: UnimplementedInstruction(stt); break;
		case 0xa7: UnimplementedInstruction(stt); break;
		case 0xa8: UnimplementedInstruction(stt); break;
		case 0xa9: UnimplementedInstruction(stt); break;
		case 0xaa: UnimplementedInstruction(stt); break;
		case 0xab: UnimplementedInstruction(stt); break;
		case 0xac: UnimplementedInstruction(stt); break;
		case 0xad: UnimplementedInstruction(stt); break;
		case 0xae: UnimplementedInstruction(stt); break;
		case 0xaf: UnimplementedInstruction(stt); break;
		case 0xb0: UnimplementedInstruction(stt); break;
		case 0xb1: UnimplementedInstruction(stt); break;
		case 0xb2: UnimplementedInstruction(stt); break;
		case 0xb3: UnimplementedInstruction(stt); break;
		case 0xb4: UnimplementedInstruction(stt); break;
		case 0xb5: UnimplementedInstruction(stt); break;
		case 0xb6: UnimplementedInstruction(stt); break;
		case 0xb7: UnimplementedInstruction(stt); break;
		case 0xb8: UnimplementedInstruction(stt); break;
		case 0xb9: UnimplementedInstruction(stt); break;
		case 0xba: UnimplementedInstruction(stt); break;
		case 0xbb: UnimplementedInstruction(stt); break;
		case 0xbc: UnimplementedInstruction(stt); break;
		case 0xbd: UnimplementedInstruction(stt); break;
		case 0xbe: UnimplementedInstruction(stt); break;
		case 0xbf: UnimplementedInstruction(stt); break;
		case 0xc0: UnimplementedInstruction(stt); break;
		case 0xc1: UnimplementedInstruction(stt); break;
		case 0xc2: UnimplementedInstruction(stt); break;
		case 0xc3: UnimplementedInstruction(stt); break;
		case 0xc4: UnimplementedInstruction(stt); break;
		case 0xc5: UnimplementedInstruction(stt); break;
		case 0xc6: UnimplementedInstruction(stt); break;
		case 0xc7: UnimplementedInstruction(stt); break;
		case 0xc8: UnimplementedInstruction(stt); break;
		case 0xc9: UnimplementedInstruction(stt); break;
		case 0xca: UnimplementedInstruction(stt); break;
		case 0xcb: UnimplementedInstruction(stt); break;
		case 0xcc: UnimplementedInstruction(stt); break;
		case 0xcd: UnimplementedInstruction(stt); break;
		case 0xce: UnimplementedInstruction(stt); break;
		case 0xcf: UnimplementedInstruction(stt); break;
		case 0xd0: UnimplementedInstruction(stt); break;
		case 0xd1: UnimplementedInstruction(stt); break;
		case 0xd2: UnimplementedInstruction(stt); break;
		case 0xd3: UnimplementedInstruction(stt); break;
		case 0xd4: UnimplementedInstruction(stt); break;
		case 0xd5: UnimplementedInstruction(stt); break;
		case 0xd6: UnimplementedInstruction(stt); break;
		case 0xd7: UnimplementedInstruction(stt); break;
		case 0xd8: UnimplementedInstruction(stt); break;
		case 0xd9: UnimplementedInstruction(stt); break;
		case 0xda: UnimplementedInstruction(stt); break;
		case 0xdb: UnimplementedInstruction(stt); break;
		case 0xdc: UnimplementedInstruction(stt); break;
		case 0xdd: UnimplementedInstruction(stt); break;
		case 0xde: UnimplementedInstruction(stt); break;
		case 0xdf: UnimplementedInstruction(stt); break;
		case 0xe0: UnimplementedInstruction(stt); break;
		case 0xe1: UnimplementedInstruction(stt); break;
		case 0xe2: UnimplementedInstruction(stt); break;
		case 0xe3: UnimplementedInstruction(stt); break;
		case 0xe4: UnimplementedInstruction(stt); break;
		case 0xe5: UnimplementedInstruction(stt); break;
		case 0xe6: UnimplementedInstruction(stt); break;
		case 0xe7: UnimplementedInstruction(stt); break;
		case 0xe8: UnimplementedInstruction(stt); break;
		case 0xe9: UnimplementedInstruction(stt); break;
		case 0xea: UnimplementedInstruction(stt); break;
		case 0xeb: UnimplementedInstruction(stt); break;
		case 0xec: UnimplementedInstruction(stt); break;
		case 0xed: UnimplementedInstruction(stt); break;
		case 0xee: UnimplementedInstruction(stt); break;
		case 0xef: UnimplementedInstruction(stt); break;
		case 0xf0: UnimplementedInstruction(stt); break;
		case 0xf1: UnimplementedInstruction(stt); break;
		case 0xf2: UnimplementedInstruction(stt); break;
		case 0xf3: UnimplementedInstruction(stt); break;
		case 0xf4: UnimplementedInstruction(stt); break;
		case 0xf5: UnimplementedInstruction(stt); break;
		case 0xf6: UnimplementedInstruction(stt); break;
		case 0xf7: UnimplementedInstruction(stt); break;
		case 0xf8: UnimplementedInstruction(stt); break;
		case 0xf9: UnimplementedInstruction(stt); break;
		case 0xfa: UnimplementedInstruction(stt); break;
		case 0xfb: UnimplementedInstruction(stt); break;
		case 0xfc: UnimplementedInstruction(stt); break;
		case 0xfd: UnimplementedInstruction(stt); break;
		case 0xfe: UnimplementedInstruction(stt); break;
		case 0xff: UnimplementedInstruction(stt); break;
		default:   UnimplementedInstruction(stt); break;
	}
	stt->pc++;
}

















