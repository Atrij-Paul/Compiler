#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int i;
int isKeyword(char *token) {
    char *keywords[] = {"int", "char", "float", "double", "long", "short", "void", "signed", "unsigned", "struct", "enum", "union", "const", "volatile"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (i = 0; i < numKeywords; ++i) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;  
        }
    }
    return 0; 
}

int isOperator(char *token) {
    char *operators[] = {"++", "--", "+", "-", "*", "/", "%%", "=", "==", "!=", "<", ">", "<=", ">="};
    int numOperators = sizeof(operators) / sizeof(operators[0]);

    for (i = 0; i < numOperators; ++i) {
        if (strcmp(token, operators[i]) == 0) {
            return 1;  
        }
    }
    return 0; 
}

int isSymbol(char *token) {
    char *symbols[] = {",", ";", "(", ")", "[", "]", "{", "}"};
    int numSymbols = sizeof(symbols) / sizeof(symbols[0]);

    for (i = 0; i < numSymbols; ++i) {
        if (strcmp(token, symbols[i]) == 0) {
            return 1; 
        }
    }
    return 0;  
}

int isNumericValue(char *token) {
    char *endptr;
    strtod(token, &endptr);
    return *endptr == '\0';
}

int main() {
    char input[100];
    char *token;

    printf("Enter an input: ");
    fgets(input, sizeof(input), stdin);

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }


    token = strtok(input, " \t\n\r[],;()");


    while (token != NULL) { 

        if (*token != '\0') { 
            if (isKeyword(token)) {
                printf("Keyword: %s\n", token);
            } else if (isOperator(token)) {
                printf("Operator: %s\n", token);
            } else if (isNumericValue(token)) {
                printf("Numeric Value: %s\n", token);
            } else if (isSymbol(token)) {
                printf("Symbol: %s\n", token);
            } else {
                printf("Identifier: %s\n", token);
            }
        }


        token = strtok(NULL, " \t\n\r*[],;()"); 
    }

    return 0;
}
