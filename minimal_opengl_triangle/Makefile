CXXFLAGS= -O2 -g -std=c++1y -Wall -Wextra
LDFLAGS = -lglfw -ldl
INCLUDE = -Iexternal/glad/include/
CXX = g++

all: pgm

pgm: main.o glad.o
	$(CXX) $^ -o $@ $(LDFLAGS)

main.o: src/main.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS) $(INCLUDE)

glad.o: external/glad/src/glad.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS) $(INCLUDE)

.PHONY: clean
clean:
	rm -f *.o pgm *~
