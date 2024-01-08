compile client.out server.out: client.o network.o server.o
	@gcc -o client.out client.o network.o -w -lm
	@gcc -o server.out server.o network.o -w -lm

client: client.out
	@./client.out $(ARGS)

server: server.out
	@./server.out $(ARGS)

client.o: client.c network.h
	@gcc -c client.c -w -lm

server.o: server.c network.h
	@gcc -c server.c -w -lm

network.o: network.c network.h
	@gcc -c network.c -w -lm

fileman.o: fileman.c network.h fileman.h
	@gcc -c fileman.c -w -lm

terminal.o: terminal.c network.h terminal.h
	@gcc -c terminal.c -w -lm

# for testing
fileman.out: fileman.o network.o
	@gcc -o fileman.out network.o fileman.o -w -lm

fileman: fileman.out
	@./fileman.out $(ARGS)

# for testing
terminal.out: terminal.o network.o
	@gcc -o terminal.out network.o terminal.o -w -lm

terminal: terminal.out
	@./terminal.out $(ARGS)

clean:
	@rm *.o 2> /dev/null || true
	@rm *~ 2> /dev/null || true
	@rm *client 2> /dev/null || true
	@rm *server 2> /dev/null || true

