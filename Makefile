CXX = g++

CPPFLAGS = -Wall -pedantic -std=c++17 -I ./inc
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJECTS = main.o game.o pawn.o board.o

graf: $(OBJECTS)
	$(CXX) $(OBJECTS) -o checkers $(SFMLFLAGS) $(CPPFLAGS) 

main.o: inc/game.h
game.o: inc/game.h inc/pawn.h inc/board.h
pawn.o: inc/pawn.h
board.o: inc/board.h inc/pawn.h

.PHONY: clean
clean:
	rm -f $(OBJECTS) checkers

%.o : ./src/%.cpp
	$(CXX) -c $(CPPFLAGS) $<