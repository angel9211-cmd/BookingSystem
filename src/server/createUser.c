#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "readUtils.h"
#include "writeUtils.h"
#include "createUser.h"

//TODO controllare lunghezza user e password lato client

int createUser
(int clientFd,char* username, char* password,char* priviledges) {
	int usersFd=open("../users.txt", O_RDWR | O_CREAT, 0660);
	if (usersFd<0) {
		perror("Error while opening users.txt");
		exit(-1);
	}
		
	char* message = "Type your username:\n";
	write(clientFd,message,strlen(message)+1);
	readIntoString(clientFd,username);
	
	message = "Type your password:\n";
	write(clientFd,message,strlen(message)+1);
	readIntoString(clientFd,password);
	
	if(searchSpaces(username)==FALSE) {
		message = "Username contains spaces, please try again\n";
		write(clientFd,message,strlen(message)+1);
		close(usersFd);
		return USER_NOT_CREATED;
	}
	if(verifyUserExists(usersFd,username)==TRUE) {
		message = "Username already exists, please try again:\n";
		write(clientFd,message,strlen(message)+1);
		close(usersFd);
		return USER_NOT_CREATED;
	}
	if(searchSpaces(password)==FALSE) {
		message = "Password cointains spaces, please try again:\n";
		write(clientFd,message,strlen(message)+1);
		close(usersFd);
		return USER_NOT_CREATED;
	}
	close(usersFd);
	priviledges[0] = '0';
	insertUsers(username,password,priviledges);
	message = "User successfully created\n";
	write(clientFd,message,strlen(message)+1);
	return USER_CREATED;
}
