#ifndef FILEIO_H
#define FILEIO_H
#include <stdio.h>
#include "types.h"
#include "vector.h"

/**
 * Runs the program in main.c
 * @return this procedure does not return anything
*/
void runPaint();

/**
 * Reads a .ppm file.
 * @param image pointer of the PPMfile struct
 * @param stream stream channel for input/output
 * @return returns a boolean to signal if the procedure worked or not
*/
boolean readPPM(PPMfile *image, FILE *stream);

/**
 * Saves a .ppm file.
 * @param image PPMfile struct
 * @param stream stream channel for input/output
 * @return this procedure does not return anything
*/
void savePPM(PPMfile image, FILE *stream);

/**
 * Prints all the information of a PPMfile
 * for debugging purposes.
 * @param input PPMfile to be printed
 * @return this procedure does not return anything
*/
void printPPMfile(PPMfile input);

#endif