#pragma once

#include <vector>
#include <stdlib.h>

class Puzzle {
    private:
        std::vector<std::vector<int>> cells;
        int n;
    public:
        Puzzle(int n);
        Puzzle(std::vector<std::vector<int>> cells);
        void printCells();
        void generate();
        int size();
        std::vector<std::vector<int>> board();
};