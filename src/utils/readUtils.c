#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "readUtils.h"

//legge da file e stampa a video
void readAndPrint(int fd, char* input) {
	int end;
	do {
		end = read(fd,input,1);
		printf("%c",input[0]);
	} while (end>0 && (*input++)!='\0');
}

//legge da file e salva su buffer
void readIntoString(int fd, char* input) {
	int end;
	do {
		end = read(fd,input,1);
	} while (end>0 && (*input++)!='\0');
}

//legge da input e salva su buffer
void readFromStdin(char* input) {
	int end;
	do {
		end = read(0,input,1);
	} while (end>0 && (*input++)!='\n');
	input[-1]='\0';
}

//sposta il puntatore di k righe in avanti
void changeLine(int fd, int k) {
	char currentCharFile[1];	
	for (int i=0;i<k;i++) {
		while(currentCharFile[0]!='\n') {
			read(fd,currentCharFile,1);
		}
	}
}

//sposta il puntatore di k campi in avanti
void skipToField(int fd, int k) {
	char currentCharFile[1];
	for (int i=0;i<k;i++) {
		while(currentCharFile[0]!='|') {
			read(fd,currentCharFile,1);
		}
		read(fd,currentCharFile,1);
	}
}

//sposta il puntatore all'inizio del record
void backToStartField(int fd) {
	char currentCharFile[1];
	while(currentCharFile[0]!='\n') {
		lseek(fd,-2,SEEK_CUR);
		read(fd,currentCharFile,1);
	}
}

//ricerca da Users.txt un record col nome utente passato
int verifyUserExists(int usersFd, char* username){
	char currentCharFile[1];
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
	char currentCharFile[1];
	int i=0;
	while (inputString[i]!='\0'){
		read(fd,currentCharFile,1);
		if(currentCharFile[0]!=inputString[i]) return FALSE;
		i++;
	}
	return TRUE;
}

//controlla che all'interno della stringa in input ci siano spazi
int searchSpaces(char* input) {
	int i;
	for(i=0;i<strlen(input)+1;i++) {
		if(input[i]==' ') return FALSE;
	}
	return TRUE;		
}
