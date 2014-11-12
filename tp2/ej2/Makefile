CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

all: ej2 test test2 test3 clean

ej2: ej2.o funciones.o
	$(CXX) $(CXXFLAGS) ej2.o funciones.o -o ejercicio2

test: test.o funciones.o
	$(CXX) $(CXXFLAGS) test.o funciones.o -o test

test2: test2.o funciones.o
	$(CXX) $(CXXFLAGS) test2.o funciones.o -o test2

test2: test3.o funciones.o
	$(CXX) $(CXXFLAGS) test3.o funciones.o -o test3

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.o 
