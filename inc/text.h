#ifndef TEXT_H
#define TEXT_H

/**
 * Cleans the string of spaces in the beginning
 * and newlines at the end.
 * @param string
 * @return this procedure does not return anything
*/
void cleanString(char *string);

/**
 * Puts the source string in front of the target string
 * and returns the resulting string.
 * @param target target string
 * @param source source string
 * @return returns a string
*/
char* insertString(char *target, char *source);

#endif