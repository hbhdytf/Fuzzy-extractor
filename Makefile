CXX=g++
all: func

func.o: func.cpp func.h
	$(CXX) -c func.cpp

func: func.o func.h
	$(CXX) func.o -o func

clean:
	rm func func.o
