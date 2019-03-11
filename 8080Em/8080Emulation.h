struct StateFlags 
{
	char z;
	char s;
	char p;
	char cy;
	char ac;
};

struct StateFlags* InitializeStateFlagsStruct(struct StateFlags* sf);

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

struct State8080* Initialize8080StateStruct(struct State8080 *st);

void Execute8080Op(struct State8080 *stt);

int fopen_safe2(FILE **f, const char *name, const char *mode);

unsigned char GetNextByteForMemory(FILE* rom);

void ReadFileIntoMemory(struct State8080* stt, FILE* rom, int startingAddress);