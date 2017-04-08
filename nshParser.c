/*** parser.c  *****from Aho, Sethi, Ullman**************/

#include "global.h"
#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <limits.h>

int lookahead;
int errors = 0;

int counter = 2;
char * DoTempToks[20];
int isDir = 0;

void parse()   /*parses and translates expression list  */
{       
	printf("%s> ",prompt);

        lookahead = yylex(); 

	while(lookahead != DONE){
		parse_start();
		printf("%s> ",prompt);
		if(strcmp(varList[1].value,"1") == 0)
                        printTokens();
	}
	printf("bye \n");
}

void parse_start(){

    
    switch(lookahead){
    
        case SET:
            parse_set();
            break;
        case DO:
            parse_do();
            break;
        case BACK:
            parse_back();
            break;
        case DIR_CMD:
            parse_dir();
            break;
        case PROMPT:
            parse_prompt();
            break;
        case TOVAR:
            parse_tovar();
            break;
        case PROCS:
            parse_procs();
            break;
        case COMMENT:
	    insertTok(currentToken, "comment");
	    lookahead = yylex();
            break;
	case EOL:
	    lookahead = yylex();
	    break;
        default:
		printf("%s\n",currentToken); 
		error("syntax error: invalid command");
		while(lookahead != EOL)
			lookahead = yylex();
    }
}

void parse_set(){

    char * tempTokens[3];
    
    if (lookahead == SET) {
	tempTokens[0] = malloc(sizeof(currentToken));
	strcpy(tempTokens[0],currentToken);
        match(SET);
	if(lookahead == ID){
		tempTokens[1] = malloc(sizeof(currentToken));
        	strcpy(tempTokens[1],currentToken);
        	match(ID);
	}
	else {error("syntax error: expected identifier");errors = 1;}
	tempTokens[2] = malloc(sizeof(currentToken));
        strcpy(tempTokens[2],currentToken);
        parse_Token();
    }
    else {error("syntax error: expected SET");errors = 1;}

    if(errors == 0){

    insertTok(tempTokens[0], "keyword");
    insertTok(tempTokens[1], "variable");
    insertTok(tempTokens[2], "token");

    int key = variableExists(tokList[numOfTokens - 2].value);
    if(key == numOfVars){
    	insertVar(key);
	numOfVars ++;
    }
    else
	insertVar(key);
    }
    else errors = 0;
}

void insertTok(char * tok, char * type){

	tokList[numOfTokens].value = malloc(sizeof(tok));
        strcat(tokList[numOfTokens].value,tok);
	tokList[numOfTokens].type = malloc(sizeof(type));
	strcat(tokList[numOfTokens].type,type);
	numOfTokens ++;
}

void printTokens(){

	int index;
	for(index = 0; index < numOfTokens; index ++){

		printf("%s: %s\n",tokList[index].type,tokList[index].value);
	}
}

void insertVar(int index){

        varList[index].varName = malloc(sizeof(tokList[numOfTokens - 2].value));
        strcat(varList[index].varName,tokList[numOfTokens - 2].value);
        varList[index].value = malloc(sizeof(tokList[numOfTokens - 1].value));
        strcat(varList[index].value,tokList[numOfTokens - 1].value);
}

int variableExists(char * var){

	int index;
	int key = numOfVars;
	for(index = 0; index < numOfVars; index ++){

		if(strcmp(var, varList[index].varName) == 0){
			key = index;
			break;
		}
	}
	return key;
}

void parse_Token(){
    
    if (lookahead == TOKEN || lookahead == ID || lookahead == DIRECTORY || lookahead == NUM) {
        match(lookahead);
    }
    else {error("syntax error: expected token");errors = 1;}
}

