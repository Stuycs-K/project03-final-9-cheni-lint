compile client.out server.out: client.o server.o network.o fileman.o terminal.o
	@gcc -o client.out client.o network.o fileman.o terminal.o -w -lm
	@gcc -o server.out server.o network.o fileman.o terminal.o -w -lm

client: client.out
	@./client.out $(ARGS)

server: server.out
	@./server.out $(ARGS)

client.o: client.c network.h fileman.h terminal.h
	@gcc -c client.c -w -lm

server.o: server.c network.h fileman.h terminal.h
	@gcc -c server.c -w -lm

network.o: network.c network.h
	@gcc -c network.c -w -lm

fileman.o: fileman.c network.h fileman.h
	@gcc -c fileman.c -w -lm

terminal.o: terminal.c network.h terminal.h fileman.h
	@gcc -c terminal.c -w -lm

clean:
	@rm *.o 2> /dev/null || true
	@rm *~ 2> /dev/null || true
	@rm *client 2> /dev/null || true
	@rm *server 2> /dev/null || true
	@rm *.out 2> /dev/null || true
