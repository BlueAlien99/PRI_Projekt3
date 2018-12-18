#ifndef IOHANDLER_H
#define IOHANDLER_H

#include <stddef.h>

#include "Utilities.h"
#include "PatientsDB.h"

#define MAX_FGETS 128
#define MAX_SCANF 64
#define LEN(S) "%"#S"s"
#define MLEN(S) LEN(S)

int getInt();
void getPath(char*);
void saveFile(Patient*);
void readFile(Patient**, Patient**);
_Bool readChar(FILE*, char);
_Bool readString(FILE*, const char*, char*);

#endif
