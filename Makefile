
CXX = g++


CXXFLAGS = -std=c++14 -Wall


SRC_DIR = .
OBJ_DIR = obj
BIN_DIR = bin


SRCS = $(wildcard $(SRC_DIR)/*.cpp)


OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


TARGET = $(BIN_DIR)/load_balancer


all: $(TARGET)


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)


$(TARGET): $(OBJ_DIR) $(BIN_DIR) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)


.PHONY: all clean
