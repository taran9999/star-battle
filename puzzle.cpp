#include "puzzle.hpp"
#include <iostream>
#include <utility>
#include <deque>
#include <algorithm>
#include <random>

Puzzle::Puzzle(int n) : cells(n, std::vector<int>(n)) { srand(42); }

void Puzzle::printCells() {
    for(unsigned int row = 0; row < cells.size(); row++) {
        for(unsigned int col = 0; col < cells[row].size(); col++) {
            if(cells[row][col] == -1) std::cout << "x ";
            else std::cout << cells[row][col] << ' ';
        }
        std::cout << '\n';
    }
}

void Puzzle::generate() {
    std::deque<std::pair<int, int>> availableCells;
    for(unsigned int row = 0; row < cells.size(); row++) {
        for(unsigned int col = 0; col < cells[0].size(); col++) availableCells.push_back(std::make_pair(row, col));
    }

    std::mt19937 g(42);
    std::shuffle(availableCells.begin(), availableCells.end(), g);

    // 1. Choose n random positions to begin the regions
    for(unsigned int i = 1; i <= cells.size(); i++) {
        auto pos = availableCells.front();
        auto row = pos.first;
        auto col = pos.second;
        cells[row][col] = i;
        availableCells.pop_front();
        std::cout << "Region " << i << " begins at (" << row << ", " << col << ")\n";
    }
    std::cout << std::endl;

    // 2. For the remaining cells, take a random value from surrounding cells
}