#ifndef UTILITIES_H
#define UTILITIES_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 64
#define LEN(S) "%"#S"s"
#define MLEN(S) LEN(S)

_Bool clearBuffer();
_Bool getString();
_Bool getStringForm();
_Bool validateString(char*);
int getInt();
char* strGen();

#endif
