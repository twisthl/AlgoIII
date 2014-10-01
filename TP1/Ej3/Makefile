CXXFLAGS=-std=c++0x -lrt -pthread -Wall -O2

OBJ=tp1ej3.o ej3_parser.o ej3.o opciones.o clock.o

all: tp1ej3

dbg: $(OBJ)
	g++ -g $(OBJ) -o tp1ej3 $(CXXFLAGS)

tp1ej3: $(OBJ)
	g++ -g $(OBJ) -o tp1ej3 $(CXXFLAGS)

clock.o: clock.cpp
	g++ -g -c $(CXXFLAGS) clock.cpp

tp1ej3.o: tp1ej3.cpp
	g++ -g -c $(CXXFLAGS) tp1ej3.cpp

ej3_parser.o: ej3_parser.cpp
	g++ -g -c $(CXXFLAGS) ej3_parser.cpp

ej3.o: ej3.cpp
	g++ -g -c $(CXXFLAGS) ej3.cpp

opciones.o: opciones.cpp
	g++ -g -c $(CXXFLAGS) opciones.cpp

clean:
	rm -rf *o tp1ej3

