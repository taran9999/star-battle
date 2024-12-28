#include <SDL2/SDL.h>
#include <iostream>
#include "grid.hpp"
#include "puzzle.hpp"

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

    if(WINDOW_H < WINDOW_W) {
        int gridSize = WINDOW_H - 2 * PADDING;
        int cellSize = gridSize / CELLS_PER_AXIS;
        int x = (WINDOW_W - gridSize) / 2;
        // drawGrid(renderer, x, PADDING, cellSize, CELLS_PER_AXIS);
        Grid grid(renderer, x, PADDING, CELLS_PER_AXIS, CELLS_PER_AXIS, cellSize, cellSize);
        grid.render();
        SDL_RenderPresent(renderer);
    } else {
        int gridSize = WINDOW_W - 2 * PADDING;
        int cellSize = gridSize / CELLS_PER_AXIS;
        int y = (WINDOW_H - gridSize) / 2;
        // drawGrid(renderer, PADDING, y, cellSize, CELLS_PER_AXIS);
        Grid grid(renderer, PADDING, y, CELLS_PER_AXIS, CELLS_PER_AXIS, cellSize, cellSize);
        grid.render();
        SDL_RenderPresent(renderer);
    }

    Puzzle puzzle(CELLS_PER_AXIS);
    puzzle.generate();
    puzzle.printCells();

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