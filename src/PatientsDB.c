#include "../include/PatientsDB.h"

void addPatient(Patient **head, Patient **tail, char name[], char surname[]){
	Patient *patient = malloc(sizeof(Patient));
	if(patient == NULL){
		exit(EXIT_FAILURE);
	}
	patient->prev = *tail;
	patient->next = NULL;
	strcpy(patient->name, name);
	strcpy(patient->surname, surname);
	if(*tail != NULL){
		(*tail)->next = patient;
	}
	*tail = patient;
	if(*head == NULL){
		*head = patient;
	}
}

void printPatients(Patient *head){
	int count = 0;
	while(head != NULL){
		printf("\n%s %s", head->name, head->surname);
		++count;
		head = head->next;
	}
	printf("\n^^^^^");
	printf("\nTotal: %d records\n\n", count);
}

void populateDB(){

}
