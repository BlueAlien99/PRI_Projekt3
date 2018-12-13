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
	*tail = patient;
	if(*head == NULL){
		*head = patient;
	}
}

void printPatients(){

}

void populateDB(){

}
