#include <vector>
#include <utility>
#include <unordered_set>
#include "puzzle.hpp"

// https://stackoverflow.com/a/15161034
struct pairHash {
    inline auto operator()(const std::pair<int, int>& p) const { return p.first * 31 + p.second; }
};

class Solver {
    using Solution = std::vector<std::pair<int, int>>;

    private:
        int stars;  // stars per row, column, and region

        void backtrack(int n, int starsPlaced, std::vector<std::vector<int>> regions,
        std::vector<int>& remainingInRow, std::vector<int>& remainingInColumn, std::vector<int>& remainingInRegion,
        Solution& currSolution, std::vector<Solution>& solutions);
        
        std::unordered_set<std::pair<int, int>> adjacentCells(std::vector<std::pair<int, int>> cells);
    public:
        Solver(int stars = 1);
        std::vector<Solution> solve(Puzzle p);
        void test();
};