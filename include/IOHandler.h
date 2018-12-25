#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utilities.h"
#include "PatientsDB.h"

#define MAX_FGETS 128
#define MAX_SCANF 64

void getPath(char path[], _Bool bin);
void saveFile(Patient *head);
void readFile(Patient **head, Patient **tail);
_Bool readChar(FILE *file, char c, char *readchar);
_Bool readString(FILE *file, const char str[], char des[]);
_Bool readInt(FILE *file, const char str[], int *n);
void saveFileBin(Patient *head);
void readFileBin(Patient **head, Patient **tail);

#endif
