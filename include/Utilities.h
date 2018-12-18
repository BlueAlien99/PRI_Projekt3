#ifndef UTILITIES_H
#define UTILITIES_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 64
#define LEN(S) "%"#S"s"
#define MLEN(S) LEN(S)

_Bool clearBuffer();
_Bool getString();
int getInt();
char* strGen();

#endif
