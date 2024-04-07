#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_SIZE 100

// Structure to represent a stack
typedef struct {
    int top;
    unsigned capacity;
    char* array;
} Stack;

// Function to create a stack of given capacity
Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Function to check if the stack is full
bool isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to push an item to the stack
void push(Stack* stack, char item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Function to pop an item from the stack
char pop(Stack* stack) {
    if (isEmpty(stack))
        return '\0';
    return stack->array[stack->top--];
}

// Function to return the top element of the stack
char peek(Stack* stack) {
    if (isEmpty(stack))
        return '\0';
    return stack->array[stack->top];
}

// Function to check if a character is an operator
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Function to get the precedence of an operator
int precedence(char ch) {
    switch (ch) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

// Function to convert infix expression to postfix expression
char* infixToPostfix(char* exp) {
    int i, k;
    Stack* stack = createStack(strlen(exp));
    if (!stack)
        return NULL;
    char* postfix = (char*)malloc((strlen(exp) + 1) * sizeof(char));
    if (!postfix)
        return NULL;
    for (i = 0, k = -1; exp[i]; ++i) {
        // If the scanned character is an operand, add it to the output
        if (isalnum(exp[i]))
            postfix[++k] = exp[i];
        // If the scanned character is an '(', push it to the stack
        else if (exp[i] == '(')
            push(stack, exp[i]);
        // If the scanned character is an ')', pop and output from the stack until '(' is encountered
        else if (exp[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                postfix[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return NULL; // Invalid expression
            else
                pop(stack);
        }
        // If an operator is encountered
        else {
            while (!isEmpty(stack) && precedence(exp[i]) <= precedence(peek(stack)))
                postfix[++k] = pop(stack);
            push(stack, exp[i]);
        }
    }
    // Pop all the remaining operators from the stack
    while (!isEmpty(stack))
        postfix[++k] = pop(stack);
    postfix[++k] = '\0';
    return postfix;
}

// Function to evaluate postfix expression
int evaluatePostfix(char* exp) {
    Stack* stack = createStack(strlen(exp));
    if (!stack)
        return -1;
    for (int i = 0; exp[i]; ++i) {
        // If the scanned character is an operand, push it to the stack
        if (isdigit(exp[i]))
            push(stack, exp[i] - '0');
        // If the scanned character is an operator, pop two elements from the stack and apply the operator
        else {
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            switch (exp[i]) {
            case '+':
                push(stack, operand1 + operand2);
                break;
            case '-':
                push(stack, operand1 - operand2);
                break;
            case '*':
                push(stack, operand1 * operand2);
                break;
            case '/':
                push(stack, operand1 / operand2);
                break;
            case '^':
                push(stack, (int)pow(operand1, operand2));
                break;
            }
        }
    }
    return pop(stack);
}

int main() {
    // char exp[] = "1+2*(3^4-5)^(6+7*8)-9";
    char exp[] = "1+2*2";
    char* postfix = infixToPostfix(exp);
    if (!postfix) {
        printf("Invalid expression\n");
        return -1;
    }
    printf("Postfix expression: %s\n", postfix);
    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);
    free(postfix);
    return 0;
}
