#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "readUtils.h"

//TODO: quando legge da reservations non copia anche l'id

char currentCharFile[1];

//legge da file e stampa a video in locale
void readAndPrint(int fd, char* buffer) {
	int end;
	do {
		end = read(fd,buffer,1);
		printf("%c",buffer[0]);
	} while (end>0 && (*buffer++)!='\0');
}


//legge da file e salva su buffer
void readIntoString(int fd, char* buffer) {
	int end;
	do {
		end = read(fd,buffer,1);;
	} while (end!=0 && *buffer++!='\0');
}

char* fileIntoString(int fd) {
	int fileSize;
	char counter[1];
	while(read(fd,counter,1)!=0){
		fileSize++;
	}
	char* fileBuffer = calloc(fileSize+1,sizeof(char));
	lseek(fd,0,SEEK_SET);
	read(fd,fileBuffer,fileSize);
	fileBuffer[fileSize+1] = '\n';
	return fileBuffer;
	
}

//legge da input e salva su buffer
void readFromStdin(char* buffer) {
	int end;
	do {
		end = read(0,buffer,1);
	} while (end>0 && (*buffer++)!='\n');
	buffer[-1]='\0';
}

//sposta il puntatore di k righe in avanti
void changeLine(int fd, int k) {	
	for (int i=0;i<k;i++) {
		while(currentCharFile[0]!='\n') {
			read(fd,currentCharFile,1);
		}
	}
}

//sposta il puntatore di k campi in avanti
void skipToField(int fd, int k) {
	for (int i=0;i<k;i++) {
		while(currentCharFile[0]!='|') {
			read(fd,currentCharFile,1);
		}
		read(fd,currentCharFile,1);
	}
}

//sposta il puntatore all'inizio del record
void backToStartField(int fd) {
	int offset = 1;
	while(currentCharFile[0]!='\n' && offset!=0 ) {
		offset=lseek(fd,-2,SEEK_CUR);
		read(fd,currentCharFile,1);
	}
}

//ricerca da Users.txt un record col nome utente passato
int userExists(int usersFd, char* username){
	int i=0;
	do {
		if(read(usersFd,currentCharFile,1)==0) return FALSE;
		if (currentCharFile[0]!=username[i]) {
			if(currentCharFile[0]==' ') return FALSE;
			changeLine(usersFd,1);
			i=-1;
			}
		i++;
	} while (username[i]!='\0');
	return TRUE;
}

//confronta ciò che legge dal file con una stringa passata
int confrontFromFile(int fd, char* inputString) {
	int i=0;
	while (inputString[i]!='\0'){
		read(fd,currentCharFile,1);
		if(currentCharFile[0]!=inputString[i]) return FALSE;
		i++;
	}
	return TRUE;
}

//controlla che all'interno della stringa in input ci siano spazi
int searchSpaces(char* string) {
	int i;
	for(i=0;i<strlen(string)+1;i++) {
		if(string[i]==' ') return FALSE;
	}
	return TRUE;		
}
