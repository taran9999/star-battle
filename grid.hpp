#include <SDL2/SDL.h>
#include <vector>

class GridCell {
    private:
        SDL_Color bgColor;
    public:
        GridCell(SDL_Color bgColor = {255, 255, 255, 255});
        void setColor(SDL_Color color);
        void render(SDL_Renderer* renderer, int x, int y, int w, int h);
        void scaleBgColor(double scale);
};

class Grid {
    private:
        SDL_Renderer* renderer;
        int x;
        int y;
        int cellW;
        int cellH;
        std::vector<std::vector<GridCell>> cells;
    public:
        Grid(SDL_Renderer* renderer, int x, int y, int rows, int cols, int cellW, int cellH);
        GridCell& getCell(int row, int col);
        void render();
};