#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <limits.h>
#include <stddef.h>

#include "Utilities.h"
#include "PatientsDB.h"

#define MAX_FGETS 128
#define MAX_SCANF 64

void getPath(char*, _Bool);
void saveFile(Patient*);
void readFile(Patient**, Patient**);
_Bool readChar(FILE*, char);
_Bool readString(FILE*, const char*, char*);
_Bool readInt(FILE*, const char*, int*);
void saveFileBin(Patient*);
void readFileBin(Patient**, Patient**);

#endif
