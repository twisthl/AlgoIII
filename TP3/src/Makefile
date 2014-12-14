CXXFLAGS=-std=c++0x -lrt -pthread -Wall

OBJ=algo3tp3.o clock.o tipos.o opciones.o parser.o exacto.o 
#greed.o

all: algo3tp3

dbg: $(OBJ)
	g++ -g $(OBJ) -o algo3tp3 $(CXXFLAGS)

algo3tp3: $(OBJ)
	g++ $(OBJ) -o algo3tp3 $(CXXFLAGS)

algo3tp3.o: algo3tp3.cpp
	g++ -g -c $(CXXFLAGS) algo3tp3.cpp

clock.o: clock.cpp
	g++ -g -c $(CXXFLAGS) clock.cpp

tipos.o: tipos.cpp
	g++ -g -c $(CXXFLAGS) tipos.cpp

opciones.o: opciones.cpp
	g++ -g -c $(CXXFLAGS) opciones.cpp

parser.o: parser.cpp
	g++ -g -c $(CXXFLAGS) parser.cpp

exacto.o: exacto.cpp
	g++ -g -c $(CXXFLAGS) exacto.cpp

greed.o: greed.cpp
	g++ -g -c $(CXXFLAGS) greed.cpp

clean:
	rm -rf *o algo3tp3
