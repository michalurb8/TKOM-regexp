CF = -Wall -std=c++17 -Wextra -pedantic

all: main.o Source.o Token.o Scanner.o Parser.o Node.o Visitor.o Regexp.o
	g++ main.o Source.o Token.o Scanner.o Parser.o Node.o Visitor.o Regexp.o -o exe.out

main.o: main.cpp
	g++ -c $(CF) main.cpp -o main.o

Source.o: Source.cpp Source.h
	g++ -c $(CF) Source.cpp -o Source.o

Token.o: Token.cpp Token.h
	g++ -c $(CF) Token.cpp -o Token.o

Scanner.o: Scanner.cpp Scanner.h
	g++ -c $(CF) Scanner.cpp -o Scanner.o

Node.o: Node.cpp Node.h
	g++ -c $(CF) Node.cpp -o Node.o

Parser.o: Parser.cpp Parser.h
	g++ -c $(CF) Parser.cpp -o Parser.o

Visitor.o: Visitor.cpp Visitor.h
	g++ -c $(CF) Visitor.cpp -o Visitor.o

Regexp.o: Regexp.cpp Regexp.h
	g++ -c $(CF) Regexp.cpp -o Regexp.o

clean:
	rm *.o *.out -rf

run: all
	./exe.out

reset: clean all
