#include <vector>
#include <utility>

class Solver {
    using Solution = std::vector<std::pair<int, int>>;

    private:
        int stars;  // stars per row, column, and region
        std::vector<int> remainingInRow;
        std::vector<int> remainingInColumn;
        std::vector<int> remainingInRegion;
};