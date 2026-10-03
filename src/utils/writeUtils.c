#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "writeUtils.h"

char currentChar[1];

void copyRecord(int inputFd,int destinationFd) {
	do {
		read(inputFd,currentChar,1);
		write(destinationFd,currentChar,1);
	} while(currentChar[0]!='\n');
}

void insertUsers(char* username, char* password, char* priviledges) {
	int usersFd = open("../users.txt", O_WRONLY);
	char* userPriviledge = "0\n";
	char* separator = " | ";
	
	lseek(usersFd,0,SEEK_END);
	write(usersFd,username,strlen(username));
	write(usersFd,separator,strlen(separator));
	write(usersFd,password,strlen(password));
	write(usersFd,separator,strlen(separator));
	write(usersFd,userPriviledge,strlen(userPriviledge));
	close(usersFd);
}
