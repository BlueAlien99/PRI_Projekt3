#include "../include/PatientsDB.h"

const char K_NAME[] = "Name";
const char K_SURNAME[] = "Surname";

void addPatientWizard(Patient **head, Patient **tail){
	char name[MAX_STR+1];
	char surname[MAX_STR+1];
	printf("\nFill out the form to add a new patient...\n");
	if(!getStringForm(name, "Name") || !getStringForm(surname, "Surname")){
		printf("Wrong input!\n\n");
		return;
	}
	addPatient(head, tail, name, surname);
	printf("--Added %s %s!\n\n", name, surname);
}

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

Patient* findPatient(Patient *head, _Bool info){
	char name[MAX_STR+1];
	char surname[MAX_STR+1];
	printf("\nEnter name and surname of a patient...\n");
	if(!getString(name) || !getString(surname)){
		printf("Wrong input!\n\n");
		return NULL;
	}
	while(head != NULL){
		if(strcmp(head->surname, surname) == 0
			&& strcmp(head->name, name) == 0){
			if(info){
				printf("placeholder\n");
				//TODO: print all the info
			}
			return head;
		}
		head = head->next;
	}
	printf("Couldn't find %s %s!\n\n", name, surname);
	return NULL;
}

void delPatient(Patient **head, Patient **tail){
	Patient *del = findPatient(*head, 0);
	if(del == NULL){
		return;
	}
	if(del == *head && del == *tail){
		*head = del->next;
		*tail = del->prev;
	}
	else if(del == *head){
		del->next->prev = del->prev;
		*head = del->next;
	}
	else if(del == *tail){
		del->prev->next = del->next;
		*tail = del->prev;
	} else{
		del->prev->next = del->next;
		del->next->prev = del->prev;
	}
	free(del);
	printf("Deletion successful!\n\n");
}

void moveEl(Patient **src, Patient **target, Patient **targetTail){
	(*src)->prev = *targetTail;
	if(*targetTail == NULL){
		*target = *src;
	} else{
		(*targetTail)->next = *src;
	}
	*targetTail = *src;
	*src = (*src)->next;
	if(*src != NULL){
		(*src)->prev = NULL;
	}
	(*targetTail)->next = NULL;
}

void mergeSortWizard(Patient **head, Patient **tail){
	printf("\nSorting...");
	*head = mergeSort(*head);
	while((*tail)->next != NULL){
		*tail = (*tail)->next;
	}
	printf("\nSorted!\n\n");
}

Patient* mergeSort(Patient *head){
	if(head->next == NULL){
		return head;
	}
	Patient *left = NULL;
	Patient *leftTail = NULL;
	Patient *right = NULL;
	Patient *rightTail = NULL;
	for(int i = 0; head != NULL; ++i){
		if(i%2){
			moveEl(&head, &left, &leftTail);
		} else{
			moveEl(&head, &right, &rightTail);
		}
	}
	left = mergeSort(left);
	right = mergeSort(right);
	return merge(left, right);
}

Patient* merge(Patient *left, Patient *right){
	Patient *list = NULL;
	Patient *listTail = NULL;
	while(left != NULL && right != NULL){
		if(strcmp(left->surname, right->surname) < 0
			|| (strcmp(left->surname, right->surname) == 0
			&& strcmp(left->name, right->name) < 0)){
			moveEl(&left, &list, &listTail);
		} else{
			moveEl(&right, &list, &listTail);
		}
	}
	while(left != NULL){
		moveEl(&left, &list, &listTail);
	}
	while(right != NULL){
		moveEl(&right, &list, &listTail);
	}
	return list;
}

int printPatients(Patient *head, _Bool info){
	int count = 0;
	while(head != NULL){
		if(info){
			printf("\n%s %s", head->name, head->surname);
		}
		++count;
		head = head->next;
	}
	if(info && count == 0){
		printf("Database is empty!\n\n");
	}
	else if(info){
		printf("\n^^^^^");
		printf("\nTotal: %d records\n\n", count);
	}
	return count;
}

void populateDB(Patient **head, Patient **tail){
	printf("\nHow many records would you like to generate?\n");
	int records = getInt();
	if(records < 1 || records > 1000){
		printf("Error! Value should be within [1,1000] range!\n\n");
		return;
	}
	for(int i = 0; i < records; ++i){
		char *name = strGen(3, 8);
		char *surname = strGen(4, 10);
		addPatient(head, tail, name, surname);
		free(name);
		free(surname);
	}
	printf("Generated %d records!\n\n", records);
}

void freeDB(Patient **head, Patient **tail){
	if(*head == NULL){
		return;
	}
	while((*head)->next != NULL){
		*head = (*head)->next;
		free((*head)->prev);
	}
	free(*tail);
	*tail = NULL;
	*head = NULL;
}
