/*** main.c  * from Aho, Sethi, Ullman**/

#include "global.h"

int main()
{
	numOfVars = 0;
	numOfTokens = 0;
	numOfProcs = 0;
	varList[0].varName = "PATH";
	varList[0].value = "/bin:/usr/bin";
	numOfVars ++;
	varList[1].varName = "ShowTokens";
        varList[1].value = "0";
	numOfVars ++;
        lineno = 1; /* Update with Milestone 2 */
	prompt = malloc(4);
	strcpy(prompt,"nsh");
	parse();
	exit(0);  /* successful termination */
}

/********************************************************************/
