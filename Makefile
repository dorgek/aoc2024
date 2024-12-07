CXX       := g++
CXX_FLAGS := -Wall -Wextra -std=c++20 -ggdb -O3

BIN     := bin
SRC     := src
INCLUDE := include
LIB     := lib
LIBRARIES   := 
EXECUTABLE  := main
SOURCES := $(wildcard src/**/*.cpp src/*.cpp)


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	@echo "Executing..."
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE):
	@echo "Building... $(SOURCES)"
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -L$(LIB) $(SOURCES) -o $@ $(LIBRARIES)

clean:
	@echo "Clearing..."
	-rm $(BIN)/*
