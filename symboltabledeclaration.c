#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_EXPRESSION_LENGTH 100

typedef enum {
    OPERATOR,
    IDENTIFIER
} SymbolType;

typedef struct {
    char symbol;
    void *address;
    SymbolType type;
} SymbolEntry;

void constructSymbolTable(char expression[], int length) {
    SymbolEntry symbolTable[MAX_EXPRESSION_LENGTH]; 
    int symbolCount = 0;

    printf("Symbol Table display\n");
    printf("Symbol \t Address \t Type\n");

    for (int i = 0; i < length; i++) {
        char currentChar = expression[i];
        if (isalpha(currentChar)) {
            symbolTable[symbolCount].symbol = currentChar;
            symbolTable[symbolCount].address = malloc(sizeof(currentChar));
            symbolTable[symbolCount].type = IDENTIFIER;
            printf("%c \t %p \t Identifier\n", currentChar, symbolTable[symbolCount].address);
            symbolCount++;
        } else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '=' || currentChar == '%' || currentChar == '/') {
            symbolTable[symbolCount].symbol = currentChar;
            symbolTable[symbolCount].address = malloc(sizeof(currentChar));
            symbolTable[symbolCount].type = OPERATOR;
            printf("%c \t %p \t Operator\n", currentChar, symbolTable[symbolCount].address);
            symbolCount++;
        }
    }

    for (int i = 0; i < symbolCount; i++) {
        free(symbolTable[i].address);
    }
}

int main() {
    char expression[MAX_EXPRESSION_LENGTH];
    int length = 0;
    char c;

    printf("Input the expression ending with $ sign: ");
    while ((c = getchar()) != '$' && length < MAX_EXPRESSION_LENGTH) {
        expression[length++] = c;
    }

    printf("Given Expression: %s\n", expression);

    constructSymbolTable(expression, length);

    return 0;
}
