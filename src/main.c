#if __STDC_VERSION__ < 199901L
#error C99 compiler required!
#endif

#include <time.h>

#include "../include/IOHandler.h"
#include "../include/PatientsDB.h"

void help();
void menu();

int main(void){
	srand(time(NULL));
	Patient *head = NULL;
	Patient *tail = NULL;
	printf("\nWelcome to medical clinic!\n");
	help();
	menu(&head, &tail);
	freeDB(&head, &tail);
	return 0;
}

void help(){
	printf("\nAvailable actions:");
	printf("\n0  - Exit");
	printf("\n1  - Find patient");
	printf("\n2  - Print all names");
	printf("\n3  - Sort database");
	printf("\n4  - Add new patient");
	printf("\n5  - Delete existing patient");
	printf("\n7  - Populate database with random data");
	printf("\n8  - Import from file");
	printf("\n81 - Import from file (binary)");
	printf("\n9  - Export to file");
	printf("\n91 - Export to file (binary)");
	printf("\n\n");
}

void menu(Patient **head, Patient **tail){
	_Bool end = 0;
	do{
		switch(getInt()){
			case 0:
				end = 1;
				break;
			case 1:
				findPatient(*head, 1);
				break;
			case 2:
				printPatients(*head);
				break;
			case 3:
				mergeSortWizard(head, tail);
				break;
			case 4:
				addPatientWizard(head, tail);
				break;
			case 5:
				delPatient(head, tail);
				break;
			case 7:
				populateDB(head, tail);
				break;
			case 8:
				readFile(head, tail);
				break;
			//case 81:
				break;
			case 9:
				saveFile(*head);
				break;
			//case 91:
				break;
			case 123:
				help();
				break;
			default:
				printf("Unrecognized parameter! Type '123' to get help...\n\n");
		}
	} while(!end);
}
