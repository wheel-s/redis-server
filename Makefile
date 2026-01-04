# CXX = g++
# CXXFLAGS = -wall -wextra -std=c++17 -Iinclude

# SRC = \
# 	main.cpp \
# 	src/commandHandler.cpp \
# 	src/serever.cpp

# OBJ = $(SRC:.cpp=.o)

# TARGET = redisServer


# all:$(TARGET)

# $(TARGET):$(OBJ)
#    $(CXX) $(OBJ) -O $(TARGET)

# %.o:%.cpp
# 	$(CXX) $(CXXFLAGS) -C $<-O$@

# clean:
# 	rm -f $(OBJ) $(TARGET)
	

CXX = g++
CXXFLAGS = -std=c++17 -Wall -pthread -MMD -MP -O2

SRC_DIR = src
BUILD_DIR = build

SRCS := main.cpp $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(addprefix $(BUILD_DIR)/, $(notdir $(SRCS:.cpp=.o)))

TARGET = ./redisServer

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.cpp| $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o:main.cpp| $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) -lws2_32

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all

run: all
	./$(TARGET)