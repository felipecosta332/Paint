#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../inc/draw.h"
#include "../inc/vector.h"
#include "../inc/types.h"

void createPPM(PPMfile *image, int height, int width, int max) {
    strcpy(image->format, "P3");
    if (width < 0) {
        image->width = 0;
    } else {
        image->width = width;
    }
    if (height < 0) {
        image->height = 0;
    } else {
        image->height = height;
    }
    if (max < 0) {
        image->max = 0;
    } else {
        image->max = max;
    }
    createMatrix(image);
}

void clear(PPMfile *image, Pixel color) {
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            image->matrix[i][j].red = color.red;
            image->matrix[i][j].green = color.green;
            image->matrix[i][j].blue = color.blue;
        }
    }
}

void drawLine(PPMfile *image, Pixel color, Point start, Point end, int thickness) {
    int abscissa, ordinate, aux;
    int initX = start.abscissa;
    int initY = start.ordinate;
    int finalX = end.abscissa;
    int finalY = end.ordinate;
    float delta = inclination(initX, initY, finalX, finalY);
    if (delta <= 1 && delta >= -1 && delta != 0) {
        if (initX > finalX) {
            aux = initX;
            initX = finalX;
            finalX = aux;
            aux = initY;
            initY = finalY;
            finalY = aux;
        }
        for (int i = 0; initX + i <= finalX; i++) {
            abscissa = initX + i;
            ordinate = initY + round(delta * i);
            if (abscissa >= 0 && abscissa < image->width) {
                if (ordinate >= 0 && ordinate < image->height) {
                    image->matrix[ordinate][abscissa] = color;
                }
                if (thickness > 1) {
                    for (int j = 1; j < thickness; j++) {
                        if ((delta > 0 && delta < 1) || (delta > -1 && delta < 0)) {
                            if (ordinate + j >= 0 && ordinate + j < image->height) {
                                image->matrix[ordinate + j][abscissa] = color;
                            }
                            if (ordinate - j >= 0 && ordinate - j < image->height) {
                                image->matrix[ordinate - j][abscissa] = color;
                            }
                        }
                        if (delta == 1 || delta == -1) {
                            if (ordinate + j >= 0 && ordinate + j < image->height) {
                                image->matrix[ordinate + j][abscissa] = color;
                            }
                            if (ordinate - j >= 0 && ordinate - j < image->height) {
                                image->matrix[ordinate - j][abscissa] = color;
                            }
                            if (abscissa + j >= 0 && abscissa + j < image->width) {
                                image->matrix[ordinate][abscissa + j] = color;
                            }
                            if (abscissa - j >= 0 && abscissa - j < image->width) {
                                image->matrix[ordinate][abscissa - j] = color;
                            }  
                        }
                    }
                }
            }
        }
    } else if (delta > 1 || delta < -1) {
        if (initY > finalY) {
            aux = initY;
            initY = finalY;
            finalY = aux;
            aux = initX;
            initX = finalX;
            finalX = aux;
        }
        for (int i = 0; initY + i <= finalY; i++) {
            abscissa = initX + round((1/delta) * i);
            ordinate = initY + i;
            if (ordinate >= 0 && ordinate < image->height) {
                if (abscissa >= 0 && abscissa < image->width) {
                    image->matrix[ordinate][abscissa] = color;
                }
                if (thickness > 1) {
                    for (int j = 1; j < thickness; j++) {
                        if (abscissa + j >= 0 && abscissa + j < image->width) {
                            image->matrix[ordinate][abscissa + j] = color;
                        }
                        if (abscissa - j >= 0 && abscissa - j < image->width) {
                            image->matrix[ordinate][abscissa - j] = color;
                        }
                    }
                }
            }
        }
    } else {
        if (initX == finalX && initX >= 0 && initX < image->width) {
            if (initY > finalY) {
                aux = initY;
                initY = finalY;
                finalY = aux;
            }
            for (int i = 0; initY + i <= finalY; i++) {
                abscissa = initX;
                ordinate = initY + i;
                if (ordinate >= 0 && ordinate < image->height) {
                    image->matrix[ordinate][abscissa] = color;
                    if (thickness > 1) {
                        for (int j = 1; j < thickness; j++) {
                            if (abscissa + j >= 0 && abscissa + j < image->width) {
                                image->matrix[ordinate][abscissa + j] = color;
                            }
                            if (abscissa - j >= 0 && abscissa - j < image->width) {
                                image->matrix[ordinate][abscissa - j] = color;
                            }
                        }
                    }
                }
            }
        }
        if (initY == finalY && initY >= 0 && initY < image->height) {
            if (initX > finalX) {
                aux = initX;
                initX = finalX;
                finalX = aux;
            }
            for (int i = 0; initX + i <= finalX; i++) {
                abscissa = initX + i;
                ordinate = initY;
                if (abscissa >= 0 && abscissa < image->width) {
                    image->matrix[ordinate][abscissa] = color;
                    if (thickness > 1) {
                        for (int j = 1; j < thickness; j++) {
                            if (ordinate + j >= 0 && ordinate + j < image->height) {
                                image->matrix[ordinate + j][abscissa] = color;
                            }
                            if (ordinate - j >= 0 && ordinate - j < image->height) {
                                image->matrix[ordinate - j][abscissa] = color;
                            }
                        }
                    }
                }
            }
        }
    }
}

