CXX = g++

INCLUDE = inc/
SOURCE = src/
CPPFLAGS = -Wall -pedantic -std=c++17 -g -I .$(INCLUDE)
OBJECTS = main.o 

graf: $(OBJECTS)
	g++ -o checkers $(CPPFLAGS) $(OBJECTS)

main.o:

.PHONY: clean
clean:
	rm -f $(OBJECTS) checkers

%.o : $(SOURCE)%.cpp %.h
	$(CXX) -c $(CPPFLAGS) $<

%.h : $(INCLUDE)%.h