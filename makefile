CPPFLAGS = -std=c++17 -Wall
TARGET = ./bin/program
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:src/%.cpp = obj/%.o)
GTKI = `pkg-config gtk+-3.0 --cflags --libs` -export-dynamic 
GTKL = -lgtk-3.0

all: $(TARGET)

$(TARGET): $(OBJ)
	g++  $(CPPFLAGS) -o $@ $^ $(GTKI) 

$(OBJ): $(SRC)
	g++ $(CPPFLAGS)  -c $^ 

clear:
	rm -rf ./bin/* ./obj/*