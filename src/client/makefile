all:
	cc -c client.c
	cc -c communicationHandler.c
	cc *.o -o client
	
clean:
	rm -f core *.o client
	
install:
	cp client ../../exec
