
all:
#chiamate ai makefile delle sottocartelle
	@$(MAKE) -C utils
	@$(MAKE) -C server
	@$(MAKE) -C client
	
clean:
	rm -f server/*.o server/core server/server
	rm -f client/*.o client/core client/client
	rm -f utils/*.o utils/core  
	
install:
	cp server/server ../exec
	cp client/client ../exec
