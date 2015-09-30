CC = g++
CFLAGS = -g -Wall -I/usr/include/irrlicht -std=c++11
LDFLAGS = -lIrrlicht -lGL

PROG = hello

RM= rm -rf

hello: hello.o
	${CC} ${LDFLAGS} -o hello hello.o

hello.o: hello.cpp
	${CC} ${CFLAGS} -c hello.cpp

s1: simple_md2.o
	${CC} ${LDFLAGS} -o simple_md2 simple_md2.o

simple_md2.o: simple_md2.cpp
	${CC} ${CFLAGS} -c simple_md2.cpp

q1: quake3map.o
	${CC} ${LDFLAGS} -o quake3map quake3map.o

quake3map.o: quake3map.cpp
	${CC} ${CFLAGS} -c quake3map.cpp

clean:
	${RM} *.o *~ ${PROG}

.PHONY: clean