void drawPolygon(PPMfile *image, Pixel color, Polygon polygon, int thickness) {
    for (int i = 0; i < polygon.sides; i++) {
        if (i == polygon.sides - 1) {
            drawLine(image, color, polygon.vertex[i], polygon.vertex[0], thickness);
        } else {
            drawLine(image, color, polygon.vertex[i], polygon.vertex[i + 1], thickness);
        }
        drawDisk(image, color, polygon.vertex[i], (int)(thickness*0.9));
    }
}

void drawRectangle(PPMfile *image, Pixel color, Point upperLeftCorner, int height, int width, int thickness) {
    Point upperRightCorner = {upperLeftCorner.abscissa + width, upperLeftCorner.ordinate};
    Point lowerLeftCorner = {upperLeftCorner.abscissa, upperLeftCorner.ordinate + height};
    Point lowerRightCorner = {upperLeftCorner.abscissa + width, upperLeftCorner.ordinate + height};
    drawLine(image, color, upperLeftCorner, upperRightCorner, thickness);
    drawLine(image, color, upperLeftCorner, lowerLeftCorner, thickness);
    drawLine(image, color, lowerLeftCorner, lowerRightCorner, thickness);
    drawLine(image, color, upperRightCorner, lowerRightCorner, thickness);
    drawDisk(image, color, upperLeftCorner, (int)(thickness*0.9));
    drawDisk(image, color, upperRightCorner, (int)(thickness*0.9));
    drawDisk(image, color, lowerLeftCorner, (int)(thickness*0.9));
    drawDisk(image, color, lowerRightCorner, (int)(thickness*0.9));
}

void drawCircle(PPMfile *image, Pixel color, Point center, int radius, int thickness) {
    double angle;
    int abscissa, upperOrdinate, lowerOrdinate, delta, j;
    int auxAbscissa, auxUpperOrdinate, auxLowerOrdinate;
    j = 0;
    for (int i = (center.abscissa - radius); i <= (center.abscissa + radius); i++) {
        abscissa = i;
        angle = acos( ((double) (fabs(abscissa - center.abscissa) ) / radius) );
        delta = round(radius * sin(angle) );
        upperOrdinate = center.ordinate + delta;
        lowerOrdinate = center.ordinate - delta;
        if (abscissa >= 0 && abscissa < image->width) {
            if (upperOrdinate >= 0 && upperOrdinate < image->height) {
                image->matrix[upperOrdinate][abscissa] = color;
            }
            if (lowerOrdinate >= 0 && lowerOrdinate < image->height) {
                image->matrix[lowerOrdinate][abscissa] = color;
            }
        }
        if (j > 0) {
            drawLine(image, color, (Point) {auxAbscissa, auxUpperOrdinate}, (Point) {abscissa, upperOrdinate}, thickness);
            drawLine(image, color, (Point) {auxAbscissa, auxLowerOrdinate}, (Point) {abscissa, lowerOrdinate}, thickness);
        }
        auxAbscissa = abscissa;
        auxUpperOrdinate = upperOrdinate;
        auxLowerOrdinate = lowerOrdinate;
        j++;
    }
}

