#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "readUtils.h"
#include "communicationHandler.h"

int main(void) {
	/*sezione codice creazione socket*/
	int clientFd,serverLength;
	unsigned short int port = 1300;
	struct sockaddr_in serverAddress;
	struct sockaddr* serverSockAddrPtr;
	serverSockAddrPtr = (struct sockaddr*) &serverAddress;
	serverLength = sizeof(serverAddress);

	//creazione effettiva del socket
	clientFd = socket(AF_INET,SOCK_STREAM,0);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	/*****/

	//client si connette al server
	int connection;
	do {
		printf("Client: connecting to server...\n");
		connection =
			   	connect(clientFd,serverSockAddrPtr,serverLength);
		if (connection == -1) sleep(1);
		} while (connection == -1);
	char priviledges [2];
	handler_startSession(clientFd);
	readIntoString(clientFd,priviledges);
	//ciclo esecuzione
	if(priviledges[0]=='0') handler_userMainCicle(clientFd);
	// ciclo amm
	printf("Client: closing connection...\n");
	close(clientFd);
	exit(0);
}
