CC=gcc
INCDIR=-I../dyad-master/include
LIBDIR=-L../dyad-master/lib
CFLAGS=-Wall -g
LDFLAGS=-ldyad -lpthread

all: server client

server: server.c
	$(CC) server.c -o server $(INCDIR) $(LIBDIR) $(LDFLAGS) $(CFLAGS)

client: client.c
	$(CC) client.c -o client $(INCDIR) $(LIBDIR) $(LDFLAGS) $(CFLAGS)

.PHONY: clean

clean:
	rm client server
