#include "puzzle.hpp"
#include <iostream>
#include <set>
#include <utility>

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
    // 1. Randomly place stars (where valid) for correct solution
    std::set<std::pair<int, int>> availableCells;

    for(unsigned int row = 0; row < cells.size(); row++) {
        for(unsigned int col = 0; col < cells[row].size(); col++) {
            availableCells.insert(std::make_pair(row, col));
        }
    }

    for(unsigned int i = 0; i < cells.size(); i++) {
        
    }
}