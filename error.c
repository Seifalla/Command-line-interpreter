/***********  error.c **from Aho, Sethi, Ullman***********/

#include "global.h"

void error(m)    /*generate all error messagese */
	char *m;
{
	fprintf(stderr, "%s\n", m);
}

