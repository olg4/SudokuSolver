CXX       := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

EXECUTABLE  := sudokuSolver

$(BIN)/$(EXECUTABLE): *.cpp
	@echo "🔨 Building..."
	$(CXX) $(CXX_FLAGS) sudoku.cpp solver.cpp -o $(EXECUTABLE)