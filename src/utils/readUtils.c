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

//confronta ciò che legge dal file con una stringa passata
int verify(int fd, char* contentFromInput){
	char currentCharFile[1];
	int i=0;
	do {
		if(read(fd,currentCharFile,1)==0) return FALSE;
		if (currentCharFile[0]!=contentFromInput[i]) {
			if(currentCharFile[0]==' ') return FALSE;
			changeLine(fd,1);
			i=-1;
			}
		i++;
	} while (contentFromInput[i]!='\0');
	
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
