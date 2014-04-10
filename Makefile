CXX=g++
all:prep main

prep:
	if [ -d bin ]; then echo '' > /dev/null; else mkdir bin; fi
	if [ -d tmp ]; then echo '' > /dev/null; else mkdir tmp; fi

func.o: func.cpp func.h
	$(CXX) -g -c func.cpp -o tmp/func.o
main.o: main.cpp func.h
	$(CXX) -g -c main.cpp -o tmp/main.o
main:prep func.o main.o func.h
	$(CXX) -g tmp/*.o -o main `pkg-config opencv --cflags --libs`

clean:
	rm bin/* tmp/*
