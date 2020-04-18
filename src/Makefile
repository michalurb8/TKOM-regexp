CF = -Wall -std=c++11 -g
CF = 

all: main.o
	g++ main.o -o exe

main.o: main.cpp
	g++ -c $(CF) main.cpp -o main.o

clean:
	rm *.o exe -rf

run: all
	./exe

reset: clean all