#ifndef PATIENTSDB_H
#define PATIENTSDB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utilities.h"

#define MAX_STR 64

extern const char K_NAME[];
extern const char K_SURNAME[];

typedef struct Patient Patient;

struct Patient{
	Patient *prev;
	Patient *next;
	char name[MAX_STR+1];
	char surname[MAX_STR+1];
};

void addPatient();
Patient* findPatient(Patient*, char*, char*, _Bool);
void delPatient();
void moveEl();
void mergeSortWizard();
Patient* mergeSort();
Patient* merge();
void printPatients();
void populateDB();
void freeDB();

#endif
