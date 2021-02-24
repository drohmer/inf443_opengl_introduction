CXXFLAGS= -O2 -g -std=c++11 -Wall -Wextra
LDFLAGS = -lglfw -ldl
INCLUDE = -Iexternal/glad/include/
CXX = g++

all: pgm

pgm: main.o opengl_helper.o window_helper.o glad.o
	$(CXX) $^ -o $@ $(LDFLAGS)

main.o: src/main.cpp src/opengl_helper.hpp src/window_helper.hpp
	$(CXX) -c src/main.cpp -o $@ $(CXXFLAGS) $(INCLUDE)

opengl_helper.o: src/opengl_helper.cpp src/opengl_helper.hpp
	$(CXX) -c src/opengl_helper.cpp -o $@ $(CXXFLAGS) $(INCLUDE)

window_helper.o: src/window_helper.cpp src/window_helper.hpp
	$(CXX) -c src/window_helper.cpp -o $@ $(CXXFLAGS) $(INCLUDE)

glad.o: external/glad/src/glad.cpp
	$(CXX) -c $^ -o $@ $(CXXFLAGS) $(INCLUDE)

.PHONY: clean
clean:
	rm -f *.o pgm *~