void drawDisk(PPMfile *image, Pixel color, Point center, int radius) {
    double angle;
    int abscissa, ordinate, upperOrdinate, lowerOrdinate;
    int auxAbscissa, auxUpperOrdinate, auxLowerOrdinate;
    int delta, j;
    for (int i = (center.abscissa - radius); i <= (center.abscissa + radius); i++) {
        abscissa = i;
        angle = acos( ((double) (fabs(abscissa - center.abscissa) ) / radius) );
        delta = fabs(round(radius * sin(angle) ) );
        upperOrdinate = center.ordinate + delta;
        lowerOrdinate = center.ordinate - delta;
        if (abscissa >= 0 && abscissa < image->width) {
            for (ordinate = lowerOrdinate; ordinate <= upperOrdinate; ordinate++) {
                if (ordinate >= 0 && ordinate < image->height) {
                    image->matrix[ordinate][abscissa] = color;
                }
            }
        }
        if (j > 0) {
            if (auxUpperOrdinate <= center.ordinate + radius 
            && upperOrdinate <= center.ordinate + radius
            && fabs(auxAbscissa - abscissa) == 1) {
                drawLine(image, color, (Point) {auxAbscissa, auxUpperOrdinate}, (Point) {abscissa, upperOrdinate}, 1);
            }
            if (auxLowerOrdinate >= center.ordinate - radius 
            && lowerOrdinate >= center.ordinate - radius
            && fabs(auxAbscissa - abscissa) == 1) {
                drawLine(image, color, (Point) {auxAbscissa, auxLowerOrdinate}, (Point) {abscissa, lowerOrdinate}, 1);
            }
        }
        auxAbscissa = abscissa;
        auxUpperOrdinate = upperOrdinate;
        auxLowerOrdinate = lowerOrdinate;
    }
}

void fillColor(PPMfile *image, Pixel sourceColor, Pixel targetColor, int abscissa, int ordinate) {
    boolean abscissaInside = (abscissa >= 0 && abscissa < image->width);
    boolean ordinateInside = (ordinate >= 0 && ordinate < image->height);
    if (abscissaInside && ordinateInside) {
        if (image->matrix[ordinate][abscissa].red == sourceColor.red
        && image->matrix[ordinate][abscissa].green == sourceColor.green
        && image->matrix[ordinate][abscissa].blue == sourceColor.blue) {
            return;
        } else if (image->matrix[ordinate][abscissa].red == targetColor.red
        && image->matrix[ordinate][abscissa].green == targetColor.green
        && image->matrix[ordinate][abscissa].blue == targetColor.blue) {
            image->matrix[ordinate][abscissa] = sourceColor;
            fillColor(image, sourceColor, targetColor, abscissa + 1, ordinate);
            fillColor(image, sourceColor, targetColor, abscissa - 1, ordinate);
            fillColor(image, sourceColor, targetColor, abscissa, ordinate + 1);
            fillColor(image, sourceColor, targetColor, abscissa, ordinate - 1);
        }
    }
}

void plotCartesian(PPMfile *image, Pixel color, int thickness) {
    Point center;
    center.abscissa = round(image->width / 2);
    center.ordinate = round(image->height / 2);
    clear(image, (Pixel) {image->max, image->max, image->max});
    drawLine(image, color, (Point) {0, center.ordinate}, (Point) {image->width - 1, center.ordinate}, thickness);
    drawLine(image, color, (Point) {center.abscissa, 0}, (Point) {center.abscissa, image->height - 1}, thickness);
}

