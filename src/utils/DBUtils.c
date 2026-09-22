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

//funzioni che creano file da usare come viste
int createUserView(char* username){
	char filePath [20];
	char buffer[1]; // buffer per poter usare read()
	sprintf(filePath,"%sReservations.txt",username);
	int myReservationsFd=open(filePath, O_CREAT|O_RDWR, 0660);
	int reservationsFd=open("../reservations.txt", O_RDWR);
	while (read(reservationsFd,buffer,1)!=0) {
		skipToField(reservationsFd,1); // spostamento su campo username
		printf("spostamento campo username\n");
		if (confrontFromFile(reservationsFd,username)==TRUE) {
			printf("fatto confronto\n");
			backToStartField(reservationsFd); /*TODO: si blocca qui*/
			printf("spostamento inizio\n");
			copyRecord(reservationsFd,myReservationsFd);
			printf("fatto copyrecord\n");
		}
	}
	close(reservationsFd);
	close(myReservationsFd);
	return myReservationsFd;
}
	
int createTempView(){
	int tempFileFd=open("/temp.txt", O_CREAT|O_RDWR, 0660);
	return tempFileFd;
}

//funzioni che simulano una query sul file 
char* users_selectAll_byUserame(char* username,int offset) {
	char record [100];
	int usersFd=open("../users.txt", O_RDONLY);
	if (usersFd<0) {
		perror("Error while opening users.txt");
		exit(-1);
	}
	
	
	
	return 0;
}
