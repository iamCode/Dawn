CC=g++
LIBS=-lpthread -lrt
CFLAGS=-DSUNOS -DNANO_SECOND_SLEEP

OBJS=Thread.cpp EventClass.cpp MutexClass.cpp main.cpp


EXECS = thread

all: $(EXECS)

thread: $(OBJS)
	$(CC) $(CFLAGS) -o thread $(OBJS) $(LIBS)


clean:; rm -f *.o $(EXECS)
