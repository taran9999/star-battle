#include <vector>
#include <stdlib.h>

class Puzzle {
    private:
        std::vector<std::vector<int>> cells;
    public:
        Puzzle(int n);
        void printCells();
        void generate();
};