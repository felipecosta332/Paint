#ifndef VECTOR_H
#define VECTOR_H
#include "types.h"

/**
 * Calculates the inclination of a line
 * @param startX starting point abscissa
 * @param startY starting point ordinate
 * @param endX ending point abscissa
 * @param endY ending point ordinate
 * @return returns the inclination of a line
*/
float inclination(float startX, float startY, float endX, float endY);

/**
 * Calculates the distance between two points
 * @param start starting point
 * @param end ending point
 * @return returns the distance between two points
*/
float distance(Point start, Point end);

/**
 * this function allocates a new matrix of pixels dynamically
 * the new pixels in the matrix are set as a gray scale color
 * (rgb: (max, max, max))
 * @param image pointer to the ppmfile struct
 * @return this procedure does not return anything
*/
void createMatrix(PPMfile *image);

/**
 * this function scales the size of a matrix, increasing or decreasing its dimensions
 * it inputs a ppmfile struct
 * the dimensions of the reallocated matrix are newRows and newColumns
 * the new pixels in the reallocated matrix are set as white (rgb: (255, 255, 255))
 * @param image pointer to the ppmfile struct
 * @param newRows number of rows of the new matrix
 * @param newColumns number of columns of the new matrix
 * @return this procedure does not return anything
*/
void stretchMatrix(PPMfile *image, int newRows, int newColumns);

/**
 * this procedure deallocates a matrix dynamically
 * it takes the rows of the matrix and its pointer as arguments
 * @param image pointer to the ppmfile struct
 * @return this procedure does not return anything
*/
void destroyMatrix(PPMfile *image);

#endif