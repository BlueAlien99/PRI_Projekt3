#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <stddef.h>

#include "Utilities.h"
#include "PatientsDB.h"

#define MAX_FGETS 128

void getPath(char*, _Bool);
void saveFile(Patient*, _Bool);
void readFile(Patient**, Patient**, _Bool);
_Bool readChar(FILE*, char);
_Bool readString(FILE*, const char*, char*);

#endif
