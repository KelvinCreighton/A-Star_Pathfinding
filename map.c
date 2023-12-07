#include "map.h"
#include <stdio.h>
#include <stdlib.h>

void loadMap(const char *filename, int ***grid, int *rows, int *cols, int mapNumber) {
    // Grid values: 0 = #, 1 = A, 2 = B, 3 = O

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }

    int mapNumberCounter = mapNumber;
    while (mapNumberCounter > 0) {
        char c;
        fscanf(file, "%c", &c);
        if (feof(file)) {
            printf("Error no map %d found\n", mapNumber);
            fclose(file);
            return;
        } else if (c == ';') {
            mapNumberCounter--;
        }
    }


    // Read the size of the grid
    if (fscanf(file, "%d,%d,", rows, cols) != 2) {
        printf("Error reading grid size from file %s\n", filename);
        fclose(file);
        return;
    }

    // Allocate memory for the grid and initialize all values of the grid as blank (#)
    *grid = (int **)malloc(*rows * sizeof(int *));
    for (int y = 0; y < *rows; y++) {
        (*grid)[y] = (int *)malloc(*cols * sizeof(int));
        for (int x = 0; x < *cols; x++)
            (*grid)[y][x] = 0;
    }

    // Read the A and B positions of the grid
    int ax, ay, bx, by;
    if (fscanf(file, "%d,%d,", &ax, &ay) != 2 || fscanf(file, "%d,%d,", &bx, &by) != 2) {
        printf("Error reading A and B positions from file %s\n", filename);
        fclose(file);
        return;
    }
    (*grid)[ay][ax] = 1;
    (*grid)[by][bx] = 2;

    // Read the rest of the entries before the first empty line '\n' as wall values
    while (1) {
        int x1, y1, x2, y2;
        if (fscanf(file, "%d,%d,%d,%d,", &x1, &y1, &x2, &y2) != 4)
            break;
        
        for (int y = y1; y <= y2; y++)
            for (int x = x1; x <= x2; x++)
                (*grid)[y][x] = 3;
    }

    fclose(file);
}

void freeGrid(int ***grid, int rows) {
    for (int i = 0; i < rows; i++) {
        free((*grid)[i]);
    }
    free(*grid);
    *grid = NULL;
}

void printGrid(int **grid, int rows, int cols) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (grid[y][x] == 1)
                printf("A ");
            else if (grid[y][x] == 2)
                printf("B ");
            else if (grid[y][x] == 3)
                printf("O ");
            else
                printf("# ");
        }
        printf("\n");
    }
}