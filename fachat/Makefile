dd:dd.o chat_socket.o
	gcc -pthread -Wall -g -ggdb -O2 -o dd dd.o chat_socket.o

dd.o:dd.c
	gcc -Wall -g -ggdb -O2 -c -o dd.o dd.c

chat_socket.o:chat_socket.c
	gcc -Wall -g -ggdb -O2 -c -o chat_socket.o chat_socket.c

clean:
	rm -f *.o
	rm -f dd
	rm -f core*
