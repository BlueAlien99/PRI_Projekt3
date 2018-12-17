#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <stddef.h>

#include "PatientsDB.h"

#define MAX_FGETS 128

void saveFile();
void readFile();
_Bool readChar(FILE*, char);
_Bool readString(FILE*, const char*, char*);

#endif
