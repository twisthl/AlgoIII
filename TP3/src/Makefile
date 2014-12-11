
CXXFLAGS=-std=c++0x -lrt -pthread -Wall

OBJ=main.o clock.o tipos.o 
#exacto.o busqueda_local.o dijkstra_class.o greed.o grasp.o

.PHONY: clean dbg

all: algo3tp3

opt: CXXFLAGS+=-O3
opt: algo3tp3

algo3tp3: $(OBJ)
	g++ $(OBJ) -o algo3tp3 $(CXXFLAGS)

# no hacen falta, los busca solo make!

# exacto.o: exacto.cpp
# 	g++ -c $(CXXFLAGS) exacto.cpp 

# io.o: io.cpp
# 	g++ -c $(CXXFLAGS) io.cpp

#dijkstra.o: dijkstra.cpp
#	g++ -c $(CXXFLAGS) dijkstra.cpp

#dijkstra_class.o: dijkstra_class.cpp
#	g++ -c $(CXXFLAGS) dijkstra_class.cpp

#busqueda_local.o: busqueda_local.cpp
#	g++ -c $(CXXFLAGS) busqueda_local.cpp

# clock.o: clock.cpp
# 	g++ -c $(CXXFLAGS) clock.cpp

# main.o: main.cpp
# 	g++ -c $(CXXFLAGS) main.cpp

# opciones.o: opciones.cpp
# 	g++ -c $(CXXFLAGS) opciones.cpp

# tipos.o: tipos.cpp tipos.h
# 	g++ -c $(CXXFLAGS) tipos.cpp

clean:
	rm -rf *o algo3tp3 core

check-syntax:
	g++ -o /dev/null -S $(CXXFLAGS)
