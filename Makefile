CC=g++
AR=ar
FLAGS=-Wall -g

all: libdesign.so server test pollServer pollClient testSingleton

testSingleton: testSingleton.o singleton.o
	$(CC) $(FLAGS) -o testSingleton testSingleton.o singleton.o

pollClient: pollClient.o reactor.o
	$(CC) $(FLAGS) -o pollClient pollClient.o reactor.o -lpthread

pollServer: pollServer.o reactor.o
	$(CC) $(FLAGS) -o pollServer pollServer.o reactor.o -lpthread

server: server.o libdesign.so activeObject.o util.o
	$(CC) $(FLAGS) -o server server.o -lpthread ./libdesign.so activeObject.o util.o


libdesign.so: guard.o singleton.o safeQueue.o data.o
	$(CC) -shared -fPIC -o libdesign.so guard.o singleton.o safeQueue.o data.o

test: test.o activeObject.o libdesign.so util.o
	$(CC) $(FLAGS) -o test test.o activeObject.o util.o ./libdesign.so -lpthread


test.o: test.cpp activeObject.hpp 
	$(CC) $(FLAGS) -c test.cpp 

guard.o: guard.cpp guard.hpp
	$(CC) $(FLAGS) -c guard.cpp

singleton.o: singleton.cpp singleton.hpp
	$(CC) $(FLAGS) -c singleton.cpp

testSingleton.o: testSingleton.cpp singleton.hpp
	$(CC) $(FLAGS) -c testSingleton.cpp

reactor.o: reactor.cpp reactor.hpp
	$(CC) $(FLAGS) -c reactor.cpp

server.o: server.cpp activeObject.hpp
	$(CC) $(FLAGS) -c server.cpp

pollServer.o: pollServer.cpp reactor.hpp
	$(CC) $(FLAGS) -c pollServer.cpp


pollClient.o: pollClient.cpp
	$(CC) $(FLAGS) -c pollClient.cpp

util.o: util.cpp util.hpp activeObject.hpp safeQueue.hpp
	$(CC) $(FLAGS) -c util.cpp	

data.o: data.cpp data.hpp
	$(CC) $(FLAGS) -c data.cpp


activeObject.o: activeObject.cpp activeObject.hpp safeQueue.hpp data.hpp util.hpp
	$(CC) $(FLAGS) -c activeObject.cpp	


safeQueue.o: safeQueue.cpp safeQueue.hpp
	$(CC) $(FLAGS) -c safeQueue.cpp



.PHONY: clean all

clean:
	rm -f *.o *.a *.so server test pollServer pollClient testSingleton