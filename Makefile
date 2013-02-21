CC=gcc -pthread
CC_FLAGS=-g -O2 -c -Wall
OBJECTS=factory.o

all:$(OBJECTS)
	$(CC) factory.o -o factory

$(OBJECTS):%.o:%.c
	$(CC) $(CC_FLAGS) $< -o $@

clean:
	rm *.o
	rm -rf factory
