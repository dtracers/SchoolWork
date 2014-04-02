all: Main

Main: Utility.o Parser.o Evaluator.o Main.o
	g++ -o Main Utility.o Parser.o Evaluator.o Main.o

Main.o: Parser.h Evaluator.h RuntimeException.h
	g++ -c Main.cpp

Evaluator.o: Evaluator.h Parser.h Utility.h LinkedStack.h LinkedQueue.h LinkedList.h Utility.h RuntimeException.h
	g++ -c Evaluator.cpp

Parser.o: Parser.h LinkedStack.h LinkedQueue.h LinkedList.h Utility.h RuntimeException.h
	g++ -c Parser.cpp

Utility.o: Utility.h
	g++ -c Utility.cpp

clean:
	rm *.o Main
