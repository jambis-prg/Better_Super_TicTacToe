# Compiler flag
CC = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Wno-error=implicit-fallthrough -I$(SFML_INCLUDE) -I$(UTILS_DIR) -I$(INCLUDE_DIR) -I$(TYPES_DIR)

# Delete
RM = del /f

# Paths
SRC_DIR = src
SFML_INCLUDE = SFML_src/include
SFML_LIB = SFML_src/lib
INCLUDE_DIR = include
UTILS_DIR = Utils
TYPES_DIR = types
BIN = bin
BIN-INT = bin-int

# Files
MAIN = main.cpp
EXE = SuperTicTacToe

# Find all .cpp files in SRC_DIR and create corresponding .o files in BIN
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
UTILS_FILES = $(wildcard $(UTILS_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN-INT)/%.o,$(SRC_FILES)) \
       $(patsubst $(UTILS_DIR)/%.cpp,$(BIN-INT)/%.o,$(UTILS_FILES)) \
       $(BIN-INT)/SuperTicTacToe.o

all: compile link

compile: $(OBJS)

# Compile main.cpp separately
$(BIN-INT)/SuperTicTacToe.o: $(MAIN)
	$(CC) $(CXXFLAGS) -c $< -I$(SFML_INCLUDE) -o $@

# Compile .cpp in SRC_DIR
$(BIN-INT)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CXXFLAGS) -c $< -I$(SFML_INCLUDE) -o $@

# Compile .cpp files in UTILS_DIR (dependency on colors.hpp)
$(BIN-INT)/%.o: $(UTILS_DIR)/%.cpp $(UTILS_DIR)/colors.hpp
	$(CC) $(CXXFLAGS) -c $< -I$(SFML_INCLUDE) -o $@

link:
	$(CC) $(CXXFLAGS) $(OBJS) -o $(BIN)/$(EXE) -L$(SFML_LIB) -lsfml-graphics -lsfml-window -lsfml-system

clean:
	if exist $(EXE).exe $(RM) $(EXE).exe
	for %%f in ($(BIN)\*.o) do $(RM) %%f