void parse_do(){

    counter = 2;
    
    if (lookahead == DO) {
	DoTempToks[0] = malloc(sizeof(currentToken));
	strcpy(DoTempToks[0],currentToken);
        match(DO);
        parse_cmd();
        parse_param();
    }
    else {error("syntax error: expected DO");errors = 1;}

    if(errors == 0){

    insertTok(DoTempToks[0], "keyword");
    insertTok(DoTempToks[1], "Program");

    int i;

    pid_t pid;
    int retval, child_status;

    for(i = 2; i < counter; i ++)
	insertTok(DoTempToks[i], "parameter");

    char *cmd[counter];

    cpyArray(cmd);

    cmd[counter-1] = '\0';

    char * path = malloc(sizeof(varList[0].value));
    strcpy(path,varList[0].value);

    char * str1 = malloc(sizeof(varList[0].value)+6);

    strcpy(str1,"PATH=");

    strcat(str1,path);

    char *env[] = {str1, (char *) 0 };

    char * tmpstr = malloc(sizeof(DoTempToks[1])+6);

    if(isDir == 0){

    strcpy(tmpstr,"/bin/");

    strcat(tmpstr,DoTempToks[1]);
    }
    else{strcpy(tmpstr,DoTempToks[1]);isDir =0;}

    pid = fork();
     if (pid ==0) {

        execve (tmpstr, cmd, env);

	perror(tmpstr);

       exit(0);
     }
     else {

       retval = wait(&child_status); /* block until child terminates */

     }
   } else errors = 0;
}

void cpyArray(char ** cmd){

	int count;
	for(count = 1; count < counter; count ++){

		cmd[count-1] = malloc(sizeof(DoTempToks[count]));
		strcpy(cmd[count-1],DoTempToks[count]);
	}
}

void parse_back(){

    counter = 2;
    
    if (lookahead == BACK) {
	DoTempToks[0] = malloc(sizeof(currentToken));
	strcpy(DoTempToks[0],currentToken);
        match(BACK);
        parse_cmd();
        parse_param();
    }
    else {error("syntax error: expected BACK");errors = 1;}

    if(errors == 0){

    insertTok(DoTempToks[0], "keyword");
    insertTok(DoTempToks[1], "Program");

    int i;

    pid_t pid;
    int retval, child_status;

    for(i = 2; i < counter; i ++)
	insertTok(DoTempToks[i], "parameter");

    char *cmd[counter];

    cpyArray(cmd);

    cmd[counter-1] = '\0';

    char * path = malloc(sizeof(varList[0].value));
    strcpy(path,varList[0].value);

    char * str1 = malloc(sizeof(varList[0].value)+6);

    strcpy(str1,"PATH=");

    strcat(str1,path);

    char *env[] = {str1, (char *) 0 };

    char * tmpstr = malloc(sizeof(DoTempToks[1])+6);

    if(isDir == 0){

    	strcpy(tmpstr,"/bin/");
    	strcat(tmpstr,DoTempToks[1]);
    }
    else{strcpy(tmpstr,DoTempToks[1]);isDir =0;}
    pid = fork();
     if (pid ==0) {

        execve (tmpstr, cmd, env);

	perror(tmpstr);

       exit(0);
     }
     else {
	processes[numOfProcs] = malloc(sizeof(DoTempToks[1]));
	strcpy(processes[numOfProcs],DoTempToks[1]);
	numOfProcs ++;
     }
   }
   else {errors = 0;}
}

void parse_cmd(){
    
    if (lookahead == ID) {
	DoTempToks[1] = malloc(sizeof(currentToken));
        strcpy(DoTempToks[1],currentToken);
        match(lookahead);
    }
    else if(lookahead == DIRECTORY){

	isDir = 1;
	DoTempToks[1] = malloc(sizeof(currentToken));
        strcpy(DoTempToks[1],currentToken);
        match(lookahead);
    }
    else {error("syntax error: expected program name or path");errors = 1;}
}

void parse_param(){
    
    if (lookahead == OPTION || lookahead == TOKEN || lookahead == NUM || lookahead == DIRECTORY || lookahead == ID) {
        parse_par();
        parse_param();
    }
    else return;
}

void parse_par(){
    
    if (lookahead == OPTION || lookahead == TOKEN || lookahead == NUM || lookahead == DIRECTORY || lookahead == ID){

	DoTempToks[counter] = malloc(sizeof(currentToken));
        strcpy(DoTempToks[counter],currentToken);
	counter ++;
        match(lookahead);
    }    
    else {error("syntax error: expected parameter");errors = 1;}
}

void parse_dir(){
    
    char * tempTokens[2];

    int direc = 0;

    if (lookahead == DIR_CMD) {
	tempTokens[0] = malloc(sizeof(currentToken));
        strcpy(tempTokens[0],currentToken);
        match(DIR_CMD);
	if (lookahead == DIRECTORY){
		direc = 1;
		tempTokens[1] = malloc(sizeof(currentToken));
                strcpy(tempTokens[1],currentToken);
        	match(lookahead);
	}
	else if(lookahead == ID){

		currentToken = strtok(currentToken,"$");
		int key = variableExists(currentToken);
		if(key == numOfVars){
			tempTokens[1] = malloc(sizeof(currentToken));
                	strcpy(tempTokens[1],currentToken);
                	match(lookahead);
		}
		else{
			tempTokens[1] = malloc(sizeof(varList[key].value));
			strcpy(tempTokens[1],varList[key].value);
			tempTokens[1] = strtok(tempTokens[1],"\n");
			match(lookahead);
		}
	}
	else if(lookahead == TOKEN){

		currentToken = strtok(currentToken,"\"");
                int key = variableExists(currentToken);
                if(key == numOfVars){
                        tempTokens[1] = malloc(sizeof(currentToken));
                        strcpy(tempTokens[1],currentToken);
                        match(lookahead);
                }
                else{
                        tempTokens[1] = malloc(sizeof(varList[key].value));
                        strcpy(tempTokens[1],varList[key].value);
                        match(lookahead);
                }
	}
	else {error("syntax error: expected directory name");errors = 1;}
    }else {error("syntax error: expected dir");errors = 1;}

    if(errors == 0){

    insertTok(tempTokens[0], "keyword");
    insertTok(tempTokens[1], "directory");

    char * path = malloc(30+sizeof(tempTokens[1]));

    strcpy(path,"/home/samo247/");

    tempTokens[1] = strtok(tempTokens[1],"\"");

    strcat(path,tempTokens[1]);

    int ret;

    if(direc == 0)

    	ret = chdir(path);
    else 
	ret = chdir(tempTokens[1]);

    if(ret != 0)

	if(direc == 0)
		perror(path);
	else
		perror(tempTokens[1]);

    char* cwd;
    char buff[PATH_MAX + 1];

    cwd = getcwd( buff, PATH_MAX + 1 );

    if( cwd != NULL ) {
        printf( "My working directory is %s.\n", cwd );
    }
   }
   else errors = 0;
}

void parse_prompt(){

    char * tempTokens[2];
    
    if (lookahead == PROMPT) {
	tempTokens[0] = malloc(sizeof(currentToken));
        strcpy(tempTokens[0],currentToken);
        match(PROMPT);
	if(lookahead == ID){
		tempTokens[1] = malloc(sizeof(currentToken));
        	strcpy(tempTokens[1],currentToken);
        	match(ID);
	}
	else {error("syntax error: expected identifier");errors = 1;}
    }
    else {error("syntax error: expected prompt");errors = 1;}

    if(errors == 0){

    insertTok(tempTokens[0], "keyword");
    insertTok(tempTokens[1], "prompt name");

    prompt = malloc(sizeof(tempTokens[1]));
    strcpy(prompt, tempTokens[1]);
    }
    else errors = 0;
}

