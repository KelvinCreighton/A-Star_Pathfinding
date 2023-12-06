#include <stdio.h>

// const int A_X = 3;
// const int A_Y = 2;
// const int B_X = 13;
// const int B_Y = 14;
// const int WALL_X = 8;
// const int WALL_Y = 8;

void drawGrid(int grid_w, int grid_h, int grid[grid_w][grid_h]) {
    for (int y = 0; y < grid_w; y++) {
        for (int x = 0; x < grid_h; x++) {
            if (grid[x][y] == 1)
                printf("A ");
            else if (grid[x][y] == 2)
                printf("B ");
            else if (grid[x][y] == 3)
                printf("O ");
            else
                printf("# ");
        }
        printf("\n");
    }
}

int main() {
    const int GRID_WIDTH = 15;
    const int GRID_HEIGHT = 15;
    int grid[GRID_WIDTH][GRID_HEIGHT];

    for (int y = 0; y < GRID_HEIGHT; y++)
        for (int x = 0; x < GRID_WIDTH; x++)
            grid[x][y] = 0;
    grid[3][2] = 1;
    grid[14][11] = 2;
    for (int x = 3; x < 9; x++)
        grid[x][8] = 3;
    for (int y = 0; y < 8; y++)
        grid[8][y] = 3;


    drawGrid(GRID_WIDTH, GRID_HEIGHT, grid);

    return 0;
}
