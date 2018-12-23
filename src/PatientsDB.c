#include "../include/PatientsDB.h"

const char K_NAME[] = "Name";
const char K_SURNAME[] = "Surname";
const char K_PESEL[] = "PESEL";
const char K_SEX[] = "Sex";
const char K_STATE[] = "State";
const char K_VISITS[] = "Visits";

void addPatientWizard(Patient **head, Patient **tail){
	_Bool error = 0;
	char name[MAX_STR+1];
	char surname[MAX_STR+1];
	int sex;
	int state = 0;
	int visits = 0;
	printf("\nFill out the form to add a new patient...\n");
	if(!getStringForm(name, K_NAME) || !getStringForm(surname, K_SURNAME)){
		error = 1;
	}
	if(!error){
		printf(">> Sex: 0 - Male / 1 - Female\n");
		sex = getIntForm(K_SEX);
		if(sex != 0 && sex != 1){
			error = 1;
		}
	}
	if(error){
		printf("Wrong input!\n\n");
		return;
	}
	addPatient(head, tail, name, surname, sex, state, visits);
	printf("-- Added %s %s!\n\n", name, surname);
}

void addPatient(Patient **head, Patient **tail, char name[], char surname[],
	int sex, int state, int visits){
	Patient *patient = malloc(sizeof(Patient));
	if(patient == NULL){
		exit(EXIT_FAILURE);
	}
	patient->prev = *tail;
	patient->next = NULL;
	upFirstLowRest(name);
	strcpy(patient->name, name);
	upFirstLowRest(surname);
	strcpy(patient->surname, surname);
	patient->sex = sex;
	patient->state = state;
	patient->visits = visits;
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
				_Bool back = 0;
				while(!back){
					printPatientInfo(head);
					back = findPatientMenu(head);
				}
			}
			return head;
		}
		head = head->next;
	}
	printf("Couldn't find %s %s!\n\n", name, surname);
	return NULL;
}

void printPatientInfo(Patient *head){
	printf("\n");
	printf("| %s %s\n", head->name, head->surname);
	switch(head->sex){
		case MALE:
			printf("| male\n");
			break;
		case FEMALE:
			printf("| female\n");
			break;
		default:
			printf("| unspecified\n");
	}
	switch(head->state){
		case REGISTERED:
			printf("| REGISTERED\n");
			break;
		case APPOINTMENT:
			printf("| APPOINTMENT\n");
			break;
		case HOSPITAL:
			printf("| HOSPITAL\n");
			break;
		default:
			printf("| unknown\n");
	}
	printf("| %d visits\n\n", head->visits);
}

int findPatientMenu(Patient *head){
	printf("0 - Back\n");
	if(head->state == REGISTERED){
		printf("1 - Make an appointment\n");
		printf("2 - Move to hospital\n");
		printf("3 - Delete patient\n\n");
	}
	else if(head->state == APPOINTMENT){
		printf("1 - End an appointment\n");
		printf("2 - Cancel an appointment\n");
		printf("3 - Move to hospital (and cancel an appointment)\n");
	}
	else if(head->state == HOSPITAL){
		printf("1 - Remove from hospital\n");
	} else{
		printf("1 - Register patient\n");
		printf("2 - Delete patient\n");
	}
	_Bool back = 0;
	char backMsg[] = "\n<-\n<-\n\n";
	if(head->state == REGISTERED){
		switch(getInt()){
			case 0:
				printf("%s", backMsg);
				back = 1;
				break;
			case 1:
				head->state = APPOINTMENT;
				break;
			case 2:
				head->state = HOSPITAL;
				break;
			//case 3:
			default:
				printf("Not available!\n\n");
		}
	}
	else if(head->state == APPOINTMENT){
		switch(getInt()){
			case 0:
				printf("%s", backMsg);
				back = 1;
				break;
			case 1:
				head->state = REGISTERED;
				++(head->visits);
				break;
			case 2:
				head->state = REGISTERED;
				break;
			case 3:
				head->state = HOSPITAL;
				break;
			default:
				printf("Not available!\n\n");
		}
	}
	else if(head->state == HOSPITAL){
		switch(getInt()){
			case 0:
				printf("%s", backMsg);
				back = 1;
				break;
			case 1:
				head->state = REGISTERED;
				break;
			default:
				printf("Not available!\n\n");
		}
	} else{
		switch(getInt()){
			case 0:
				printf("%s", backMsg);
				back = 1;
				break;
			case 1:
				head->state = REGISTERED;
				break;
			//case 2:
			default:
				printf("Not available!\n\n");
		}
	}
	return back;
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
	int spacing = STATE_MAX_LEN+1;
	while(head != NULL){
		if(info){
			switch(head->state){
				case REGISTERED:
					printf("\n%*s  ", spacing, "REGISTERED");
					break;
				case APPOINTMENT:
					printf("\n%*s  ", spacing, "APPOINTMENT");
					break;
				case HOSPITAL:
					printf("\n%*s  ", spacing, "HOSPITAL");
					break;
				default:
					printf("\n%*s  ", spacing, "unknown");
			}
			printf("%s %s", head->name, head->surname);
		}
		++count;
		head = head->next;
	}
	if(info && count == 0){
		printf("Database is empty!\n\n");
	}
	else if(info){
		printf("\n\n%*s  %d records\n\n", spacing, "Total:", count);
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
		int sex = intGen(0, 1);
		int state = intGen(0, 2);
		int visits = intGen(0, 8);
		addPatient(head, tail, name, surname, sex, state, visits);
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
