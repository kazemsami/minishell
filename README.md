 # 42's Minishell project
 
 
Minishell is a partial replica of the UNIX shell and command language Bash written in the C lanugage.
 
 ### This project's tasks include
 
 * Parsing input
 * Executing commands with piping functionality
 * Rebuilding the commands echo, cat, export unset, pwd, cd, env
 * Handling environmental variables
 * Handling Redirections

### Installation

HTTPS
```
git clone https://github.com/kazemsami/minishell.git
```
SSH
```
git clone git@github.com:kazemsami/minishell.git
```
```
$ cd minishell
$ make
```
#### If for example you have already built the progam and would like to run it on a docker container
`$ make re` which will force clean all files and redo the build.

### Usage
`$ ./minishell`
