#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// function to check for delimeters
bool isDelimeter(char ch){
    if(ch == ' ' || ch == '(' || ch == ')' || ch == ';' || ch == '+' || ch == '/' || ch == '*' || ch == '>' || ch == '=' || ch == '<'){
        return true;
    }
    return false;
}

// function to check for operators
bool isSeperator(char ch){
    if(ch == '(' || ch == ')' || ch == ';'){
        return true;
    }
    return false;
}

// function to check for operators
bool isOperator(char ch){
    if(ch == '+' || ch == '/' || ch == '*' || ch == '>' || ch == '=' || ch == '<'){
        return true;
    }
    return false;
}

//function to check for integers
bool isInteger(char* str){
    if(strlen(str) == 0) return false;
    for(int i = 0; i < strlen(str); i++){
        if(str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '0'){
            return false;
        }
        return true;
    }
}

// function to check for variable
bool isVariable(char* str){
     if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' || 
        str[0] == '6' || str[0] == '7' || str[0] == '8' || 
        str[0] == '9')
        return (false);
    return (true);
} 

// function to check for keyword
bool isKeyword(char* str){
    if (!strcmp(str, "if") || !strcmp(str, "else") ||
        !strcmp(str, "while") || !strcmp(str, "do") || 
        !strcmp(str, "break") || 
         !strcmp(str, "continue") || !strcmp(str, "int")
        || !strcmp(str, "double") || !strcmp(str, "float")
        || !strcmp(str, "return") || !strcmp(str, "char")
        || !strcmp(str, "case") || !strcmp(str, "char")
        || !strcmp(str, "sizeof") || !strcmp(str, "long")
        || !strcmp(str, "short") || !strcmp(str, "typedef")
        || !strcmp(str, "switch") || !strcmp(str, "unsigned")
        || !strcmp(str, "void") || !strcmp(str, "static")
        || !strcmp(str, "struct") || !strcmp(str, "goto") || !strcmp(str, "for"))
        return (true);
    return (false);
}

// function to get ssubstr
char* subString(char* s, int left, int right){
    char* str = (char*)malloc(sizeof(char*)*(right-left+2));

    for(int i = left; i <= right; i++){
        str[i-left] = s[i]; 
    }
    str[right-left+1] = '\0';
    return str;
}

void parse(char* str){
    int left = 0, right = 0;
    int len = strlen(str);

    while(right <= len && left <= right){
        if(isDelimeter(str[right]) == false) right++;

        if(isDelimeter(str[right]) == true && left == right){
            if(isSeperator(str[right])){
                printf("%c is a seperator\n", str[right]);
            } else if(isOperator(str[right])){
                printf("%c is a operator\n", str[right]);
            }
            right++;
            left = right;
        } else if((isDelimeter(str[right]) == true && left != right) || (right == len && left != right)){
            char* substr = subString(str, left, right-1);
            if(isKeyword(substr)){
                printf("%s is a keyword\n", substr);
            } else if(isInteger(substr)){
                printf("%s is a integer\n", substr);
            } else if(isVariable(str)){
                printf("%s is a variable\n", substr);
            }
            if(isSeperator(str[right])){
                printf("%c is a seperator\n", str[right]);
            }
            right++;
            left = right;
        }
        
    }
}


int main(){
    char str[100];
    fgets(str, 100 , stdin);
    parse(str);
}