void plotFunction(PPMfile *image, Pixel color, int thickness, int degree, float *coefficient) {
    Point center;
    center.abscissa = round(image->width / 2);
    center.ordinate = round(image->height / 2);
    int abscissa, ordinate, auxAbscissa, auxOrdinate;
    for (int i = 0; i < image->width; i++) {
        abscissa = i - center.abscissa;
        ordinate = 0;
        for (int j = 0; j <= degree; j++) {
            ordinate += round(pow(abscissa, (degree - j)) * -coefficient[j]);
        }
        ordinate += center.ordinate;
        if (ordinate >= 0 && ordinate < image->height) {
            image->matrix[ordinate][i] = color; 
        }
        if (i > 0 && ((ordinate >= 0 && ordinate < image->height) || (auxOrdinate >= 0 && auxOrdinate < image->height))) {
            drawLine(image, color, (Point) {auxAbscissa, auxOrdinate}, (Point) {i, ordinate}, thickness);
        }
        auxAbscissa = i;
        auxOrdinate = ordinate;
    }
}

void plotTrigonometric(PPMfile *image, Pixel color, int thickness, int ratio, float a, float b, float c, float d) {
    Point center;
    center.abscissa = round(image->width / 2);
    center.ordinate = round(image->height / 2);
    int abscissa, ordinate, auxAbscissa, auxOrdinate;
    for (int i = 0; i < image->width; i++) {
        abscissa = i - center.abscissa;
        switch (ratio) {
            case 0:
                ordinate = round((-a * sin(b * abscissa + c) + d));
                break;
            case 1:
                ordinate = round((-a * cos(b * abscissa + c) + d));
                break;
            case 2:
                ordinate = round((-a * tan(b * abscissa + c) + d));
                break;
            case 3:
                ordinate = round((-a * pow(sin(b * abscissa + c), -1) + d));
                break;
            case 4:
                ordinate = round((-a * pow(cos(b * abscissa + c), -1) + d));
                break;
            case 5:
                ordinate = round((-a * pow(tan(b * abscissa + c), -1) + d));
                break;
        }
        ordinate += center.ordinate;
        if (ordinate >= 0 && ordinate < image->height) {
            image->matrix[ordinate][i] = color; 
        }
        if (i > 0 && ((ordinate >= 0 && ordinate < image->height) || (auxOrdinate >= 0 && auxOrdinate < image->height))) {
            drawLine(image, color, (Point) {auxAbscissa, auxOrdinate}, (Point) {i, ordinate}, thickness);
        }
        auxAbscissa = i;
        auxOrdinate = ordinate;
    }
}

