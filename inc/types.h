#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int red, green, blue;
} Pixel;

typedef struct {
    int abscissa;
    int ordinate;
} Point;

typedef struct {
    int sides;
    Point *vertex;
} Polygon;

typedef struct {
    char format[2];
    int width, height;
    int max;
    Pixel **matrix;
} PPMfile;

typedef enum {
    false, true
} boolean;

#endif