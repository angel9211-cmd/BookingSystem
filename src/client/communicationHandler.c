#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "readUtils.h"
#include "communicationHandler.h"

char message [100];
char option [2] = "0";
int procedureResult[1];
char username[20];
char password[20];

void handler_login(int clientFd){
	//primo mesaggio server
	readAndPrint(clientFd,message);
	do {
		//riceve richiesta username
		readAndPrint(clientFd,message);
		//scrittura username
		readFromStdin(username);
		write(clientFd,username,strlen(username)+1);
		//riceve richiesta password
		readAndPrint(clientFd,message);
		//scrittura password
		readFromStdin(password);
		write(clientFd,password,strlen(password)+1);
		//riceve messaggio successo/fallimento
		readAndPrint(clientFd,message);
		//riceve risultato creazione utente
		read(clientFd,procedureResult,sizeof(procedureResult));
	} while(procedureResult[0]!= USER_FOUND && 
			procedureResult[0]!=USER_IS_AMMINISTRATOR);
}

void handler_createUser(int clientFd){
		//primo messaggio server
		readAndPrint(clientFd,message);
		do {
		//riceve richiesta username
		readAndPrint(clientFd,message);
		//scrittura username
		readFromStdin(username);
		write(clientFd,username,strlen(username)+1);
		//riceve richiesta password
		readAndPrint(clientFd,message);
		//scrittura password
		readFromStdin(password);
		write(clientFd,password,strlen(password)+1);
		//riceve messaggio successo/fallimento
		readAndPrint(clientFd,message);
		//riceve risultato login
		read(clientFd,procedureResult,sizeof(procedureResult));
	} while (procedureResult[0]!= USER_CREATED);
}

void handler_startSession(int clientFd){
	//messaggio di benvenuto
	readAndPrint(clientFd,message);
	//mostra opzioni
	readAndPrint(clientFd,message);
	//ciclo per scrittura scelta
	do {
	readAndPrint(clientFd,message);
	readFromStdin(option);
	write(clientFd,option,sizeof(option));
	switch (option[0]) {
		case '1':
			handler_login(clientFd);
			break;
		case '2':
			handler_createUser(clientFd);
			break;
		default:
			option[0]='0';
			readAndPrint(clientFd,message);
			break;
		}
	} while	(option[0]=='0');
}

int handler_userMainCicle(int clientFd) {
	// stesso di startSession
	do {
		readAndPrint(clientFd,message);
		readAndPrint(clientFd,message);
		readFromStdin(option);
		write(clientFd,option,sizeof(option));
		switch (option[0]) {
			case '0':
				return 0;
			case '1':
				printf("client: option 1\n");
				break;
			case '2':
				printf("client: option2\n");
				break;
			case '3':
				printf("option3\n");
				break;
			default:
				readAndPrint(clientFd,message);
				break;
		}
	} while	(1==1);
	return 0;
}
