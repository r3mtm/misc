#!/bin/bash

#Setting font colors in bash
#Refer man console_codes for escape sequences and codes

RED="\x1b[0;1;32m"
DEF="\x1b[0m"

printf "${RED}Hello${DEF}"

#\e is equivalent to \x1b or \033 in bash.
#However bash only permits octal numbers when used with variables like PS1 etc.
#Refer man bash (PROMPTING section) for bash prompt escape sequences and such details.

export PS1="\e[0;1;31m[\u@\h \W]#\e[0m "
