#include "../include/IOHandler.h"

void getPath(char path[], _Bool bin){
	_Bool clutter = 0;
	printf("\nSpecify path to a file (64-char limit)...\n");
	if(!bin){
		printf("<Press 'Enter' for ./database.txt>\n");
	} else{
		printf("<Press 'Enter' for ./databaseBin.txt>\n");
	}
	fgets(path, MAX_STR+2, stdin);
	path[strlen(path)-1] = '\0';
	if(strlen(path) == MAX_STR){
		clutter = clearBuffer();
	}
	if(clutter || !strcmp(path, "")){
		printf("Following a default path...\n");
		if(!bin){
			strcpy(path, "database.txt");
		} else{
			strcpy(path, "databaseBin.txt");
		}
	}
}

void saveFile(Patient *head){
	char path[MAX_STR+2];
	getPath(path, 0);
	FILE *file = fopen(path, "w");
	if(file == NULL){
		printf("Couldn't create a file!\n\n");
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
	printf("Database exported successfully!\n\n");
}

void readFile(Patient **head, Patient **tail){
	char path[MAX_STR+2];
	getPath(path, 0);
	FILE *file = fopen(path, "r");
	if(file == NULL){
		printf("Couldn't open a file!\n\n");
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
	printf("Database imported successfully!\n\n");
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
	if(fgets(fstr, MAX_FGETS, file) && !strncmp(str, fstr+1, strlen(str))){
		char *beg = fstr+strlen(str)+4;
		char *end = strrchr(fstr, '"');
		ptrdiff_t len = end-beg;
		if(len > 0 && len <= MAX_STR){
			strncpy(des, beg, len);
			des[len] = '\0';
			return 1;
		}
	}
	return 0;
}

void saveFileBin(Patient *head){
	char path[MAX_STR+2];
	getPath(path, 1);
	FILE *file = fopen(path, "wb");
	if(file == NULL){
		printf("Couldn't create a file!\n\n");
		return;
	}
	while(head != NULL){
		fwrite(head, sizeof(Patient), 1, file);
		head = head->next;
	}
	fclose(file);
	printf("Database exported successfully!\n\n");
}

void readFileBin(Patient **head, Patient **tail){
	char path[MAX_STR+2];
	getPath(path, 1);
	FILE *file = fopen(path, "rb");
	if(file == NULL){
		printf("Couldn't open a file!\n\n");
		return;
	}
	fseek(file, 0, SEEK_END);
	long records = ftell(file) / sizeof(Patient);
	rewind(file);
	for(int i = 0; i < records; ++i){
		Patient *patient = malloc(sizeof(Patient));
		if(patient == NULL){
			exit(EXIT_FAILURE);
		}
		if(!fread(patient, sizeof(Patient), 1, file)){
			printf("> Corrupted file!\n");
			printf("> At least one record couldn't be loaded!\n\n");
			break;
		}
		addPatient(head, tail, patient->name, patient->surname);
		free(patient);
	}
	fclose(file);
	printf("Database imported successfully!\n\n");
}
