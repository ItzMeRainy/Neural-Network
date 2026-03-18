CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRC = main.cpp Matrix/matrix.cpp
OUT = program

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)