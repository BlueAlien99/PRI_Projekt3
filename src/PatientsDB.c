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

Patient* findPatient(Patient **m_head, Patient **m_tail, _Bool info){
	Patient *head = *m_head;
	char name[MAX_STR+1];
	char surname[MAX_STR+1];
	printf("\nEnter name and surname of a patient...\n");
	if(!getString(name) || !getString(surname)){
		printf("Wrong input!\n\n");
		return NULL;
	}
	upFirstLowRest(name);
	upFirstLowRest(surname);
	while(head != NULL){
		if(strcmp(head->surname, surname) == 0
			&& strcmp(head->name, name) == 0){
			if(info){
				_Bool back = 0;
				while(!back){
					printPatientInfo(head);
					back = findPatientMenu(m_head, m_tail, head);
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

int findPatientMenu(Patient **m_head, Patient **m_tail, Patient *head){
	printf("0 - Back\n");
	if(head->state == REGISTERED){
		printf("1 - Make an appointment\n");
		printf("2 - Move to hospital\n");
		printf("3 - Delete patient\n\n");
	}
	else if(head->state == APPOINTMENT){
		printf("1 - End an appointment\n");
		printf("2 - Cancel an appointment\n");
		printf("3 - Move to hospital (and cancel an appointment)\n\n");
	}
	else if(head->state == HOSPITAL){
		printf("1 - Remove from hospital\n\n");
	} else{
		printf("1 - Register patient\n");
		printf("2 - Delete patient\n\n");
	}
	_Bool back = 0;
	char backMsg[] = "\n<-\n<-\n\n";
	char backDelMsg[] = "<-\n<-\n\n";
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
			case 3:
				delPatient(m_head, m_tail, head);
				printf("%s", backDelMsg);
				back = 1;
				break;
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
			case 2:
				delPatient(m_head, m_tail, head);
				printf("%s", backDelMsg);
				back = 1;
				break;
			default:
				printf("Not available!\n\n");
		}
	}
	return back;
}

void delPatient(Patient **head, Patient **tail, Patient *el){
	Patient *del = NULL;
	if(el == NULL){
		del = findPatient(head, tail, 0);
	} else{
		del = el;
	}
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

void getStats(Patient *head){
	uint stats[E_SEX+1][NOFSTATS];
	for(int i = 0; i < NOFSTATS; ++i){
		for(int j = 0; j < E_SEX+1; ++j){
			stats[j][i] = 0;
			if(i == NOFSTATS-1){
				stats[j][i] = INT_MAX;
			}
		}
	}
	while(head != NULL){
		int col = min(head->sex, E_SEX-1);
		++stats[col][min(head->state, E_STATE-1)];
		stats[col][E_STATE+1] += head->visits;
		stats[col][E_STATE+2] = max(stats[col][E_STATE+2], head->visits);
		stats[col][E_STATE+3] = min(stats[col][E_STATE+3], head->visits);
		head = head->next;
	}
	for(int i = 0; i < E_SEX+1; ++i){
		if(stats[i][NOFSTATS-1] == INT_MAX){
			stats[i][NOFSTATS-1] = 0;
		}
	}
	for(int i = 0; i < E_STATE+2; ++i){
		for(int j = 0; j < E_SEX; ++j){
			stats[E_SEX][i] += stats[j][i];
		}
	}
	for(int i = 0; i < E_SEX+1; ++i){
		for(int j = 0; j < E_STATE; ++j){
			stats[i][E_STATE] += stats[i][j];
		}
	}
	double avgvisit[E_SEX+1];
	for(int i = 0; i < E_SEX+1; ++i){
		if(stats[i][E_STATE] != 0){
			avgvisit[i] = (double)stats[i][E_STATE+1]/stats[i][E_STATE];
		} else{
			avgvisit[i] = 0;
		}
	}
	stats[E_SEX][E_STATE+2] = max(stats[0][E_STATE+2], max(stats[1][E_STATE+2], stats[2][E_STATE+2]));
	stats[E_SEX][E_STATE+3] = min(stats[0][E_STATE+3], min(stats[1][E_STATE+3], stats[2][E_STATE+3]));
	printStats(stats, avgvisit);
}

void printStats(uint stats[][NOFSTATS], double avgvisit[]){
	printf("\n            |   male  |  female | unknown | overall ");
	printStatsLine("       REG", stats, 0);
	printStatsLine("       APP", stats, 1);
	printStatsLine("       HOS", stats, 2);
	printStatsLine("       unk", stats, 3);
	printStatsLine("    >> SUM", stats, E_STATE);
	printf("\n");
	printf("\n Avg visits | %7.2lf | %7.2lf | %7.2lf | %7.2lf",
		avgvisit[0], avgvisit[1], avgvisit[2], avgvisit[3]);
	printStatsLine("Max visits", stats, E_STATE+2);
	printStatsLine("Min visits", stats, E_STATE+3);
	printf("\n\n");
}

void printStatsLine(char header[], uint stats[][NOFSTATS], int i){
	printf("\n %s | %7d | %7d | %7d | %7d", header,
		stats[0][i], stats[1][i], stats[2][i], stats[E_SEX][i]);
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
