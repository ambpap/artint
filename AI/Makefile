# Compiler and flags
CXX = g++
CXXFLAGS = -Iinclude -Wall -Wextra -O2 -std=c++17

# Directories
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin

# Source and object files
SRCS = $(SRC_DIR)/Matrix.cpp $(SRC_DIR)/Neuralnetwork.cpp $(SRC_DIR)/main.cpp
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Output binary
TARGET = $(BIN_DIR)/main

# Create necessary directories
$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@


# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild everything
rebuild: clean all

