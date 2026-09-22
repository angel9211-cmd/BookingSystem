#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include "readUtils.h"

int login
(int clientFd,char* username, char* password,char* priviledges) {
	int usersFd=open("../users.txt", O_RDONLY);
	if (usersFd<0) {
		perror("Error while opening users.txt");
		exit(-1);
	}
	char* message = "Username: \n";
	write(clientFd,message,strlen(message)+1);
	readIntoString(clientFd,username);
	
	message = "Password: \n";
	write(clientFd,message,strlen(message)+1);
	readIntoString(clientFd,password);

	if(verifyUserExists(usersFd,username)!=TRUE) {
		message="User not found, please try again\n";
		write(clientFd,message,strlen(message)+1);
		close(usersFd);
		return ERR_USER_NOT_FOUND;
	}
	skipToField(usersFd,1);
	if(confrontFromFile(usersFd,password)!=TRUE){
		message="Wrong password, please try again\n";
		write(clientFd,message,strlen(message)+1);
		close(usersFd);
		return ERR_WRONG_PASSWORD;
	}
	skipToField(usersFd,1);
	char amministrator [2] = "1";
	if(confrontFromFile(usersFd,amministrator)!=TRUE){
		message = "Server: successfully logged in\n";
		priviledges[0] = '0';
		write(clientFd,message,strlen(message)+1);
		close(usersFd);
		return USER_FOUND;
	}
	close(usersFd);
	message = "Server: successfully logged in as amministrator\n";
	priviledges[0] = '1';
	write(clientFd,message,strlen(message)+1);
	return USER_IS_AMMINISTRATOR;
}
