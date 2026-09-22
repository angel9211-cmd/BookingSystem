#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "login.h"
#include "readUtils.h"
#include "createUser.h"
#include "DBUtils.h"

char* message;
char option [2] = "0";
int procedureResult [1];

//TODO gestire la creazione di nuovi amministratori

void supplier_login
(int clientFd,char* username,char* password,char* priviledges) {
	message = "Logging in...\n";
	write(clientFd,message,strlen(message)+1);
	do {
		procedureResult[0] =
			login(clientFd,username,password,priviledges);
		// manda risultato a client
		write(clientFd,procedureResult,sizeof(procedureResult));
		} while (procedureResult[0]!= USER_FOUND &&
				 procedureResult[0]!= USER_IS_AMMINISTRATOR);
}

void supplier_createUser
(int clientFd,char* username,char* password,char* priviledges) {
	message =
	"To create a new user you have to choose\n"
	"A unique username and a password\n"
	"To choose your credentials, please follow these rules:\n"
	"1)Username and password have to be shorter than 20 characters\n"
	"2)Spaces are not allowed\n";
	write(clientFd,message,strlen(message)+1);
	do {
		procedureResult[0] =
			createUser(clientFd,username,password,priviledges);
		// manda risultato a client
		write(clientFd,procedureResult,sizeof(procedureResult));
	} while (procedureResult[0]!= USER_CREATED);
}

void supplier_startSession
(int clientFd,char* username,char* password,char* priviledges) {
	message = "Welcome!\n";
	write(clientFd,message,strlen(message)+1);
	message = "Choose an option by typing its number\n";
	write(clientFd,message,strlen(message)+1);
	message = "1)log in\n2)create a new user\n";
	
	do {
		write(clientFd,message,strlen(message)+1);
		readIntoString(clientFd,option);
		switch (option[0])	{
			case '1': 
				supplier_login(clientFd,username,password,priviledges);
				break;
			case '2': 
				supplier_createUser(clientFd,username,password,priviledges);
				break;
			default:
				option[0]='0';
				message = "Please choose a valid option\n";
				write(clientFd,message,strlen(message)+1);
			}
	} while(option[0]=='0');
}


int supplier_userMainCicle(int clientFd,char* username) {
	printf("sto per creare view\n");
	int myReservationsFd = createUserView(username);
	do {
		message = "Choose next action to execute:\n";
		write(clientFd,message,strlen(message)+1);
		message =
		 "1)check all your reservations\n2)search for a reservation\n"
		 "3)create a new reservation\n0)end session\n";
		write(clientFd,message,strlen(message)+1);
		readIntoString(clientFd,option);
		switch (option[0])	{
			case '0':
				char filePath [20];
				sprintf(filePath,"%sReservations.txt",username);
				unlink(filePath);
				return 0;
			case '1': 
				printf("option 1\n");
				break;
			case '2': 
				printf("option 2\n");
				break;
			case '3':
				printf("option3\n");
				break;
			default:
				message = "Please choose a valid option\n";
				write(clientFd,message,strlen(message)+1);
			}
	} while(1==1);
	return 0;
}
