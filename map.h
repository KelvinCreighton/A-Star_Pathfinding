#ifndef MAP_H
#define MAP_H

void loadMap(const char *filename, int ***grid, int *rows, int *cols, int mapNumber);
void freeGrid(int ***grid, int rows);
void printGrid(int **grid, int rows, int cols);

#endif