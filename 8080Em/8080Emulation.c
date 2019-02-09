#include<stdlib.h>

struct StateFlags 
{
	char z;
	char s;
	char p;
	char cy;
	char ac;
};

struct StateFlags* InitializeStateFlagsStruct(struct StateFlags *sf)
{
	sf->z  = 0;
	sf->s  = 0;
	sf->p  = 0;
	sf->cy = 0;
	sf->ac = 0;
	return sf;
}

struct State8080
{
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	unsigned char e;
	unsigned char h;
	unsigned char l;
	unsigned short interrupt_enable;
	unsigned short sp;
	unsigned short pc;
	unsigned char* memory;
	struct StateFlags sf;
};

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
	st->memory = malloc(sizeof(unsigned char) * 16000);
	InitializeStateFlagsStruct(&(st->sf));
	return st;
}

void DoThingBasedOffState(struct State8080 *stt)
{
}

















