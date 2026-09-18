#include <stdio.h>
#include <unistd.h>
#include "writeUtils.h"

char currentCharFile[1];

void copyRecord(int inputFd,int destinationFd) {
	do {
		read(inputFd,currentCharFile,1);
		write(destinationFd,currentCharFile,1);
	} while(currentCharFile[1]!='\n');
}
