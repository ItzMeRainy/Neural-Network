CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.

SRC = main.cpp Matrix/matrix.cpp Layer/layer.cpp
OUT = program

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)