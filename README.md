# Design Pattern
> Made by [Nerya Bigon]() and [Ori Howard]()  

In this assignment we've implemented a thread-safe queue with cond, active object, active objects pipe-line, guard (scope mutex), singleton and a reactor.  
- We've used code from the beej networking guide https://beej.us/guide/bgnet/html/#poll  

## Assumptions
since we've implemented the assignment in CPP there are a couplle of logical assumption we've made:
- since we have constructors and destructors we didn't used the names from the assignmnet but the name of the class.
- the active object doesn't recive pointer to a queue since it has it's own queue, (also the destructor doesn't need to recive the AO to destroy).
- the Reactor constructor work like a regular constructor (return an instance).
- `installHandler` doesn't get a reactor since it is a member function


### How To Run  
1. Download this repository
2. Open a terminal window in the main folder and run the following command:

```
make all
```  

to run the `main1` that simulate the design patterns run the following command:
```
./main1
```

#### Active Object
to simulate the active object you'll first need to run the server, and then send text to sipher via a client (in our case telnet works beautifully). 
3. run the server using the following command:

```
./server
```

4. To run the telnet client - the command is:  

```
telnet remotehostname 3490
```  

#### Reactor
in order to simulate the reactor you'll need to run the poll Server and connect to it with clients.

5. To run the pollServer run the following comand in a seperate terminal:
```
./pollServer
```

6. run clients by opening a separate terminals and running the following command:

```
./pollClient host
```  

* For example:  
```
./pollClient 127.0.0.1
```    

#### Guard

to run the main simulating the guard run the following command:
```
./guardMain
```

#### Singleton
to run the main simulating the singleton run the following command:
```
./singletonMain
```

#### Tests
to run the tests run the following command:
```
./test
```
