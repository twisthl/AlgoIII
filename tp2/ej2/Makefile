CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

all: ej2 clean

ej2: ej2.o funciones.o
	$(CXX) $(CXXFLAGS) ej2.o funciones.o -o ejercicio2

test: test.o funciones.o
	$(CXX) $(CXXFLAGS) test.o funciones.o -o test

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.o 
