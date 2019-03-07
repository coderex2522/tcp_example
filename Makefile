.PHONY:clean

CC :=gcc
CFLAGS := -Wall -g 

APPS := client server

all:${APPS}
	
client:client.o
	gcc -Wall -g $^ -o $@

server:server.o
	gcc -Wall -g $^ -o $@ 
	
clean:
	rm -rf *.o client server