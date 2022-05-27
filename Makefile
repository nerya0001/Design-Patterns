CC=g++
AR=ar
FLAGS=-Wall -g

all: main1


main1: main1.o libdesign.so
	$(CC) $(FLAGS) -o  main1 main1.o -lpthread -ltbb ./libdesign.so

libdesign.so: guard.o singleton.o reactor.o
	$(CC) -shared -o libdesign.so guard.o singleton.o reactor.o -fPIC

main1.o: main1.cpp main1.hpp
	$(CC) $(FLAGS) -c main1.cpp

guard.o: guard.cpp guard.hpp
	$(CC) $(FLAGS) -c guard.cpp

singleton.o: singleton.cpp singleton.hpp
	$(CC) $(FLAGS) -c singleton.cpp

reactor.o: reactor.cpp reactor.hpp
	$(CC) $(FLAGS) -c reactor.cpp


.PHONY: clean all

clean:
	rm -f *.o *.a *.so main1