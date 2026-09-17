#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "readUtils.h"
#include "DBUtils.h"

//idea: le funzioni ritornano un record che corrisponde ma serve
// funzione che scrive quel record e ripete la ricerca da dove ci siamo
// fermati

//funzioni che creano file da usare come viste
int createUserView(){
	int myReservationsFd=open("/myReservations.txt", O_CREAT|O_RDWR, 0660);
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
