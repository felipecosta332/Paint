#include <stdlib.h>
#include <string.h>
#include "../inc/text.h"

void cleanString(char *string) {
    int spaces = 0, i;
    for (i = 0; string[i] == ' '; i++, spaces++);
    for (i = 0; string[i + spaces] != '\0'; i++) {
        string[i] = string[i + spaces];
    }
    string[i] = '\0';
    for (i = 0; string[i] != '\0'; i++) {
        if (string[i] == '\n') {
            string[i] = '\0';
            break;
        }
    }
}

char* insertString(char *target, char *source) {
    int i, j;
    char *string = NULL;
    for (i = 0; target[i] != '\0'; i++);
    for (j = 0; source[j] != '\0'; j++);
    string = calloc((i + j), sizeof(char));
    for (i = 0; source[i] != '\0'; i++) {
        string[i] = source[i];
    }
    for (j = 0; target[j] != '\0'; j++, i++) {
        string[i] = target[j];
    }
    string[i] = '\0';
    return string;
}