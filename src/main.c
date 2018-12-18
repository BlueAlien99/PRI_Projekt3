#if __STDC_VERSION__ < 199901L
#error C99 compiler required!
#endif

#include <time.h>

#include "../include/IOHandler.h"
#include "../include/PatientsDB.h"

int main(void){
	srand(time(NULL));
	Patient *head = NULL;
	Patient *tail = NULL;











	//
		populateDB(&head, &tail, 5);
		//delPatient(&head, &tail, "Anne", "Greenhill");
		//addPatient(&head, &tail, "Steven", "Stephanson");
		readFile(&head, &tail, 0);
		mergeSortWizard(&head, &tail);
		printPatients(head);
		//saveFile(head, 0);

		freeDB(&head, &tail);
	//
}
