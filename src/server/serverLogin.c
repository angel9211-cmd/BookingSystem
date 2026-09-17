#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "serverLogin.h"
#include "readUtils.h"

//TODO: 
//		creare i file header per login e register
// 		file separato per register
//		creare un login per client che fa le read e write

char currentCharFile[1];

void changeLine(int fd, int k) {	
	for (int i=0;i<k;i++) {
		while(currentCharFile[0]!='\n') {
			read(fd,currentCharFile,1);
		}
	}
}

int verify(int fd, char* contentFromInput){
	int i=0;
	
	do {
		if(read(fd,currentCharFile,1)==0) return -1;
		
		if (currentCharFile[0]!=contentFromInput[i]) {
			if(currentCharFile[0]==' ') return -1;
			changeLine(fd,1);
			i=-1;
			}
		i++;
	} while (contentFromInput[i]!='\0');
	
	return 0;
}

int login(int clientFd) {
	int usersFd=open("../users.txt", O_RDONLY);
	if (usersFd<0) {
		perror("Error while opening users.txt");
		exit(-1);
	}
	
	char username [USER_INPUT_MAXLEN];
	char password [USER_INPUT_MAXLEN];
	
	char* output = "Username: \n";
	write(clientFd,output,strlen(output)+1);
	readFromString(clientFd,username);
	
	output = "Password: \n";
	write(clientFd,output,strlen(output)+1);
	readFromString(clientFd,password);

	if(verify(usersFd,username)!=0) {
		printf("User not found, try again\n");
		close(usersFd);
		return ERR_USER_NOT_FOUND;
	}
	lseek(usersFd,3,SEEK_CUR);
	if(verify(usersFd,password)!=0){
		printf("Wrong password, try again");
		close(usersFd);
		return ERR_WRONG_PASSWORD;
	}
	lseek(usersFd,3,SEEK_CUR);
	char amministrator [2] = "1";
	if(verify(usersFd,amministrator)!=0){
		return USER_FOUND;
		close(usersFd);
	}
	close(usersFd);
	printf("utente amministratore!\n");
	return USER_IS_AMMINISTRATOR;
}

/*int createUser(char *userName, char *userPassword) {
	
	int fd=open("./users.txt", O_WRONLY);
	if (fd<0) {
		perror("Error while opening users.txt");
		exit(-1);
	}
	
	if(verify(fd,userName)==0) return USER_FOUND;
	lseek(fd,0,SEEK_END);
	return 0;
}
*/
