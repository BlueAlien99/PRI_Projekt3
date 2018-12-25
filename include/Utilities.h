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
_Bool getString(char str[]);
_Bool getStringForm(char str[], const char form[]);
_Bool validateString(char str[]);
_Bool verifyPesel(char p[], int sex);
void upFirstLowRest(char str[]);
int getInt();
int getIntForm(const char form[]);
char* strGen(int min, int max);
char* numGen(int l);
int intGen(int min, int max);
int max(int a, int b);
int min(int a, int b);

#endif
