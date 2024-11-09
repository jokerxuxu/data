#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//建立栈数据结构
typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

//创建新的栈
Stack* createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

//判断是否为空栈
int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

//入栈
void push(Stack *stack, char data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

//出栈
char pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    Node *temp = stack->top;
    char data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

//取栈顶元素
char peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

//返回运算符的优先级
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

//判断是否是操作数
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//中缀表达式转换成后缀表达式
void infixToPostfix(char* expression, char* postfix) {
    Stack *stack = createStack();
    int k = 0;
    for (int i = 0; i < strlen(expression); i++) {
        char c = expression[i];

        if (isdigit(c)) {
            postfix[k++] = c;
            while (isdigit(expression[i + 1])) {
                postfix[k++] = expression[++i];
            }
            postfix[k++] = ' ';
        } else if (c == '(') {
            push(stack, c);
        } else if (c == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[k++] = pop(stack);
                postfix[k++] = ' ';
            }
            pop(stack); // Pop '('
        } else if (isOperator(c)) {
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(c)) {
                postfix[k++] = pop(stack);
                postfix[k++] = ' ';
            }
            push(stack, c);
        }
    }

    while (!isEmpty(stack)) {
        postfix[k++] = pop(stack);
        postfix[k++] = ' ';
    }
    postfix[k - 1] = '\0'; // Remove the last space and terminate string
}

//计算后缀表达式
int evaluatePostfix(char* postfix) {
    Stack *stack = createStack();
    int i = 0;
    while (postfix[i]) {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');
            }
            push(stack, num);                                    //将操作数入栈
        } else if (isOperator(postfix[i])) {
            int right = pop(stack);                              //操作数出栈
            int left = pop(stack);
            switch (postfix[i]) {
                case '+': push(stack, left + right); break;
                case '-': push(stack, left - right); break;
                case '*': push(stack, left * right); break;
                case '/': push(stack, left / right); break;
            }
            i++;
        } else {
            i++;
        }
    }
    return pop(stack);
}

int main() {
    char expression[100];
    printf("请输入一个中缀表达式：");
    fgets(expression, 100, stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Remove newline character

    char postfix[100];
    infixToPostfix(expression, postfix);
    printf("后缀表达式为：%s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("结果为：%d\n", result);

    return 0;
}