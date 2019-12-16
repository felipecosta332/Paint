#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/fileio.h"
#include "../inc/draw.h"
#include "../inc/types.h"
#include "../inc/vector.h"
#include "../inc/text.h"

void runPaint() {
    PPMfile image;
    Pixel color = {0, 0, 0};
    Point point = {0, 0};
    Polygon polygon;
    polygon.vertex = malloc(1);
    boolean opened = false, terminal = false;
    int X, Y, degree, ratio;
    int height = 0, width = 0, max = 255, radius = 0, thickness = 1;
    int red = 255, green = 255, blue = 255;
    float distance, *coefficient, a, b, c, d;
    char axis = 'a', input[100], string[3], *command;
    unsigned long x;
    FILE *file = fopen("../files/input.txt", "r");
    while (true) {
        fscanf(file, "%s", input);
        if (!strcmp(input, "terminal")) {
            if (!terminal) {
                fclose(file);
            }
            file = stdin;
            terminal = true;
        } else if (!strcmp(input, "image")) {
            if (opened) {
                destroyMatrix(&image);
            }
            fscanf(file, "%d %d %d", &height, &width, &max);
            createPPM(&image, height, width, max);
            opened = true;
        } else if (!strcmp(input, "resize") && opened) {
            fscanf(file, "%d %d", &height, &width);
            stretchMatrix(&image, height, width);
        } else if (!strcmp(input, "color") && opened) {
            fscanf(file, "%d %d %d", &color.red, &color.green, &color.blue);
            if (color.red < 0) {
                color.red = 0;
            } else if (color.red > image.max) {
                color.red = image.max;
            }
            if (color.green < 0) {
                color.green = 0;
            } else if (color.green > image.max) {
                color.green = image.max;
            }
            if (color.blue < 0) {
                color.blue = 0;
            } else if (color.blue > image.max) {
                color.blue = image.max;
            }
        } else if (!strcmp(input, "gray") && opened) {
            grayScaleFilter(&image);
        } else if (!strcmp(input, "thickness") && opened) {
            fscanf(file, "%d", &thickness);
        } else if (!strcmp(input, "clear") && opened) {
            clear(&image, color);
        } else if (!strcmp(input, "line") && opened) {
            free(polygon.vertex);
            polygon.sides = 2;
            polygon.vertex = calloc(polygon.sides, sizeof(Point));
            for (int i = 0; i < polygon.sides; i++) {
                fscanf(file, "%d %d", &polygon.vertex[i].abscissa, &polygon.vertex[i].ordinate);
            }
            drawLine(&image, color, polygon.vertex[0], polygon.vertex[1], thickness);
        } else if (!strcmp(input, "rect") && opened) {
            fscanf(file, "%d %d %d %d", &point.abscissa, &point.ordinate, &height, &width);
            drawRectangle(&image, color, point, height, width, thickness);
        } else if (!strcmp(input, "circle") && opened) {
            fscanf(file, "%d %d %d", &point.abscissa, &point.ordinate, &radius);
            drawCircle(&image, color, point, radius, thickness);
        } else if (!strcmp(input, "disk") && opened) {
            fscanf(file, "%d %d %d", &point.abscissa, &point.ordinate, &radius);
            drawDisk(&image, color, point, radius);
        } else if (!strcmp(input, "parabola") && opened) {
            fscanf(file, "%c %c %d %d %f", &axis, &axis, &point.abscissa, &point.ordinate, &distance);
            drawParabola(&image, color, thickness, axis, point, distance);
        } else if (!strcmp(input, "ellipse") && opened) {
            fscanf(file, "%c %c %d %d %f %f", &axis, &axis, &point.abscissa, &point.ordinate, &a, &b);
            drawEllipse(&image, color, thickness, axis, point, a, b);
        } else if (!strcmp(input, "hyperbola") && opened) {
            fscanf(file, "%c %c %d %d %f %f", &axis, &axis, &point.abscissa, &point.ordinate, &c, &a);
            drawHyperbola(&image, color, thickness, axis, point, c, a);
        } else if (!strcmp(input, "graph") && opened) {
            plotCartesian(&image, color, thickness);
        } else if (!strcmp(input, "function") && opened) {
            fscanf(file, "%d", &degree);
            if (degree >= 0) {
                coefficient = calloc((degree + 1), sizeof(float));
                for (int i = 0; i < (degree + 1); i++) {
                    fscanf(file, "%f", &coefficient[i]);
                }
                plotFunction(&image, color, thickness, degree, coefficient);
                free(coefficient);
            }
        } else if (!strcmp(input, "trig") && opened) {
            fscanf(file, "%s %f %f %f %f", string, &a, &b, &c, &d);
            if (!strcmp(string, "sin")) {
                ratio = 0;
            } else if (!strcmp(string, "cos")) {
                ratio = 1;
            } else if (!strcmp(string, "tan")) {
                ratio = 2;
            } else if (!strcmp(string, "csc")) {
                ratio = 3;
            } else if (!strcmp(string, "sec")) {
                ratio = 4;
            } else if (!strcmp(string, "ctg")) {
                ratio = 5;
            } else {
                continue;
            }
            plotTrigonometric(&image, color, thickness, ratio, a, b, c, d);
        } else if (!strcmp(input, "polygon") && opened) {
            free(polygon.vertex);
            fscanf(file, "%d", &polygon.sides);
            polygon.vertex = calloc(polygon.sides, sizeof(Point));
            for (int i = 0; i < polygon.sides; i++) {
                fscanf(file, "%d %d", &polygon.vertex[i].abscissa, &polygon.vertex[i].ordinate);
            }
            drawPolygon(&image, color, polygon, thickness);
        } else if (!strcmp(input, "fill") && opened) {
            fscanf(file, "%d %d", &X, &Y);
            fillColor(&image, color, image.matrix[Y][X], X, Y);
        } else if (!strcmp(input, "save") && opened) {
            savePPM(image, file);
        } else if (!strcmp(input, "open")) {
            if (opened) {
                destroyMatrix(&image);
            }
            opened = readPPM(&image, file);
            printf("%d\n", opened);
        } else if (!strcmp(input, "view")) {
            strcpy(input, "eog ../files/");
            getline(&command, &x, file);
            cleanString(command);
            strcat(input, command);
            system(input);
        } else if (!strcmp(input, "end")) {
            if (!terminal) {
                fclose(file);
            }
            if (opened) {
                destroyMatrix(&image);
                free(polygon.vertex);
            }
            break;
        }
    }
}

