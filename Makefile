# Makefile for app

# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -Wall -std=c++11

# Source files
SRCS := app.cpp \
        source/rand.cpp \
        source/msg.cpp \
        source/objects.cpp

# Include directories
INC_DIRS := -I./include

# Output executable
TARGET := app

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)