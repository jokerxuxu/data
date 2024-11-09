#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
��׺���ʽ����
���ʽ�����������������ļ������Ϊ��
���ȼ��ߵ��ȼ���
���ȼ���ͬ�ĸ��ݽ���ԣ����㷽�������м���
��ʹ������ʱ�����ڲ����ſ�ʼ����
*/

/* 
��׺���ʽ�ص�
1������Ӧ����׺���ʽ�еĲ�����������ͬ
2��û������
*/

//�ڵ�����
typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

//��ջ
Stack* createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

//�ж��Ƿ�Ϊ��
int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

//��ջ
void push(Stack *stack, char data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

//��ջ
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

//��ȡջ��Ԫ��
char peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

//Ϊ�������Ȩ
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

//�ж��Ƿ�Ϊ�����
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//��׺���ʽת��Ϊ��׺���ʽ
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

//�����׺���ʽ
/*
�����׺���ʽ�����Ƚϼ򵥣�
��������������ջ
���������������right��left���м��㣬�ѵõ��Ľ����ջ
*/
int evaluatePostfix(char* postfix) {
    Stack *stack = createStack();
    int i = 0;
    while (postfix[i]) {
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i++] - '0');
            }
            push(stack, num);                                    //��ȡ����������ջ
        } else if (isOperator(postfix[i])) {
            int right = pop(stack);                              //��ջ
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
    printf("后缀表达式为�?%s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("结果为：%d\n", result);

    return 0;
}