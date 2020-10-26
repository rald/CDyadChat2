all: server client

server: server.c
	gcc server.c -o server -ldyad -lpthread

client: client.c
	gcc client.c -o client -ldyad -lpthread

.PHONY: clean

clean:
	rm client server
