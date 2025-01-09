#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include "grid.hpp"
#include "puzzle.hpp"
#include "solver.hpp"

const int WINDOW_W = 800;
const int WINDOW_H = 600;
const int CELLS_PER_AXIS = 8;
const int PADDING = 20;

int main() {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("grid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
    if(!window) {
        std::cerr << "Window Creation Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) {
        std::cerr << "Renderer Creation Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int gridSize;
    int cellSize;
    int x;
    int y;
    if(WINDOW_H < WINDOW_W) {
        gridSize = WINDOW_H - 2 * PADDING;
        cellSize = gridSize / CELLS_PER_AXIS;
        x = (WINDOW_W - gridSize) / 2;
        y = PADDING;
    } else {
        gridSize = WINDOW_W - 2 * PADDING;
        cellSize = gridSize / CELLS_PER_AXIS;
        x = PADDING;
        y = (WINDOW_H - gridSize) / 2;
    }
    Grid grid(renderer, x, y, CELLS_PER_AXIS, CELLS_PER_AXIS, cellSize, cellSize);

    // Puzzle puzzle(CELLS_PER_AXIS);
    // puzzle.generate();
    // puzzle.printCells();
    std::vector<std::vector<int>> cells
    {
        {1, 1, 2, 2, 2, 2, 3, 3},
        {1, 1, 1, 1, 2, 2, 3, 3},
        {1, 1, 1, 1, 4, 4, 3, 3},
        {1, 1, 1, 1, 4, 4, 4, 5},
        {1, 6, 6, 6, 4, 7, 7, 5},
        {1, 6, 6, 8, 8, 8, 7, 7},
        {1, 6, 6, 8, 8, 8, 8, 7},
        {1, 8, 8, 8, 8, 8, 7, 7}
    };
    Puzzle puzzle(cells);
    puzzle.printCells();
    Solver solver;
    auto solutions = solver.solve(puzzle);
    std::cout << "Found " << solutions.size() << " solutions" << std::endl;
    for(auto s : solutions) {
        std::cout << "{ ";
        for(auto p : s) std::cout << "(" << p.first << ", " << p.second << ") ";
        std::cout << "}\n";
    }

    srand(42);
    std::vector<SDL_Color> randColors;
    for(auto i = 0; i < CELLS_PER_AXIS; i++) {
        Uint8 r = rand() % 256;
        Uint8 g = rand() % 256;
        Uint8 b = rand() % 256;
        std::cout << "Random color " << i + 1 << " set to { " << unsigned(r) << ", " << unsigned(g) << ", " << unsigned(b) << " }\n";
        randColors.push_back(SDL_Color {r, g, b, 255});
    }
    std::cout << std::endl;

    auto board = puzzle.board();
    // Maybe make an iterator over the board
    for(unsigned int i = 0; i < board.size(); i++) {
        for(unsigned int j = 0; j < board[i].size(); j++) {
            auto val = board[i][j];
            grid.getCell(i, j).setColor(randColors[val - 1]);
        }
    }

    // Darken the cells of the first solution to see
    if(solutions.size() > 0) {
        auto s = solutions[0];
        for(auto p : s) {
            auto i = p.first;
            auto j = p.second;
            grid.getCell(i, j).scaleBgColor(0.5);
        }
    }
    grid.render();
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while(true) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) goto Quit;
        }
    }

    Quit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}