

struct StateFlags 
{
	char z;
	char s;
	char p;
	char cy;
	char ac;
};

struct StateFlags* InitializeStateFlagsStruct(struct StateFlags* sf)
{
	sf->z  = 0;
	sf->s  = 0;
	sf->p  = 0;
	sf->cy = 0;
	sf->ac = 0;
	return sf;
}