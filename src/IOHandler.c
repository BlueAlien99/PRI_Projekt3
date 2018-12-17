#include "../include/IOHandler.h"

void saveFile(Patient *head){
	FILE *file = fopen("xd.txt", "w");
	if(file == NULL){
		printf("\nCouldn't create a file!\n\n");
		return;
	}
	while(head != NULL){
		fprintf(file, "{\n");
		fprintf(file, "\"%s\":\"%s\"\n", K_NAME, head->name);
		fprintf(file, "\"%s\":\"%s\"\n", K_SURNAME, head->surname);
		fprintf(file, "}\n");
		head = head->next;
	}
	fclose(file);
}

void readFile(Patient **head, Patient **tail){
	FILE *file = fopen("xd.txt", "r");
	if(file == NULL){
		printf("\nCouldn't open a file!\n\n");
		return;
	}
	char name[MAX_STR+1];
	char surname[MAX_STR+1];
	
	fclose(file);
}
