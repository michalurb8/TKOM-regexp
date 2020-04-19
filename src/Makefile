CF = -Wall -std=c++11 -g

all: main.o Source.o Token.o Scanner.o
	g++ main.o Source.o Token.o Scanner.o -o exe.out

main.o: main.cpp
	g++ -c $(CF) main.cpp -o main.o

Source.o: Source.cpp Source.h
	g++ -c $(CF) Source.cpp -o Source.o

Token.o: Token.cpp Token.h
	g++ -c $(CF) Token.cpp -o Token.o

Scanner.o: Scanner.cpp Scanner.h
	g++ -c $(CF) Scanner.cpp -o Scanner.o

test: build_test
	./test.out

build_test: test.o Source.o Token.o Scanner.o
	g++ test.o Source.o Token.o Scanner.o -o test.out

test.o: test.cpp
	g++ -c $(CF) test.cpp -o test.o

clean:
	rm *.o *.out -rf

run: all
	./exe.out

reset: clean all