void drawParabola(PPMfile *image, Pixel color, int thickness, char axis, Point vertex, float distance) {
    int abscissa, upperAbscissa, lowerAbscissa, ordinate, upperOrdinate, lowerOrdinate, delta;
    int auxAbscissa, auxUpperAbscissa, auxLowerAbscissa, auxOrdinate, auxUpperOrdinate, auxLowerOrdinate, i;
    if (axis == 'x') {
        if (distance > 0) {
            i = 0;
            for (abscissa = vertex.abscissa; abscissa < image->width; abscissa++) {
                delta = round(sqrt(fabs(4*distance*(abscissa - vertex.abscissa))));
                upperOrdinate = vertex.ordinate + delta;
                lowerOrdinate = vertex.ordinate - delta;
                if (abscissa >= 0 && abscissa < image->width) {
                    if (upperOrdinate >= 0 && upperOrdinate < image->height) {
                        image->matrix[upperOrdinate][abscissa] = color;
                    }
                    if (lowerOrdinate >= 0 && lowerOrdinate < image->height) {
                        image->matrix[lowerOrdinate][abscissa] = color;
                    }
                }
                if (i > 0) {
                    drawLine(image, color, (Point) {auxAbscissa, auxUpperOrdinate}, (Point) {abscissa, upperOrdinate}, thickness);
                    drawLine(image, color, (Point) {auxAbscissa, auxLowerOrdinate}, (Point) {abscissa, lowerOrdinate}, thickness);
                }
                auxAbscissa = abscissa;
                auxUpperOrdinate = upperOrdinate;
                auxLowerOrdinate = lowerOrdinate;
                i++;
            }
        } else if (distance < 0) {
            i = 0;
            for (abscissa = vertex.abscissa; abscissa >= 0; abscissa--) {
                delta = round(sqrt(fabs(4*distance*(abscissa - vertex.abscissa))));
                upperOrdinate = vertex.ordinate + delta;
                lowerOrdinate = vertex.ordinate - delta;
                if (abscissa >= 0 && abscissa < image->width) {
                    if (upperOrdinate >= 0 && upperOrdinate < image->height) {
                        image->matrix[upperOrdinate][abscissa] = color;
                    }
                    if (lowerOrdinate >= 0 && lowerOrdinate < image->height) {
                        image->matrix[lowerOrdinate][abscissa] = color;
                    }
                }
                if (i > 0) {
                    drawLine(image, color, (Point) {auxAbscissa, auxUpperOrdinate}, (Point) {abscissa, upperOrdinate}, thickness);
                    drawLine(image, color, (Point) {auxAbscissa, auxLowerOrdinate}, (Point) {abscissa, lowerOrdinate}, thickness);
                }
                auxAbscissa = abscissa;
                auxUpperOrdinate = upperOrdinate;
                auxLowerOrdinate = lowerOrdinate;
                i++;
            }
        }
    } else if (axis == 'y') {
        if (distance > 0) {
            i = 0;
            for (ordinate = vertex.ordinate; ordinate >= 0; ordinate--) {
                delta = round(sqrt(fabs(4*distance*(ordinate - vertex.ordinate))));
                upperAbscissa = vertex.abscissa + delta;
                lowerAbscissa = vertex.abscissa - delta;
                if (ordinate >= 0 && ordinate < image->height) {
                    if (upperAbscissa >= 0 && upperAbscissa < image->width) {
                        image->matrix[ordinate][upperAbscissa] = color;
                    }
                    if (lowerAbscissa >= 0 && lowerAbscissa < image->width) {
                        image->matrix[ordinate][lowerAbscissa] = color;
                    }
                    if (i > 0) {
                        drawLine(image, color, (Point) {auxUpperAbscissa, auxOrdinate}, (Point) {upperAbscissa, ordinate}, thickness);
                        drawLine(image, color, (Point) {auxLowerAbscissa, auxOrdinate}, (Point) {lowerAbscissa, ordinate}, thickness);
                    }
                }
                auxOrdinate = ordinate;
                auxUpperAbscissa = upperAbscissa;
                auxLowerAbscissa = lowerAbscissa;
                i++;
            }
        } else if (distance < 0) {
            i = 0;
            for (ordinate = vertex.ordinate; ordinate < image->height; ordinate++) {
                delta = round(sqrt(fabs(4*distance*(ordinate - vertex.ordinate))));
                upperAbscissa = vertex.abscissa + delta;
                lowerAbscissa = vertex.abscissa - delta;
                if (ordinate >= 0 && ordinate < image->height) {
                    if (upperAbscissa >= 0 && upperAbscissa < image->width) {
                        image->matrix[ordinate][upperAbscissa] = color;
                    }
                    if (lowerAbscissa >= 0 && lowerAbscissa < image->width) {
                        image->matrix[ordinate][lowerAbscissa] = color;
                    }
                }
                if (i > 0) {
                    drawLine(image, color, (Point) {auxUpperAbscissa, auxOrdinate}, (Point) {upperAbscissa, ordinate}, thickness);
                    drawLine(image, color, (Point) {auxLowerAbscissa, auxOrdinate}, (Point) {lowerAbscissa, ordinate}, thickness);
                }
                auxOrdinate = ordinate;
                auxUpperAbscissa = upperAbscissa;
                auxLowerAbscissa = lowerAbscissa;
                i++;
            }
        }
    }
}

