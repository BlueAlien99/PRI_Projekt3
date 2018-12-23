#ifndef UTILITIES_H
#define UTILITIES_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR 64
#define PESEL_LEN 11
#define LEN(S) "%"#S"s"
#define MLEN(S) LEN(S)

typedef unsigned int uint;
typedef long long llong;

_Bool clearBuffer();
_Bool getString();
_Bool getStringForm();
_Bool validateString(char*);
void upFirstLowRest(char*);
int getInt();
int getIntForm();
char* strGen();
int intGen();
int max();
int min();

#endif
