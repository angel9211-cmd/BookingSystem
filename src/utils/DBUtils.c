#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "readUtils.h"
#include "DBUtils.h"
#include "writeUtils.h"

//idea: le funzioni ritornano un record che corrisponde ma serve
// funzione che scrive quel record e ripete la ricerca da dove ci siamo
// fermati

// crea file da usare come vista su un elemento in input
//TODO: cambiare nome e rendere generale per users e resources
char* createView(char* field, int k){
	//TODO: aggiungere messaggio in caso no reservations
	char* filePath = calloc(20, sizeof(char));
	char buffer[1]; // buffer per poter usare read()
	int end;
	sprintf(filePath,"%sReservations.txt",field);
	int myReservationsFd=open(filePath, O_CREAT|O_RDWR, 0660);
	int reservationsFd=open("../reservations.txt", O_RDONLY);
	while (read(reservationsFd,buffer,1)>0) {
		//CAMBIARE
		skipToField(reservationsFd,k); // spostamento su campo di field
		if (confrontFromFile(reservationsFd,field)==TRUE) {
			backToStartField(reservationsFd);
			copyRecord(reservationsFd,myReservationsFd);
		} else {
			changeLine(reservationsFd,1);
		}
	}
	close(reservationsFd);
	close(myReservationsFd);
	return filePath;
}

void insertRecord () {
	
}
	
	
