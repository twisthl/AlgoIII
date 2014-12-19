CXXFLAGS=-std=c++0x -lrt -pthread -Wall

OBJ=algo3tp3.o clock.o tipos.o opciones.o parser.o exacto.o greed.o busqueda_local.o grasp.o peorSolucion.o randomSolucion.o
OBJ2=testingGrasp.o clock.o tipos.o opciones.o parser.o exacto.o greed.o busqueda_local.o grasp.o peorSolucion.o randomSolucion.o

all: algo3tp3

dbg: $(OBJ) testingGrasp.o
	g++ -g $(OBJ) -o algo3tp3 $(CXXFLAGS)
	g++ -g $(OBJ2) -o testingGrasp $(CXXFLAGS)

algo3tp3: $(OBJ) testingGrasp.o
	g++ $(OBJ) -o algo3tp3 $(CXXFLAGS)
	g++ $(OBJ2) -o testingGrasp $(CXXFLAGS)

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

busqueda_local.o: busqueda_local.cpp
	g++ -g -c $(CXXFLAGS) busqueda_local.cpp

grasp.o: grasp.cpp
	g++ -g -c $(CXXFLAGS) grasp.cpp
	
peorSolucion.o: peorSolucion.cpp
	g++ -g -c $(CXXFLAGS) peorSolucion.cpp

randomSolucion.o: randomSolucion.cpp
	g++ -g -c $(CXXFLAGS) randomSolucion.cpp

testingGrasp.o: testingGrasp.cpp
	g++ -g -c $(CXXFLAGS) testingGrasp.cpp

clean:
	rm -rf *o algo3tp3
