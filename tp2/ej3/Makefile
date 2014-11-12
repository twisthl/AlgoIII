CXX = g++
CXXFLAGS=-g -Wall -std=c++98 -Werror -fno-stack-protector

all: ej3 clean

ej3: ej3.o funciones.o
	$(CXX) $(CXXFLAGS) ej3.o funciones.o -o ej3

test: test.o funciones.o
	$(CXX) $(CXXFLAGS) test.o funciones.o -o test

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f *.o 
