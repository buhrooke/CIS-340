CC=gcc
CFLAGS=-g
DEPS = getsuper.h help.h showsuper.h traverse.h
OBJ = getsuper.o help.o main.o showsuper.o traverse.o showzone.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

minix: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)