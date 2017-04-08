/***global.h******from Aho, Sethi, Ullman*************************************/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#define NUM 256
#define ID  257
#define COMMENT 258
#define TOKEN 259
#define DIRECTORY 260
#define OPTION 261
#define SET 262
#define PROMPT 263
#define PROCS 264
#define DONE 265
#define DO 266
#define BACK 267
#define TOVAR 268
#define DIR_CMD 269
#define EOL 270

#define  SYMMAX 100   /* size of symtable */

char yystring[1000];
int yylex();

int tokenval;    /* value of token atribute  */
int lineno;

char * prompt;

char * processes[SYMMAX];

int numOfProcs;

int numOfVars;

struct variable {
	char * varName;
	char * value;
};

struct variable varList[SYMMAX];

struct token {

	char * value;
	char * type;
};

int numOfTokens;

struct token tokList[SYMMAX];

char * currentToken;

void error(char *m);
void match(int t);

void insertVar(int index);
void printTokens();
void insertTok(char * tok, char * type);

void cpyArray(char ** cmd);
void cpyArray2(char ** cmd);


void parse();
void parse_start();
void parse_set();
void parse_Token();
void parse_do();
void parse_back();
void parse_cmd();
void parse_param();
void parse_par();
void parse_dir();
void parse_prompt();
void parse_tovar();
void parse_procs();
void parse_done();


void match(int t);

int lexan();
void emit(int t, int tval);
void init();
void exit(int n);
int main();

