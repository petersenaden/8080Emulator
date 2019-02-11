#ifndef EMULATION8080
#define EMULATION8080
#include "8080Emulation.h"
#endif

void UnimplementedInstruction(struct State8080* stt);
void CheckFlags(unsigned char* resultByte, bool checkCarryFlag, bool checkACFlag, bool checkSignFlag, bool checkZeroFlag, bool checkParityFlag);

void LXIInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo);
void STAXInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* destByte);
void INXInstruction(unsigned char* byteOne, unsigned char* byteTwo);