boolean readPPM(PPMfile *image, FILE *stream) {
    char *filepath = NULL;
    unsigned long x;
    getline(&filepath, &x, stream);
    cleanString(filepath);
    FILE *file = fopen(insertString(filepath, "../files/"), "r");
    if (file == NULL) {
        printf("Something went wrong. Please, make sure the file path is correct.\n");
        return false;
    } else {
        fgets(image->format, 3, file);
        fscanf(file, "%d %d %d", &image->width, &image->height, &image->max);
        createMatrix(image);
        for (int i = 0; i < image->height; i++) {
            for (int j = 0; j < image->width; j++) {
                fscanf(file, "%d", &image->matrix[i][j].red);
                fscanf(file, "%d", &image->matrix[i][j].green);
                fscanf(file, "%d", &image->matrix[i][j].blue);
            }
        }
        fclose(file);
        return true;
    }
}

void savePPM(PPMfile image, FILE *stream) {
    char *filename = NULL;
    unsigned long x;
    getline(&filename, &x, stream);
    cleanString(filename);
    FILE *file = fopen(insertString(filename, "../files/"), "w");
    fprintf(file, "%s\n%d %d\n%d\n", image.format, image.width, image.height, image.max);
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            fprintf(file, "%d ", image.matrix[i][j].red);
            fprintf(file, "%d ", image.matrix[i][j].green);
            fprintf(file, "%d\n", image.matrix[i][j].blue);
        }
    }
    fclose(file);
}

void printPPMfile(PPMfile input) {
	printf("FORMATO: %s\n", input.format);
	printf("LARGURA: %d\n", input.width);
	printf("ALTURA: %d\n", input.height);
	printf("MÁXIMO: %d\n", input.max);
	for (int i = 0; i < input.height; i++) {
		for (int j = 0; j < input.width; j++) {
			printf("%d ", input.matrix[i][j].red);
			printf("%d ", input.matrix[i][j].green);
			printf("%d\n", input.matrix[i][j].blue);
		}
	}
}