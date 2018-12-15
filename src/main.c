#if __STDC_VERSION__ < 199901L
#error C99 compiler required!
#endif

#include "../include/PatientsDB.h"

int main(void){
	srand(time());
	Patient *head = NULL;
	Patient *tail = NULL;

	//
		addPatient(&head, &tail, "John", "Kowalski");
		addPatient(&head, &tail, "Anne", "Greenhill");
		addPatient(&head, &tail, "Steven", "Stephanson");
		populateDB(&head, &tail, 20);

		printPatients(head);
	//
}
