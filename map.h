#ifndef MAP_H
#define MAP_H

void loadMap(const char *filename, int ***grid, int *rows, int *cols, int startNode[2], int endNode[2], int mapNumber);
void freeGrid(int ***grid, int rows);
void printGrid(int **grid, int rows, int cols);

#endif