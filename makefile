# Compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I"C:/TEMP/OpenCV/opencv/build/include"

# Source files and object files
SOURCES = main.cc
OBJECTS = $(SOURCES:.cc=.o)

# Target executable
TARGET = main.exe

all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Rule to compile source files into object files
%.o: %.cc %.hh
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJECTS) $(TARGET)