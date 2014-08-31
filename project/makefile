main.o:client.o server.o
client.o:client.c myinclude.h
	gcc client.c -o client -lpthread
server.o:server.c myinclude.h
	gcc server.c -o server -lpthread
clean:
	rm server  client 
