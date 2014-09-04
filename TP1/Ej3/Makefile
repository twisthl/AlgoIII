CXXFLAGS=-std=c++0x -lrt -pthread -Wall -O2

OBJ=algo3tp1.o ej3_parser.o ej3.o opciones.o aux.o

all: algo3tp1

dbg: $(OBJ)
	g++ -g $(OBJ) -o algo3tp1 $(CXXFLAGS)

algo3tp1: $(OBJ)
	g++ $(OBJ) -o algo3tp1 $(CXXFLAGS)

aux.o: aux.cpp
	g++ -c $(CXXFLAGS) aux.cpp

algo3tp1.o: algo3tp1.cpp
	g++ -c $(CXXFLAGS) algo3tp1.cpp

ej3_parser.o: ej3_parser.cpp
	g++ -c $(CXXFLAGS) ej3_parser.cpp

ej3.o: ej3.cpp
	g++ -c $(CXXFLAGS) ej3.cpp

opciones.o: opciones.cpp
	g++ -c $(CXXFLAGS) opciones.cpp

clean:
	rm -rf *o algo3tp1

