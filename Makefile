# Makefile pentru proiectul "dive-log"
# Acest Makefile este utilizat pentru a compila și gestiona proiectul C++.

# Comenzi disponibile:
# 1. `make`         - Compilează proiectul și generează executabilul `dive-log`.
# 2. `make clean`   - Șterge fișierele generate (executabilul și fișierele obiect `.o`).

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Target executable
TARGET = dive-log

# Source files
SRCS = dive-log.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Phony targets
.PHONY: all clean
