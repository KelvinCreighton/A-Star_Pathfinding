#include <stdio.h>
#include <stdlib.h>
#include "map.h"

int Fcost(int startNode[2], int endNode[2], int currentNode[2]) {
    return Gcost(startNode, currentNode) + Hcost(endNode, currentNode);
}

int Gcost(int startNode[2], int currentNode[2]) {
    int dy = startNode[0]-currentNode[0];
    int dx = startNode[1]-currentNode[1];
    return dx*dx + dy*dy;
}

int Hcost(int endNode[2], int currentNode[2]) {
    int dy = endNode[0]-currentNode[0];
    int dx = endNode[1]-currentNode[1];
    return dx*dx + dy*dy;
}

void findNeighbours(int **grid, int rows, int cols, int currentNode[2]) {
    int bestNeighbour[2];

    for (int y = -1; y < 3; y++) {
        for (int x = -1; x < 3; x++) {
            // Skip the index of the current node
            if (x == 0 && y == 0)
                continue;
            // Skip any out of bounds nodes
            else if (currentNode[0]+y < 0 || currentNode[1]+x < 0 || currentNode[0]+y > rows || currentNode[1]+x > cols)
                continue;
            // Skip any that are walls
            else if (grid[y][x] == -4)
                continue;
            

        }
    }
}

int main(/*int argc, char *argv[]*/) {
    // Add argv[2] for the user to request a specific maps csv file name (default will be maps.csv)
    // if (argc != 2) {
    //     printf("Usage: %s <Map Number>\n", argv[0]);
    //     return 1;
    // }
    // int mapNumber = atoi(argv[1]);
    int mapNumber = 0;

    int **grid = NULL;
    int startNode[2];   // A node position
    int endNode[2];     // B node position
    int rows, cols;

    loadMap("maps.csv", &grid, &rows, &cols, startNode, endNode, mapNumber);
    printGrid(grid, rows, cols);

    freeGrid(&grid, rows);
    return 0;
}
