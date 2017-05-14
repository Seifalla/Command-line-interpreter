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

This software runs on Linux 4.4.0-34-generic x86_64 (DMB 005)

This program supports the following commands:

set variable value

Here, variable is any reasonable variable name (starting with a letter, continuing with letters or numbers), and value is a token. It is conventional for users to represent variables in ALL CAPITALS, but nsh does not enforce this convention. Variable names are case-sensitive, that is, home and HOME represent different variables. The effect of this command is to associate the name with the value of the variable in a data structure inside nsh.
prompt newPrompt

Set the shell prompt to newPrompt, which is a token. Do not add or subtract spaces at the end of the new prompt. The initial prompt in nsh is nsh > . (There is a space after the >.)
dir directoryName
This command changes the current directory to directoryName. The dir command must have a single parameter. See the getwd(3) and chdir(2) system calls. the directoryName may be either absolute (starting with /) or relative (not starting with /).
procs

nsh lists all processes running in the background, in any format you like. nsh should keep a list and not rely on external programs like ps to create its output.
done

nsh exits with exit status 0. nsh should also accept <control-D> (end-of-file) on the input stream and treat it as if the user had typed done. That is, if a user types <control-D> at the input, nsh performs exactly the same as when it receives the built-in command done.
Program-control commands

do cmd param*
The user submits a do command to execute a program. The keyword do must appear as the first token on the command line, followed by the command to be executed. Here, cmd is a token that specifies the filename of the program the user wants to execute. It is followed by zero or more tokens specifying parameters. nsh should wait for the program to finish before it prompts for and accepts the next command.
nsh looks for cmd in a list of directories indicated by the variable PATH, whose value is a colon-separated list of directories. By default, PATH has value /bin:/usr/bin; the user can change that value by assigning a new value to PATH. If, however, cmd starts with a / character, it is a full path name starting at the root. Similarly, a cmd that starts with ./ is a path name starting in the current directory.

back cmd param* 
The back command is identical to the do command, except that the program should run in the background, that is, nsh should immediately prompt for and accept the next command.
tovar variable cmd param*

The tovar command executes the program cmd along with its parameters, if any, and assigns its output to the variable specified by variable. Like the do command, the variable PATH contains a colon-separated list of directories where nsh looks for the file to be executed. The file name to be executed may also be specified as a full path name or a name relative to the current directory.

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




