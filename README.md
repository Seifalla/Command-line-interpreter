# Command-line-interpreter
Author: Seifalla Moustafa

File names:

- error.c
- global.h
- nshParser.c
- main.c
- Makefile
- nsh.lex

Description:

The two main components of this projects are the scanner and the parser. I used the software lex to generate the scanner. The parser was written by hand. The kind of parser I wrote is the recursive-descent parser. It is based on the 
following context-free grammar:

start -> keywords

Set -> “set” identifier Token

Token -> token|identifier|dir|num

Do -> “do” Cmd Param

Back -> “back” Cmd Param

Cmd -> identifier| dir

Param -> Par Param|lambda

Par -> option|token|num|dir|identifier

Dir -> “dir” dir

Prompt -> “prompt” identifier

Tovar -> “tovar” identifier identifier Param

Procs -> “procs”

Done -> “done”

Limitations:

- directories' names must not be surrounded by double-quotes.
- variable substitution is done only in the dir command
- The "do" command doesn't look up the file name in the list of directories(PATH)




