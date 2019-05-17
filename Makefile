CXX = g++

CPPFLAGS = -Wall -pedantic -std=c++17 -g -I ./inc
OBJECTS = main.o game.o pawn.o board.o

graf: $(OBJECTS)
	g++ -o checkers $(CPPFLAGS) $(OBJECTS)

main.o:
game.o: inc/game.h inc/pawn.h inc/board.h
pawn.o: inc/pawn.h inc/game.h
board.o: inc/board.h inc/game.h

.PHONY: clean
clean:
	rm -f $(OBJECTS) checkers

%.o : ./src/%.cpp
	$(CXX) -c $(CPPFLAGS) $<