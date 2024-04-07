#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char *keywords[] = {"int", "bool", "double", "char", "for", "while", "if", "else", "do", "printf", "scanf"};
    char *operators[] = {"+", "*", "/", "-", "=", "^", "<", ">", "==", ">=", "<="};
    char str[100];
    fgets(str, 100, stdin);
    char token[100];
    for (int i = 0; i < sizeof(str) / sizeof(str[0]); i++) {
        if (str[i] == ';' || str[i] == '(' || str[i] == ')' || str[i] == '{' || str[i] == '}' || str[i] == ',') {
            printf("%c -> seperator\n", str[i]);
        }
        if (str[i] != ';' && str[i] != '(' && str[i] != ')' && str[i] != '{' && str[i] != '}' && str[i] != ',') {
            char temp[2] = {str[i], '\0'};
            strncat(token, temp, sizeof(temp) - 1);
        } else{
            if (token[0] == '\0') {
                break;
            }
            bool isFound = false;
            for(int i = 0; i < sizeof(keywords)/sizeof(keywords[0]); i++){
                if(token && strcmp(keywords[i], token) == 0){
                    printf("%s -> Keyword\n", token);
                    isFound = true;
                }
            }
            for(int i = 0; i < sizeof(operators)/sizeof(operators[0]); i++){
                if(token && strcmp(operators[i], token) == 0){
                    printf("%s -> Operator\n", token);
                    isFound = true;
                }
            }
            if(token && token[0] == '&' && !isFound){
                printf("%s -> Variable\n", token);
                isFound = true;
            }
            if(token && !isFound && token[0] == '\"'){
                printf("%s -> string format\n", token);
                isFound = true;
            }
            if(token && !isFound && token[0] == '\''){
                printf("%s -> character\n", token);
                isFound = true;
            }
            if(token && !isFound) {
                printf("%s -> Value\n", token);
                isFound = true;
            }
            token[0] = '\0';
        }
    }
    return 0;
}