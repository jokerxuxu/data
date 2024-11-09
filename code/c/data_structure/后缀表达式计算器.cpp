#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
中缀表达式计算
表达式中相邻两个操作符的计算次序为：
优先级高的先计算
优先级相同的根据结合性（运算方向）来进行计算
当使用括号时从最内层括号开始计算
*/

/* 
后缀表达式特点
1、与相应的中缀表达式中的操作数次序相同
2、没有括号
*/

//节点类型
typedef struct Node {
    char data;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *top;
} Stack;

//建栈
Stack* createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

//判断是否为空
int isEmpty(Stack *stack) {
    return stack->top == NULL;
}

//进栈
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

//调取栈顶元素
char peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

//为运算符加权
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

//判断是否为运算符
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//中缀表达式转化为后缀表达式
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
/*
计算后缀表达式操作比较简单：
读到操作数则入栈
读到运算符，弹出right和left进行计算，把得到的结果入栈
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
            push(stack, num);                                    //读取操作数并入栈
        } else if (isOperator(postfix[i])) {
            int right = pop(stack);                              //出栈
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
    printf("璇疯緭鍏ヤ竴涓腑缂�琛ㄨ揪寮忥細");
    fgets(expression, 100, stdin);
    expression[strcspn(expression, "\n")] = '\0'; // Remove newline character

    char postfix[100];
    infixToPostfix(expression, postfix);
    printf("鍚庣紑琛ㄨ揪寮忎负锛?%s\n", postfix);

    int result = evaluatePostfix(postfix);
    printf("缁撴灉涓猴細%d\n", result);

    return 0;
}