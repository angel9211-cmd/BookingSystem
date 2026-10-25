#include <"stdio.h">
#include <"fcntl.h">

//ha senso verificare che non si scontrino in scrittura?
int lock = 1;

//TODO: controllare la struct già fatta di C per le date
// verificare se ha senso chiedere le info lato client o fare richiesta
// qui e controllo là, si può allora fare anche controllo credenziali


typedef struct date {
		int day;
		int month;
		int year;
	} Date;
	
typedef struct time {
		int hours;
		int minutes;
	} Time;

void createReservation(char* username) {
	char id [5];
	char resource [20];
	Date reservationDate;
	Time startingTime;
	Time endTime;
	char reservationState;
	
	// 1. chiedere tutte le info necessarie
	// a. controllo degli input
	// b. creare view sulla risorsa e controllare orari
	// 2. verificare nessun altro stia scrivendo
	// 3. scrittura effettiva
	char* message "Choose a resource to reserve from the list below:\n";
	
	// 1
	
	while(lock<1) {
	char* message;
	}
	lock--;
	int reservationsFd = open("reservations.txt",O_WRONLY);
	// scrittura
	close(reservationsFd);
	lock++;
}
