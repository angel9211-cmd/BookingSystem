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
	printf("sto per fare sprintf\n");
	sprintf(filePath,"/%sReservations.txt",username);
	printf("il filepath è %s\n",filePath);
	int myReservationsFd=open(filePath, O_CREAT|O_RDWR, 0660);
	printf("creato fileview\n");
	int reservationsFd=open("../reservations.txt", O_RDWR);
	printf("aperto file users\n");
	copyRecord(reservationsFd,myReservationsFd);
	printf("fatto copyrecord\n");
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
