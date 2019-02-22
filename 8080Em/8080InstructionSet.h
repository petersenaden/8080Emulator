#ifndef EMULATION8080
#define EMULATION8080
#include "8080Emulation.h"
#endif

void UnimplementedInstruction(struct State8080* stt);
void CheckFlags(struct State8080* stt, unsigned char checkByte, bool checkSignFlag, bool checkZeroFlag, bool checkParityFlag);

void LXIInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo);
void STAXInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* destByte);
void INXInstruction(unsigned char* byteOne, unsigned char* byteTwo);
void INRInstruction(struct State8080* stt, unsigned char* byteOne);
void DCRInstruction(struct State8080* stt, unsigned char* byteOne);
void MVIInstruction(struct State8080* stt, unsigned char* byteOne);
void RLCInstruction(struct State8080* stt, unsigned char* byteOne);
void DADInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* byteThree, unsigned char* byteFour);
void LDAXInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* destByte);
void DCXInstruction(unsigned char* byteOne, unsigned char* byteTwo);
void RRCInstruction(struct State8080* stt, unsigned char* byteOne);
void RARInstruction(struct State8080* stt, unsigned char* byteOne);
void DAAInstruction();
void SHLDInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* destByteOne, unsigned char* destByteTwo);
void LHLDInstruction(struct State8080* stt, unsigned char* byteOne, unsigned char* byteTwo, unsigned char* destByteOne, unsigned char* destByteTwo);
void CMAInstruction(unsigned char* byteOne);
void STCInstruction(struct State8080* stt);
void CMCInstruction(struct State8080* stt);
void MOVInstruction(unsigned char* byteOne, unsigned char* byteTwo);
void RALInstruction(struct State8080* stt, unsigned char* byteOne);