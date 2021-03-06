TARGET ?= cmp_algorithms
SRC_DIRS ?= ./src
BUILD_DIR ?= ./build

SRCS := $(shell find $(SRC_DIRS) -name *.cpp)

$(TARGET):
	$(CXX) $(SRCS) -std=c++11 -O2 -o $(BUILD_DIR)/$(TARGET)	
	
.PHONY: clean

#clean:
#	cd $(BUILD_DIR); \
#	$(RM) $(TARGET) output/*
