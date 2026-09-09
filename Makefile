CC = gcc
CFLAGS = -Wall -Wextra

scheduler: main.c funcoes.c
	$(CC) $(CFLAGS) -o scheduler main.c funcoes.c

clean:
	rm -f scheduler *.out
