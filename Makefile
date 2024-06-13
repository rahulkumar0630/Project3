# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++14 -Wall

# Directories
SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/load_balancer

# Default target
all: $(TARGET)

# Create bin and obj directories if they don't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build the target
$(TARGET): $(OBJ_DIR) $(BIN_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean
