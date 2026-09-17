#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "readUtils.h"
#include "createUser.h"

//TODO controllare lunghezza user e password lato client

int createUser
(int clientFd,char* username, char* password,char* priviledges) {
	int usersFd=open("../users.txt", O_RDWR | O_CREAT, 0660);
	if (usersFd<0) {
		perror("Error while opening users.txt");
		exit(-1);
	}
	
	char* userPriviledge = "0\n";
	char* separator = " | ";
	
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
	if(verify(usersFd,username)==TRUE) {
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
	
	priviledges[0] = '0';
	
	lseek(usersFd,0,SEEK_END);
	write(usersFd,username,strlen(username));
	write(usersFd,separator,strlen(separator));
	write(usersFd,password,strlen(password));
	write(usersFd,separator,strlen(separator));
	write(usersFd,userPriviledge,strlen(userPriviledge));
	close(usersFd);
	message = "User successfully created\n";
	write(clientFd,message,strlen(message)+1);
	return USER_CREATED;
}
