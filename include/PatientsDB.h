#ifndef PATIENTSDB_H
#define PATIENTSDB_H

#include <stdlib.h>
#include <string.h>

#define MAX_STR 64

typedef struct Patient Patient;

struct Patient{
	Patient *prev;
	Patient *next;
	char name[MAX_STR];
	char surname[MAX_STR];
};

void addPatient();
void printPatients();
void populateDB();

#endif