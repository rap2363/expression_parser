CPP = g++
OFLAG = -o
CFLAG = -c

all: expressionparser

expressionparser: main.o DirectedAcyclicGraph.o
	$(CPP) DirectedAcyclicGraph.o main.o $(OFLAG) bin/expressionparser

DirectedAcyclicGraph.o: DirectedAcyclicGraph.cpp
	$(CPP) $(CFLAG) DirectedAcyclicGraph.cpp

main.o: main.cpp
	$(CPP) $(CFLAG) main.cpp

clean:
	rm *.o bin/expressionparser
