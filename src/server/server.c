#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include "readUtils.h"
#include "serviceSupplier.h"
#include "DBUtils.h"

int main (void) {
	/*sezione codice per creazione socket*/
	unsigned int serverFd, clientFd, serverLenght, clientLenght;
	unsigned short int port = 1300;
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	struct sockaddr* serverSockAddrPtr;
	struct sockaddr* clientSockAddrPtr;
	
	signal(SIGCHLD, SIG_IGN);
	serverSockAddrPtr = (struct sockaddr*) &serverAddress;
	clientSockAddrPtr = (struct sockaddr*) &clientAddress;
	serverLenght = sizeof(serverAddress);
	clientLenght = sizeof(clientAddress);

	/*creazione effettiva del socket*/
	serverFd = socket(AF_INET,SOCK_STREAM,0);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	if(bind(serverFd,serverSockAddrPtr,serverLenght)<0){
		perror("error while binding");
		exit(-1);
	}
	listen(serverFd,5);

	/****/
	

	/*server si mette in attesa di connessioni*/
	while(1) {
	printf("Server: waiting for connections...\n");
	clientFd=accept(serverFd,clientSockAddrPtr,&clientLenght);
	printf("Server: connection established\n");	
	if (fork() == 0) {
		char username[20];
		char password [20];
		char priviledges [2];
		/*gestione richiesta client tramite processo figlio*/
		supplier_startSession(clientFd,username,password,priviledges);
		write(clientFd,priviledges,strlen(priviledges)+1);
		if (priviledges[0]=='0') {
			int myReservationsFd = createUserView();
			supplier_userMainCicle(clientFd,myReservationsFd);
			unlink("/myReservations.txt");
			}
		//ammMainCicle
		close(clientFd);
		exit(0); 
	} else 
		close(clientFd);
	}
	return 0;
}
