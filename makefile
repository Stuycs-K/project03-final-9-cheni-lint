
compile client.out server.out: client.o networking.o server.o
	@gcc -o client.out client.o networking.o -w -lm
	@gcc -o server.out server.o networking.o -w -lm

client: client.out
	@./client.out $(ARGS)

server: server.out
	@./server.out $(ARGS)

client.o: client.c networking.h
	@gcc -c client.c -w -lm

server.o: server.c networking.h
	@gcc -c server.c -w -lm

networking.o: networking.c networking.h
	@gcc -c networking.c -w -lm

clean:
	@rm *.o 2> /dev/null || true
	@rm *~ 2> /dev/null || true
	@rm *client 2> /dev/null || true
	@rm *server 2> /dev/null || true

