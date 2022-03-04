# makefile sample

TARGET= prj.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= algo.o vector.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
algo.o: algo.c enum.h vector.h
	$(CC) $(CFLAGS) -c algo.c
	
vector.o: vector.c vector.h enum.h
	$(CC) $(CFLAGS) -c vector.c
	
clean:
	rm -f $(TARGET) $(OBJS)

