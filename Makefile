CC=gcc
CFLAGS=-lWarn -pedantic 

temp:	temp.o libmyifttt.a
	$(CC) temp.o -L. -lmyifttt -lcurl -o temp

tester: tester.o libmyifttt.a
	cc tester.o -L. -lmyifttt -lcurl -o tester

libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o

ifttt.o: 	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

temp.o:	temp.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

tester.o:	tester.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

all:    temp tester

clean:	rm temp tester  *.o 
