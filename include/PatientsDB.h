#ifndef PATIENTSDB_H
#define PATIENTSDB_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utilities.h"

#define STATE_MAX_LEN 11
#define E_SEX 3
#define E_STATE 4
#define NOFSTATS E_STATE+4

extern const char K_NAME[];
extern const char K_SURNAME[];
extern const char K_PESEL[];
extern const char K_SEX[];
extern const char K_STATE[];
extern const char K_VISITS[];

typedef struct Patient Patient;

enum Sex {MALE, FEMALE};
enum State {REGISTERED, APPOINTMENT, HOSPITAL};

struct Patient{
	Patient *prev;
	Patient *next;
	char name[MAX_STR+1];
	char surname[MAX_STR+1];
	char PESEL[MAX_STR+1];
	enum Sex sex;
	enum State state;
	uint visits;
};

void addPatientWizard(Patient **head, Patient **tail);
void addPatient(Patient **head, Patient **tail, char name[], char surname[],
	char pesel[], int sex, int state, int visits);
Patient* findPatient(Patient **m_head, Patient **m_tail, _Bool info);
void printPatientInfo(Patient *head);
int findPatientMenu(Patient **m_head, Patient **m_tail, Patient *head);
void delPatient(Patient **head, Patient **tail, Patient *el);
void moveEl(Patient **src, Patient **target, Patient **targetTail);
void mergeSortWizard(Patient **head, Patient **tail);
Patient* mergeSort(Patient *head);
Patient* merge(Patient *left, Patient *right);
int printPatients(Patient *head, _Bool info);
void getStats(Patient *head);
void printStats(uint stats[][NOFSTATS], double avgvisit[]);
void printStatsLine(char header[], uint stats[][NOFSTATS], int i);
void populateDB(Patient **head, Patient **tail);
void freeDB(Patient **head, Patient **tail);

#endif
