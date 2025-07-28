# idocohen963@gmail.com
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose

# Source files
DEMO_SOURCES = Demo.cpp
TEST_SOURCES = Test.cpp

# Object files
DEMO_OBJECTS = $(DEMO_SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Executables
DEMO_EXEC = demo
TEST_EXEC = Test_exec

.PHONY: all Main test valgrind clean

all: Main test

# Build and run the demo
Main: $(DEMO_EXEC)
	./$(DEMO_EXEC)

# Build demo executable
$(DEMO_EXEC): $(DEMO_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Build and run tests
test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Build test executable
$(TEST_EXEC): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile object files
%.o: %.cpp MyContainer.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Memory leak detection
valgrind: $(TEST_EXEC) $(DEMO_EXEC)
	@echo "=== Running Valgrind on Tests ==="
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_EXEC)
	@echo "=== Running Valgrind on Demo ==="
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(DEMO_EXEC)
# Clean build artifacts
clean:
	rm -f *.o $(DEMO_EXEC) $(TEST_EXEC)