void drawEllipse(PPMfile *image, Pixel color, int thickness, char axis, Point center, float a, float b) {
    int abscissa, upperAbscissa, lowerAbscissa, ordinate, upperOrdinate, lowerOrdinate, delta, i;
    int auxAbscissa, auxUpperAbscissa, auxLowerAbscissa, auxOrdinate, auxUpperOrdinate, auxLowerOrdinate;
    if (a > b && a > 0 && b > 0) {
        if (axis == 'x') {
            i = 0;
            for (abscissa = (center.abscissa - a); abscissa <= (center.abscissa + a); abscissa++) {
                delta = round(fabs(sqrt(pow(b, 2) * (1 - (pow((abscissa - center.abscissa), 2) / pow(a, 2))))));
                upperOrdinate = center.ordinate + delta;
                lowerOrdinate = center.ordinate - delta;
                if (abscissa >= 0 && abscissa < image->width) {
                    if (upperOrdinate >= 0 && upperOrdinate < image->height) {
                        image->matrix[upperOrdinate][abscissa] = color;
                    }
                    if (lowerOrdinate >= 0 && lowerOrdinate < image->height) {
                        image->matrix[lowerOrdinate][abscissa] = color;
                    }
                }
                if (i > 0) {
                    drawLine(image, color, (Point) {auxAbscissa, auxUpperOrdinate}, (Point) {abscissa, upperOrdinate}, thickness);
                    drawLine(image, color, (Point) {auxAbscissa, auxLowerOrdinate}, (Point) {abscissa, lowerOrdinate}, thickness);
                }
                auxAbscissa = abscissa;
                auxUpperOrdinate = upperOrdinate;
                auxLowerOrdinate = lowerOrdinate;
                i++;
            }
        } else if (axis == 'y') {
            i = 0;
            for (ordinate = (center.ordinate - a); ordinate <= (center.ordinate + a); ordinate++) {
                delta = round(fabs(sqrt(pow(b, 2) * (1 - (pow((ordinate - center.ordinate), 2) / pow(a, 2))))));
                upperAbscissa = center.abscissa + delta;
                lowerAbscissa = center.abscissa - delta;
                if (ordinate >= 0 && ordinate < image->height) {
                    if (upperAbscissa >= 0 && upperAbscissa < image->width) {
                        image->matrix[ordinate][upperAbscissa] = color;
                    }
                    if (lowerAbscissa >= 0 && lowerAbscissa < image->width) {
                        image->matrix[ordinate][lowerAbscissa] = color;
                    }
                }
                if (i > 0) {
                    drawLine(image, color, (Point) {auxUpperAbscissa, auxOrdinate}, (Point) {upperAbscissa, ordinate}, thickness);
                    drawLine(image, color, (Point) {auxLowerAbscissa, auxOrdinate}, (Point) {lowerAbscissa, ordinate}, thickness);
                }
                auxOrdinate = ordinate;
                auxUpperAbscissa = upperAbscissa;
                auxLowerAbscissa = lowerAbscissa;
                i++;
            }
        }
    }
}

