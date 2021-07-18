# 42sh - A shell program based on tcsh

## Built-ins:
- cd
- setenv
- unsetenv
- alias
- foreach
- if
- set
- exit
- echo
- repeat
- where
- which

## Redirections:
redirect the standard output into files or commands
- pipe `|`
- right redirection `>`
- double right redirection `>>`
- left redirection `<`
- double left redirection `<<`

## Multi-command execution:
- `;` normal separator
- `&&` and separator
- `||` or separator

## Globings:
Use special characters to match current directory file names according to pattern
ex: `[a-z]*`

## Subshell:
Use parenthesis to execute commands in a subshell that wont affect current state
ex: 
```
(cd ..; echo $PWD); echo $PWD
```

## Line command substitution
Use magic quotes to input a command into the line
ex:
```
echo `ls`
```

## Cute prompt:
- Colored arrow (reflects last command's return value)
- Current working directory
- Current git branch, if any

Credits: Amoz Pay, Célèste Cote, Floriane Peteau, Nicolas Saclier
