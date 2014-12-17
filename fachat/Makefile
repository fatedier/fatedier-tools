fachat:fachat.o chat_socket.o
	gcc -pthread -Wall -g -ggdb -O2 -o fachat fachat.o chat_socket.o

fachat.o:fachat.c
	gcc -Wall -g -ggdb -O2 -c -o fachat.o fachat.c

chat_socket.o:chat_socket.c
	gcc -Wall -g -ggdb -O2 -c -o chat_socket.o chat_socket.c

clean:
	rm -f *.o
	rm -f fachat
	rm -f core*
