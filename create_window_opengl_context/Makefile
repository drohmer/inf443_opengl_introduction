CXXFLAGS= -O2 -g -std=c++11 -Wall -Wextra
LDFLAGS = -lglfw -ldl
CXX = g++

all: pgm

pgm: main.o glad.o
	$(CXX) $^ -o $@ $(LDFLAGS)

main.o: src/main.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

glad.o: external/glad/src/glad.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -f *.o pgm *~
