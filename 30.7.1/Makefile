
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./src/include

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

SRC_LIB = $(SRC_DIR)/lib
SRC_APP = $(SRC_DIR)/app

OBJS = $(BUILD_DIR)/ThreadPool.o $(BUILD_DIR)/QuickSort.o
TARGET = $(BIN_DIR)/main

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_LIB)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS) $(SRC_APP)/main.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC_APP)/main.cpp $(OBJS) -o $(TARGET)

run: all
	$(TARGET) inputData.txt

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all run clean
