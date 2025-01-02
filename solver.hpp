#include <vector>
#include <utility>
#include "puzzle.hpp"

class Solver {
    using Solution = std::vector<std::pair<int, int>>;

    private:
        int stars;  // stars per row, column, and region

        void backtrack(int n, int starsPlaced, std::vector<std::vector<int>> regions,
        std::vector<int>& remainingInRow, std::vector<int>& remainingInColumn, std::vector<int>& remainingInRegion,
        Solution& currSolution, std::vector<Solution>& solutions);
    public:
        Solver(int stars = 1);
        std::vector<Solution> solve(Puzzle p);
};