CC = g++
CFLAGS = -g -Wall -I/usr/include/irrlicht -std=c++11
LDFLAGS = -lIrrlicht -lGL

PROG = hello

RM= rm -rf

hello: hello.o
	${CC} ${LDFLAGS} -o hello hello.o

hello.o: hello.cpp
	${CC} ${CFLAGS} -c hello.cpp

clean:
	${RM} *.o *~ ${PROG}

.PHONY: clean
