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

Patient* findPatient(){

}

void delPatient(){

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
	*tail = *head;
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

void freeDB(Patient **head, Patient **tail){
	while((*head)->next != NULL){
		*head = (*head)->next;
		free((*head)->prev);
	}
	if(*tail != NULL){
		free(*tail);
		*tail = NULL;
		*head = NULL;
	}
}
