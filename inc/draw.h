#ifndef DRAW_H
#define DRAW_H
#include "types.h"

/**
 * Takes the pointer of a PPMfile struct and initializes it
 * with the input parameters as the new values of the struct.
 * A new matrix is allocated to the struct with height X width dimensions.
 * @param image pointer of the PPMfile struct
 * @param height height dimension of the PPMfile struct matrix
 * @param width width dimension of the PPMfile struct matrix
 * @param max maximum value of the components of the pixels
 * @return this procedure does not return anything
 */
void createPPM(PPMfile *image, int height, int width, int max);

/**
 * Takes the pointer of a PPMfile struct and
 * sets every pixel in the matrix as the input pixel.
 * @param image pointer of the PPMfile struct
 * @param color input color pixel used to paint all the matrix
 * @return this procedure does not return anything
 */
void clear(PPMfile *image, Pixel color);

/**
 * Draws a line from the start point to the end point.
 * If thickness is greater than 1 then it draws a thick line
 * according to the value of thickness.
 * The color of the line is the color input parameter.
 * @param image pointer of the PPMfile struct
 * @param color color of the line
 * @param start the starting point
 * @param end the ending point
 * @param thickness thickness of the line
 * @return this procedure does not return anything
 */
void drawLine(PPMfile *image, Pixel color, Point start, Point end, int thickness);

/**
 * Draws a polygon in the image. It draws a line between 
 * each consecutive point in the array and between the 
 * first and last point of the array of the polygon struct.
 * @param image pointer of the PPMfile struct
 * @param color color of the polygon borders
 * @param polygon struct with the total sides and an array of points
 * @param thickness thickness of the border
 * @return this procedure does not return anything
 */
void drawPolygon(PPMfile *image, Pixel color, Polygon polygon, int thickness);

/**
 * Draws a rectangle in the pixel
 * matrix of the PPMfile struct.
 * @param image pointer of the PPMfile struct
 * @param color color of the rectangle borders
 * @param upperLeftCorner the upper left point struct
 * @param height the height measure of the rectangle
 * @param width the width measure of the rectangle
 * @param thickness the thickness of the border
 * @return this procedure does not return anything
 */
void drawRectangle(PPMfile *image, Pixel color, Point upperLeftCorner, int height, int width, int thickness);

/**
 * Draws a circle in the pixel matrix of the PPMfile struct    
 * @param image pointer of the PPMfile struct
 * @param color color of the circle border
 * @param center point struct with coordinates of the center
 * @param radius distance between each point in the circle and the center
 * @param thickness thickness measure of the border
 * @return this procedure does not return anything
 */
void drawCircle(PPMfile *image, Pixel color, Point center, int radius, int thickness);

/**
 * Draws a disk in the pixel matrix of the PPMfile struct    
 * @param image pointer of the PPMfile struct
 * @param color color of the disk
 * @param center point struct with coordinates of the center
 * @param radius distance between each point in the circle and the center
 * @return this procedure does not return anything
 */
void drawDisk(PPMfile *image, Pixel color, Point center, int radius);

/**
 * Paints a set of adjacent points
 * in the matrix of the PPMfile struct.
 * @param image pointer of the PPMfile struct
 * @param sourceColor the color used to paint
 * @param targetColor the color to be painted
 * @param abscissa the column of the first Pixel
 * @param ordinate the row of the first Pixel
 * @return this procedure does not return anything
 */
void fillColor(PPMfile *image, Pixel sourceColor, Pixel targetColor, int abscissa, int ordinate);

/**
 * Draws a cartesian coordinate system
 * @param image pointer of the PPMfile struct
 * @param color the color of the axis
 * @param thickness the thickness of the axis
 * @return this procedure does not return anything
*/
void plotCartesian(PPMfile *image, Pixel color, int thickness);

/**
 * Plots the graph of a polynomial function
 * @param image pointer of the PPMfile struct
 * @param color color of the graph
 * @param thickness thickness of the graph
 * @param degree degree of the function
 * @param coefficient array of the coefficients
 * @return this procedure does not return anything
*/
void plotFunction(PPMfile *image, Pixel color, int thickness, int degree, float *coefficient);

/**
 * Plots the graph of a trigonometric function
 * @param image pointer of the PPMfile struct
 * @param color color of the graph
 * @param thickness thickness of the graph
 * @param ratio number to identify which trigonometric function
 * @param a multiplies the trigonometric function
 * @param b multiplies the angle
 * @param c adds to the angle inside the function
 * @param d adds to the whole expression
 * @return this procedure does not return anything
*/
void plotTrigonometric(PPMfile *image, Pixel color, int thickness, int ratio, float a, float b, float c, float d);

/**
 * Draws a vertical or horizontal parabola
 * @param image pointer of the PPMfile struct
 * @param color color of the parabola
 * @param thickness thickness of the parabola
 * @param axis vertical or horizontal axis of the parabola
 * @param vertex vertex point of the parabola
 * @param distance distance between the focus and the vertex
 * @return this procedure does not return anything
*/
void drawParabola(PPMfile *image, Pixel color, int thickness, char axis, Point vertex, float distance);

/**
 * Draws a vertical or horizontal ellipse
 * @param image pointer of the PPMfile struct
 * @param color color of the ellipse
 * @param thickness thickness of the border
 * @param axis vertical or horizontal axis of the ellipse
 * @param center central point of the ellipse
 * @param a larger axle size
 * @param b smaller axle size
 * @return this procedure does not return anything
*/
void drawEllipse(PPMfile *image, Pixel color, int thickness, char axis, Point center, float a, float b);

/**
 * Draws a hyperbola
 * @param image pointer of the PPMfile struct
 * @param color color of the hyperbola
 * @param thickness thickness of the hyperbola
 * @param axis vertical or horizontal axis of the hyperbola
 * @param center center point of the hyperbola
 * @param c distance between the center and the focus
 * @param a distance between the center and the vertex
 * @return this procedure does not return anything
*/
void drawHyperbola(PPMfile *image, Pixel color, int thickness, char axis, Point center, float c, float a);

/**
 * Sets all pixels in the matrix to a gray scale
 * @param image
 * @return this procedure does not return anything
*/
void grayScaleFilter(PPMfile *image);

#endif