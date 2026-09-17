
all:
	cc -c serviceSupplier.c
	cc -c createUser.c
	cc -c login.c
	cc -c server.c
	cc *.o -o server
	
clean:
	rm -f core *.o server
	
install:
	cp server ../../exec