void drawHyperbola(PPMfile *image, Pixel color, int thickness, char axis, Point center, float c, float a) {
    int abscissa, upperAbscissa, lowerAbscissa, ordinate, upperOrdinate, lowerOrdinate, delta, i;
    int auxAbscissa, auxUpperAbscissa, auxLowerAbscissa, auxOrdinate, auxUpperOrdinate, auxLowerOrdinate;
    float b;
    if (c > a && c > 0 && a > 0) {
        b = fabs(sqrt(pow(c, 2) - pow(a, 2)));
        if (axis == 'x') {
            i = 0;
            for (abscissa = 0; abscissa < image->width; abscissa++) {
                if (abscissa <= (center.abscissa - a) || abscissa >= (center.abscissa + a)) {
                    delta = round(fabs(sqrt(pow(b, 2) * ((pow((abscissa - center.abscissa), 2) / pow(a, 2)) - 1))));
                    upperOrdinate = center.ordinate + delta;
                    lowerOrdinate = center.ordinate - delta;
                    if (upperOrdinate >= 0 && upperOrdinate < image->height) {
                        image->matrix[upperOrdinate][abscissa] = color;
                    }
                    if (lowerOrdinate >= 0 && lowerOrdinate < image->height) {
                        image->matrix[lowerOrdinate][abscissa] = color;
                    }
                    if (i > 0) {
                        if (auxUpperOrdinate != upperOrdinate
                        && auxUpperOrdinate >= 0 && auxUpperOrdinate < image->height
                        && upperOrdinate >= 0 && upperOrdinate < image->height) {
                            drawLine(image, color, (Point) {auxAbscissa, auxUpperOrdinate}, (Point) {abscissa, upperOrdinate}, thickness);
                        }
                        if (auxLowerOrdinate != lowerOrdinate
                        && auxLowerOrdinate >= 0 && auxLowerOrdinate < image->height
                        && lowerOrdinate >= 0 && lowerOrdinate < image->height) {
                            drawLine(image, color, (Point) {auxAbscissa, auxLowerOrdinate}, (Point) {abscissa, lowerOrdinate}, thickness);
                        }
                    }
                    auxAbscissa = abscissa;
                    auxUpperOrdinate = upperOrdinate;
                    auxLowerOrdinate = lowerOrdinate;
                    i++;
                }
            }
        } else if (axis == 'y') {
            i = 0;
            for (ordinate = 0; ordinate < image->height; ordinate++) {
                if (ordinate <= (center.ordinate - a) || ordinate >= (center.ordinate + a)) {
                    delta = round(fabs(sqrt(pow(b, 2) * ((pow((ordinate - center.ordinate), 2) / pow(a, 2)) - 1))));
                    upperAbscissa = center.abscissa + delta;
                    lowerAbscissa = center.abscissa - delta;
                    if (upperAbscissa >= 0 && upperAbscissa < image->width) {
                        image->matrix[ordinate][upperAbscissa] = color;
                    }
                    if (lowerAbscissa >= 0 && lowerAbscissa < image->width) {
                        image->matrix[ordinate][lowerAbscissa] = color;
                    }
                    if (i > 0) {
                        if (auxUpperAbscissa != upperAbscissa 
                        && auxUpperAbscissa >= 0 && auxUpperAbscissa < image->width
                        && upperAbscissa >= 0 && upperAbscissa < image->width) {
                            drawLine(image, color, (Point) {auxUpperAbscissa, auxOrdinate}, (Point) {upperAbscissa, ordinate}, thickness);
                        }
                        if (auxLowerAbscissa != lowerAbscissa
                        && auxLowerAbscissa >= 0 && auxLowerAbscissa < image->width
                        && lowerAbscissa >= 0 && lowerAbscissa < image->width) {
                            drawLine(image, color, (Point) {auxLowerAbscissa, auxOrdinate}, (Point) {lowerAbscissa, ordinate}, thickness);
                        }
                    }
                    auxOrdinate = ordinate;
                    auxUpperAbscissa = upperAbscissa;
                    auxLowerAbscissa = lowerAbscissa;
                    i++;
                }
            }
        }
    }
}

void grayScaleFilter(PPMfile *image) {
    int color;
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            color = round((image->matrix[i][j].red + image->matrix[i][j].green + image->matrix[i][j].blue) / 3);
            image->matrix[i][j].red = color;
            image->matrix[i][j].green = color;
            image->matrix[i][j].blue = color;
        }
    }
}