#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map.h"

int Gcost(int startNode[2], int currentNode[2]) {
    // This is only an estimate gcost calculated by finding the distance
    // replace this with a real gcost by summing the path through each node
    int dy = startNode[0]-currentNode[0];
    int dx = startNode[1]-currentNode[1];
    return dx*dx + dy*dy;
}

int Hcost(int endNode[2], int currentNode[2]) {
    int dy = endNode[0]-currentNode[0];
    int dx = endNode[1]-currentNode[1];
    return dx*dx + dy*dy;
}

int Fcost(int startNode[2], int endNode[2], int currentNode[2]) {
    return Gcost(startNode, currentNode) + Hcost(endNode, currentNode);
}

int findNeighbours(int ***grid, int rows, int cols, int startNode[2], int endNode[2], int currentNode[2]) {
    for (int y = -1; y < 2; y++) {
        for (int x = -1; x < 2; x++) {
            int neighbourNode[2];
            neighbourNode[0] = currentNode[0]+y;
            neighbourNode[1] = currentNode[1]+x;

            // Skip the index of the current node
            if (x == 0 && y == 0)
                continue;
            // Skip any out of bounds nodes
            else if (neighbourNode[0] < 0 || neighbourNode[1] < 0 || neighbourNode[0] > rows || neighbourNode[1] > cols)
                continue;
            // Break if the end was found
            else if ((*grid)[neighbourNode[0]][neighbourNode[1]] == -2)
                return 1;
            // Skip any that are objects or taken cells
            else if ((*grid)[neighbourNode[0]][neighbourNode[1]] < 0)
                continue;
            
            int fcost = Fcost(startNode, endNode, neighbourNode);
            fcost += 4; // Account for the other object types that take up numbers 0 to -3 (negative values past these are considered "taken" cells)
            (*grid)[neighbourNode[0]][neighbourNode[1]] = fcost;
        }
    }
    return 0;
}

int *takeLowest(int ***grid, int rows, int cols) {
    int lowest = -1;
    int *lowestPos = (int *)malloc(2 * sizeof(int));
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if ((*grid)[y][x] <= 0)
                continue;
            if ((*grid)[y][x] < lowest || lowest == -1) {
                lowest = (*grid)[y][x];
                lowestPos[0] = y;
                lowestPos[1] = x;
            }
        }
    }
    (*grid)[lowestPos[0]][lowestPos[1]] *= -1;  // Mark as taken
    return lowestPos;
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
    int rows, cols;
    int startNode[2];   // A node position
    int endNode[2];     // B node position
    int *currentNode = (int *)malloc(2 * sizeof(int));   // Current node position

    loadMap("maps.csv", &grid, &rows, &cols, startNode, endNode, mapNumber);
    printGrid(grid, rows, cols);

    currentNode[0] = startNode[0];
    currentNode[1] = startNode[1];

    struct timespec delay;
    delay.tv_sec = 0;
    delay.tv_nsec = 200 * 1000000;

    int counter = 0;
    int maxCount = rows*cols;
    while (counter < maxCount) {
        printf("\n");
        int foundEnd = findNeighbours(&grid, rows, cols, startNode, endNode, currentNode);
        if (foundEnd)
            break;
        currentNode = takeLowest(&grid, rows, cols);
        printGrid(grid, rows, cols);

        nanosleep(&delay, NULL);
        counter++;
    }

    freeGrid(&grid, rows);
    return 0;
}
