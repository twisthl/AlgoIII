CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

all: ej2

ej2: ej2.o funciones.o
	$(CXX) $(CXXFLAGS) ej2.o funciones.o -o ejercicio2

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.o ej1 test
