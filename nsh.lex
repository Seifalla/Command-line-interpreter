%option noyywrap

%{
#include "global.h"
#include <math.h>
%}

delim           [\t ]
endOfLine	[\n]
ws              {delim}+
digit           [0-9]
num		{digit}+
alpha 		[a-zA-Z]
identifier      {alpha}({alpha}|{digit})*|[$]{alpha}({alpha}|{digit})*
comment		[%]([\40-\44]|[\46-\176]|{alpha}|{digit}|[ ])*[\n]
value		["]([\40-\41]|[\43-\44]|[\46-\176]|{alpha}|{digit})+["]
dir		[\56-\57]({alpha}|{digit}|[\56-\57])*
option		[-]({alpha})+

%%

{ws}            {/* skip blanks and tabs*/}

{endOfLine} {return EOL;}

{option} {
	currentToken = malloc(sizeof(yytext));
	strcpy(currentToken,yytext);
	return OPTION;
}

{num} {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return NUM;
}

{value} {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return TOKEN;
}

{dir} {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return DIRECTORY;
}

"set" {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return SET;
}

"prompt" {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return PROMPT;
}

"dir" {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return DIR_CMD;
}

"procs" {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return PROCS;
}

"done" {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return DONE;
}

<<EOF>>         {return DONE;}

"do" {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return DO;
}

"back" {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
        return BACK;
}

"tovar" {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
        return TOVAR;
}

{identifier} {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return ID;
}

{comment} {
	currentToken = malloc(sizeof(yytext));
        strcpy(currentToken,yytext);
	return COMMENT;
}

%%
