#include <math.h>
#include <stdlib.h>
#include "../inc/vector.h"
#include "../inc/types.h"

float inclination(float startX, float startY, float endX, float endY) {
    if ((startX == endX) || (startY == endY)) {
        return 0;
    }
    return (endY - startY)/(endX - startX);
}

float distance(Point start, Point end) {
    return sqrt(pow((start.abscissa - end.abscissa), 2) + pow((start.ordinate - start.ordinate), 2));
}

void createMatrix(PPMfile *image) {
    int i, j;
    image->matrix = calloc(image->height, sizeof(Pixel*));
    for (i = 0; i < image->height; i++) {
        image->matrix[i] = calloc(image->width, sizeof(Pixel));
        for (j = 0; j < image->width; j++) {
            image->matrix[i][j].red = image->max;
            image->matrix[i][j].green = image->max;
            image->matrix[i][j].blue = image->max;
        }
    }
}

void stretchMatrix(PPMfile *image, int newRows, int newColumns) {
    int i, j;
    for (i = image->height - 1; i >= newRows; i--) {
        free(image->matrix[i]);
    }
    image->matrix = realloc(image->matrix, newRows * sizeof(Pixel*));
    for (i = 0; i < newRows; i++) {
        if (i < image->height) {
            image->matrix[i] = realloc(image->matrix[i], newColumns * sizeof(Pixel));
        } else {
            image->matrix[i] = malloc(newColumns * sizeof(Pixel));
        }
    }
    for (i = image->height; i < newRows; i++) {
        for (j = 0; j < newColumns; j++) {
            image->matrix[i][j].red = image->max;
            image->matrix[i][j].green = image->max;
            image->matrix[i][j].blue = image->max;
        }
    }
    for (i = 0; i < newRows; i++) {
        for (j = image->width; j < newColumns; j++) {
            image->matrix[i][j].red = image->max;
            image->matrix[i][j].green = image->max;
            image->matrix[i][j].blue = image->max;
        }
    }
    image->height = newRows;
    image->width = newColumns;
}

void destroyMatrix(PPMfile *image) {
    int i;
    for (i = 0; i < image->height; i++) {
        free(image->matrix[i]);
    }
    free(image->matrix);
}