void parse_tovar(){

    counter = 3;   
 
    if (lookahead == TOVAR){
        DoTempToks[0] = malloc(sizeof(currentToken));
	strcpy(DoTempToks[0],currentToken);
        match(TOVAR);
	DoTempToks[1] = malloc(sizeof(currentToken));
	strcpy(DoTempToks[1],currentToken);
        match(ID);
	if (lookahead == ID) {
		DoTempToks[2] = malloc(sizeof(currentToken));
        	strcpy(DoTempToks[2],currentToken);
        	match(lookahead);
    	}
        else if (lookahead == DIRECTORY){
	
		isDir = 1;
		DoTempToks[2] = malloc(sizeof(currentToken));
                strcpy(DoTempToks[2],currentToken);
                match(lookahead);
	}
	else {error("syntax error: expected program");errors = 1;}
        parse_param();
    }
    else {error("syntax error: expected tovar");errors = 1;}

    if(errors == 0){

    insertTok(DoTempToks[0], "keyword");
    insertTok(DoTempToks[1], "variable");
    insertTok(DoTempToks[2], "program");

    int key = variableExists(DoTempToks[1]);

    varList[key].varName = malloc(sizeof(DoTempToks[1]));
        strcat(varList[key].varName,DoTempToks[1]);

   if(key == numOfVars)

	numOfVars ++;
    

    int i;

    pid_t pid;
    int retval, child_status;

    for(i = 3; i < counter; i ++)
	insertTok(DoTempToks[i], "parameter");

    char *cmd[counter-1];

    cpyArray2(cmd);

    cmd[counter-2] = '\0';

    /*for(i = 0; i < counter - 2; i ++)
	printf("%s\n",cmd[i]);*/

    char * path = malloc(sizeof(varList[0].value));
    strcpy(path,varList[0].value);

    char * str1 = malloc(sizeof(varList[0].value)+6);

    strcpy(str1,"PATH=");

    strcat(str1,path);

    char *env[] = {str1, (char *) 0 };

    char * tmpstr = malloc(sizeof(DoTempToks[2])+6);

   if(isDir == 0){

    	strcpy(tmpstr,"/bin/");
    	strcat(tmpstr,DoTempToks[2]);
    }
    else{strcpy(tmpstr,DoTempToks[2]);isDir =0;}

    int pipefd[2];
    pipe(pipefd);

    pid = fork();
     if (pid ==0) {

	close(pipefd[0]);    // close reading end in the child

    dup2(pipefd[1], 1);  // send stdout to the pipe
    dup2(pipefd[1], 2);  // send stderr to the pipe

    close(pipefd[1]);    // this descriptor is no longer needed

        execve (tmpstr, cmd, env);

	perror(tmpstr);

       exit(0);
     }
     else {

       retval = wait(&child_status); 

        char buffer[1024];

    close(pipefd[1]);  // close the write end of the pipe in the parent

    varList[key].value = malloc(100);

    while (read(pipefd[0], buffer, sizeof(buffer)) != 0)
    {
        strcat(varList[key].value,buffer);
    }
   }
  }
  else errors = 0;
}

void cpyArray2(char ** cmd){

        int count;
        for(count = 2; count < counter; count ++){

                cmd[count-2] = malloc(sizeof(DoTempToks[count]));
                strcpy(cmd[count-2],DoTempToks[count]);
        }
}

void parse_procs(){
    
    char * tempTokens[1];

    if (lookahead == PROCS) {
        tempTokens[0] = malloc(sizeof(currentToken));
        strcpy(tempTokens[0],currentToken);
        match(PROCS);
    }
    else{ error("syntax error: expected procs");errors = 1;}

    if(errors == 0){
     
    insertTok(tempTokens[0], "keyword");

    printf("\n");

    int i;
    for(i = 0; i < numOfProcs; i++)
	printf("%s\n",processes[i]);
    }
    else errors = 0;
}

void parse_done(){
    
    if (lookahead == DONE) {
        match(DONE);
    }
    else error("syntax error: expected done");
    printf("bye\n");
    exit(0);
}

void match(t)
        int t;
{
        if (lookahead == t)
                lookahead = yylex();
        else{
		errors = 1; 
		error("syntax error - unexpected token");
	}
}

                                                          


