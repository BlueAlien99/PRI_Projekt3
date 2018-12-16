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

void sortPatients(){

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

void populateDB(Patient **head, Patient **tail, int records){
	for(int i = 0; i < records; ++i){
		char *name = strGen(3, 8);
		char *surname = strGen(4, 10);
		addPatient(head, tail, name, surname);
		free(name);
		free(surname);
	}
	printf("\nGenerated %d records!\n\n", records);
}

char* strGen(int min, int max){
	int l = min + rand() % (max-min+1);
	char *str = malloc(l+1);
	if(str == NULL){
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < l; ++i){
		int c = 'a' + rand() % ('z'-'a'+1);
		str[i] = c;
	}
	str[0] = toupper(str[0]);
	str[l] = '\0';
	return str;
}
