CXXFLAGS=-std=c++0x -lrt -pthread -Wall -O2

OBJ=tp2ej1.o tipos.o ej1.o opciones.o ej1_parser.o dijkstra_autofill.o

all: tp2ej1

dbg: $(OBJ)
	g++ -g $(OBJ) -o tp2ej1 $(CXXFLAGS)

tp2ej1: $(OBJ)
	g++ $(OBJ) -o tp2ej1 $(CXXFLAGS)

tp2ej1.o: tp2ej1.cpp
	g++ -g -c $(CXXFLAGS) tp2ej1.cpp

tipos.o: tipos.cpp
	g++ -g -c $(CXXFLAGS) tipos.cpp

dijkstra_autofill.o: dijkstra_autofill.cpp
	g++ -g -c $(CXXFLAGS) dijkstra_autofill.cpp

ej1_parser.o: ej1_parser.cpp
	g++ -g -c $(CXXFLAGS) ej1_parser.cpp

ej1.o: ej1.cpp
	g++ -g -c $(CXXFLAGS) ej1.cpp

opciones.o: opciones.cpp
	g++ -g -c $(CXXFLAGS) opciones.cpp

clean:
	rm -rf *o tp2ej1

