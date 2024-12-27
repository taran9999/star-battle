#include "grid.hpp"

GridCell::GridCell(SDL_Color bgColor) : bgColor(bgColor) {}

void GridCell::setColor(SDL_Color color) { bgColor = color; }

void GridCell::render(SDL_Renderer* renderer, int x, int y, int w, int h) {
    SDL_Rect rect {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(renderer, &rect);
}

Grid::Grid(SDL_Renderer* renderer, int x, int y, int rows, int cols, int cellW, int cellH)
    : renderer(renderer), x(x), y(y), cellW(cellW), cellH(cellH), cells(rows, std::vector<GridCell>(cols)) {}

GridCell& Grid::getCell(int row, int col) { return cells[row][col]; }

void Grid::render() {
    // Render grid cells
    for(unsigned int row = 0; row < cells.size(); row++) {
        for(unsigned int col = 0; col < cells[row].size(); col++) {
            int cellX = x + col * cellW;
            int cellY = y + row * cellH;
            cells[row][col].render(renderer, cellX, cellY, cellW, cellH);
        }
    }

    // Render grid lines
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for(unsigned int i = 0; i < cells[0].size() + 1; i++) {
        SDL_RenderDrawLine(renderer, x + i * cellW, y, x + i * cellW, y + cells[0].size() * cellH);
    }

    for(unsigned int j = 0; j < cells.size() + 1; j++) {
        SDL_RenderDrawLine(renderer, x, y + j * cellH, x + cells.size() * cellW, y + j * cellH);
    }
}