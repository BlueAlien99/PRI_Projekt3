#if __STDC_VERSION__ < 199901L
#error C99 compiler required!
#endif

#include "../include/PatientsDB.h"

int main(void){
	Patient *head = NULL;
	Patient *tail = NULL;

	//
		addPatient(&head, &tail, "John", "Kowalski");
		addPatient(&head, &tail, "Anne", "Greenhill");
		addPatient(&head, &tail, "Steven", "Stephanson");

		printPatients(head);
	//
}
