#include "puzzle.hpp"
#include <iostream>
#include <utility>
#include <deque>
#include <algorithm>
#include <random>

Puzzle::Puzzle(int n) : cells(n, std::vector<int>(n)), n(n) {}

Puzzle::Puzzle(std::vector<std::vector<int>> cells) : cells(cells), n((int)cells.size()) {}

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
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) availableCells.push_back(std::make_pair(row, col));
    }

    std::mt19937 g(42);
    std::shuffle(availableCells.begin(), availableCells.end(), g);

    // 1. Choose n random positions to begin the regions
    for(int i = 1; i <= n; i++) {
        auto pos = availableCells.front();
        auto row = pos.first;
        auto col = pos.second;
        cells[row][col] = i;
        availableCells.pop_front();
        std::cout << "Region " << i << " begins at (" << row << ", " << col << ")\n";
    }
    std::cout << std::endl;

    // 2. For the remaining cells, take a random value from surrounding cells
    std::uniform_int_distribution<int> d(0, 3);
    std::vector<int> x_dir {-1, 0, 0, 1};
    std::vector<int> y_dir {0, -1, 1, 0};

    unsigned int its = 0;
    while(availableCells.size() > 0) {
        auto pos = availableCells.front();
        auto currRow = pos.first;
        auto currCol = pos.second;
        availableCells.pop_front();

        auto dir_idx = d(g);
        auto dx = x_dir[dir_idx];
        auto dy = y_dir[dir_idx];
        while((currRow == 0 && dx == -1) || (currCol == 0 && dy == -1) || (currRow == n - 1 && dx == 1) || (currCol == n - 1 && dy == 1)) {
            dir_idx = d(g);
            dx = x_dir[dir_idx];
            dy = y_dir[dir_idx];
        }

        cells[currRow][currCol] = cells[currRow + dx][currCol + dy];
        
        if(cells[currRow][currCol] == 0) {
            std::cout << "(" << currRow << ", " << currCol << ") remains free\n";
            availableCells.push_back(pos);
        } else {
            std::cout << "(" << currRow << ", " << currCol << ") assigned to region " << cells[currRow][currCol] << "\n";
        }

        its++;
    }
    std::cout << "\n" << (n - 1) * n << " cells assigned in " << its << " iterations\n" << std::endl;

    // 3. Solve (validate that a single solution exists)
}

int Puzzle::size() { return n; }

std::vector<std::vector<int>> Puzzle::board() { return cells; }