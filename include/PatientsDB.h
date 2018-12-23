#ifndef PATIENTSDB_H
#define PATIENTSDB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utilities.h"

#define STATE_MAX_LEN 11

extern const char K_NAME[];
extern const char K_SURNAME[];
extern const char K_PESEL[];
extern const char K_SEX[];
extern const char K_STATE[];
extern const char K_VISITS[];
extern const int E_SEX;
extern const int E_STATE;

typedef struct Patient Patient;

enum Sex {MALE, FEMALE};
enum State {REGISTERED, APPOINTMENT, HOSPITAL};

struct Patient{
	Patient *prev;
	Patient *next;
	char name[MAX_STR+1];
	char surname[MAX_STR+1];
	char PESEL[PESEL_LEN+1];
	enum Sex sex;
	enum State state;
	uint visits;
};

void addPatientWizard();
void addPatient();
Patient* findPatient(Patient*, _Bool);
void printPatientInfo(Patient*);
int findPatientMenu(Patient*);
void delPatient();
void moveEl();
void mergeSortWizard();
Patient* mergeSort();
Patient* merge();
int printPatients(Patient*, _Bool);
void getStats();
void populateDB();
void freeDB();

#endif
