#include "solver.hpp"
#include <iostream>

using Solution = std::vector<std::pair<int, int>>;

Solver::Solver(int stars) : stars(stars) {}

void Solver::backtrack(int n, int starsPlaced, std::vector<std::vector<int>> regions,
std::vector<int>& remainingInRow, std::vector<int>& remainingInColumn, std::vector<int>& remainingInRegion,
Solution& currSolution, std::vector<Solution>& solutions) {
    if(n * stars == starsPlaced) {
        solutions.push_back(currSolution);
        return;
    }

    auto adj = adjacentCells(currSolution);

    // Naive backtracking just go row by row
    auto row = starsPlaced;
    for(std::size_t col = 0; col < regions[row].size(); col++) {
        auto region = regions[row][col];
        if(remainingInRow[row] > 0 && remainingInColumn[col] > 0 && remainingInRegion[region - 1] > 0 && adj.count(std::make_pair(row, col)) == 0) {
            remainingInRow[row]--;
            remainingInColumn[col]--;
            remainingInRegion[region - 1]--;
            currSolution.push_back(std::make_pair(row, col));

            backtrack(n, starsPlaced + 1, regions, remainingInRow, remainingInColumn, remainingInRegion, currSolution, solutions);

            remainingInRow[row]++;
            remainingInColumn[col]++;
            remainingInRegion[region - 1]++;
            currSolution.pop_back();
        }
    }
}

std::vector<Solution> Solver::solve(Puzzle p) {
    auto n = p.size();
    auto regions = p.board();
    std::vector<int> remainingInRow(n, stars);
    std::vector<int> remainingInColumn(n, stars);
    std::vector<int> remainingInRegion(n, stars);
    Solution currSolution;
    std::vector<Solution> solutions;

    backtrack(n, 0, regions, remainingInRow, remainingInColumn, remainingInRegion, currSolution, solutions);

    return solutions;
}

std::unordered_set<std::pair<int, int>, pairHash> Solver::adjacentCells(std::vector<std::pair<int, int>> cells) {
    std::unordered_set<std::pair<int, int>, pairHash> adj;

    for(auto p : cells) {
        auto row = p.first;
        auto col = p.second;

        for(auto r = -1; r <= 1; r++) {
            for(auto c = -1; c <= 1; c++) adj.insert(std::make_pair(row + r, col + c));
        }
    }

    return adj;
}