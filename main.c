#include <stdio.h>
#include "map.h"

int main(int argc, char *argv[]) {
    // Add argv[2] for the user to request a specific maps csv file name (default will be maps.csv)
    // if (argc != 2) {
    //     printf("Usage: %s <Map Number>\n", argv[0]);
    //     return 1;
    // }
    // int mapNumber = atoi(argv[1]);
    int mapNumber = 0;

    int **grid = NULL;
    int rows, cols;

    loadMap("maps.csv", &grid, &rows, &cols, mapNumber);
    printGrid(grid, rows, cols);
    freeGrid(&grid, rows);

    printf("\n\n");
    return 0;
}
