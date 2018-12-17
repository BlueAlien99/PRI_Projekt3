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

		/*addPatient(&head, &tail, "John", "Kowalski");
		addPatient(&head, &tail, "Anne", "Greenhill");
		addPatient(&head, &tail, "Marry", "Blood");
		addPatient(&head, &tail, "Santa", "Claus");
		//populateDB(&head, &tail, 5);
		//printPatients(head);
		//mergeSortWizard(&head, &tail);
		//delPatient(&head, &tail, "Anne", "Greenhill");
		//printPatients(head);
		//delPatient(&head, &tail, "Santa", "Claus");
		//printPatients(head);
		addPatient(&head, &tail, "Steven", "Stephanson");
		addPatient(&head, &tail, "Johna", "Kowalski");*/
		//printPatients(head);
		//saveFile(head);
		readFile(&head, &tail);

		freeDB(&head, &tail);
	//
}
