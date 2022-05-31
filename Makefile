CC=g++
AR=ar
FLAGS=-Wall -g

all: libdesign.so server


# main1: main1.o libdesign.so
# 	$(CC) $(FLAGS) -o  main1 main1.o -lpthread -ltbb ./libdesign.so
server: server.o libdesign.so activeObject.o util.o
	$(CC) $(FLAGS) -o server server.o -lpthread ./libdesign.so activeObject.o util.o

libdesign.so: guard.o singleton.o reactor.o safeQueue.o data.o
	$(CC) -shared -fPIC -o libdesign.so guard.o singleton.o reactor.o safeQueue.o data.o

# main: main.o activeObject.o libdesign.so util.o
# 	$(CC) $(FLAGS) -o main main.o activeObject.o util.o ./libdesign.so -lpthread


# main.o: main.cpp activeObject.hpp 
# 	$(CC) $(FLAGS) -c main.cpp 

guard.o: guard.cpp guard.hpp
	$(CC) $(FLAGS) -c guard.cpp

singleton.o: singleton.cpp singleton.hpp
	$(CC) $(FLAGS) -c singleton.cpp

reactor.o: reactor.cpp reactor.hpp
	$(CC) $(FLAGS) -c reactor.cpp

server.o: server.cpp activeObject.hpp
	$(CC) $(FLAGS) -c server.cpp

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
	rm -f *.o *.a *.so server