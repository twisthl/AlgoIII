CXX = g++
#CXX = clang
DBG = gdb

MAIN=tp3

OBJ=main.o reloj.o

.PHONY: all clean

release: CXXFLAGS = -lrt -O2 -std=c++0x

debug: CXXFLAGS = -ggdb -lrt -std=c++0x

release: all
debug: all

all: $(MAIN)

$(MAIN): $(OBJ)
	$(CXX) $(OBJ) $(CXXFLAGS) -o $@ 

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(MAIN)
	rm -rf *.o

