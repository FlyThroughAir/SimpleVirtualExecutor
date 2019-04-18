.PHONY:clean

CC = gcc
CFLAGS = -Wall -g 
OBJ = main.o tools.o zstack.o runtime.o compile.o
main:$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm
#%.o:%.c
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -lm

clean:
	rm -f *.o main
