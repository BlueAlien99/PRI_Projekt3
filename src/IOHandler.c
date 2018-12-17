#include "../include/IOHandler.h"

void saveFile(Patient *head){
	FILE *file = fopen("xd.txt", "w");
	if(file == NULL){
		printf("\nCouldn't create a file!\n\n");
		return;
	}
	while(head != NULL){
		fprintf(file, "{\n");
		fprintf(file, "\"%s\":\"%s\";\n", K_NAME, head->name);
		fprintf(file, "\"%s\":\"%s\";\n", K_SURNAME, head->surname);
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
	while(!feof(file)){
		if(readChar(file, '{') && readString(file, K_NAME, name) &&
			readString(file, K_SURNAME, surname) && readChar(file, '}')){
			addPatient(head, tail, name, surname);
		}
	}
	fclose(file);
}

_Bool readChar(FILE *file, char c){
	char fstr[MAX_FGETS];
	if(fgets(fstr, MAX_FGETS, file) && fstr[0] == c){
		return 1;
	}
	return 0;
}

_Bool readString(FILE *file, const char str[], char des[]){
	char fstr[MAX_FGETS];
	if(fgets(fstr, MAX_FGETS, file) && !strncmp(str, fstr+1, strlen(str)-1)){
		char *beg = fstr+strlen(str)+4;
		char *end = strrchr(fstr, '"');
		ptrdiff_t len = end-beg;
		if(len > 0){
			strncpy(des, beg, len);
			des[len] = '\0';
			return 1;
		}
	}
	return 0;
}
