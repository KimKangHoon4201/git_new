#for criminal
CC = gcc
TARGETS = main
OBJECTS = main.c criminal.o
.SUFFIXES = .c .o
main_debug : $(TARGETS)
main_debug : DEBUGOPTION = -DDEBUG

$(TARGETS) : $(OBJECTS)
	$(CC) $(DEBUGOPTION) -o $@ $^

.c.o :
	$(CC) $(DEBUGOPTION) -c $<

clean:
	rm *.o $(TARGETS)
