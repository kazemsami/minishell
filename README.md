 # 42's Minishell project
 
 
Minishell is a partial replica of the UNIX shell and command language Bash written in the C lanugage. Thank you [Anastasia](https://github.com/Anastasiia-Ni) for being a wonderful partner in this long project.

<img width="1630" alt="Minishell-img" src="https://user-images.githubusercontent.com/74882142/201451249-6bfb40db-f931-42b7-9bc3-335f64ad61dc.png">
 
 ### Project tasks include
 
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

### Tester
This minishell works with this updated [Lucus Kuhn minishell tester](https://github.com/LucasKuhn/minishell_tester). If you want to try it with this tester then make sure you comment out `print_minishell();` on line 104 in ./src/main/minishell.c
