#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
栈和队列结构:
栈用于后进先出的操作。
队列用于先进先出的操作。
栈操作:
push: 将字符压入栈。
pop: 从栈中弹出字符。
队列操作:
enqueue: 将字符加入队列。
dequeue: 从队列中移除字符。
回文检查:
将字符串的每个字符分别压入栈和加入队列。
逐个比较栈弹出的字符和队列移除的字符。
如果所有字符匹配，则字符串是回文。
主函数:
从用户输入获取字符串。
调用 isPalindrome 判断是否为回文，并输出结果。
*/

typedef struct {
    int top;
    char* data;
    int size;
} Stack;

typedef struct {
    int front, rear, size;
    char* data;
    int capacity;
} Queue;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->size = capacity;
    stack->top = -1;
    stack->data = (char*)malloc(stack->size * sizeof(char));
    return stack;
}

int isStackFull(Stack* stack) {
    return stack->top == stack->size - 1;
}

int isStackEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char item) {
    if (!isStackFull(stack)) {
        stack->data[++stack->top] = item;
    }
}

char pop(Stack* stack) {
    if (!isStackEmpty(stack)) {
        return stack->data[stack->top--];
    }
    return '\0';
}

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->data = (char*)malloc(queue->capacity * sizeof(char));
    return queue;
}

int isQueueFull(Queue* queue) {
    return queue->size == queue->capacity;
}

int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

void enqueue(Queue* queue, char item) {
    if (!isQueueFull(queue)) {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->data[queue->rear] = item;
        queue->size++;
    }
}

char dequeue(Queue* queue) {
    if (!isQueueEmpty(queue)) {
        char item = queue->data[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return item;
    }
    return '\0';
}

int isPalindrome(char* str) {
    int len = strlen(str);
    Stack* stack = createStack(len);
    Queue* queue = createQueue(len);

    for (int i = 0; i < len; i++) {
        push(stack, str[i]);
        enqueue(queue, str[i]);
    }

    for (int i = 0; i < len; i++) {
        if (pop(stack) != dequeue(queue)) {
            free(stack->data);
            free(queue->data);
            free(stack);
            free(queue);
            return 0;
        }
    }

    free(stack->data);
    free(queue->data);
    free(stack);
    free(queue);
    return 1;
}

int main() {
    char str[100];
    printf("请输入一个字符串: ");
    scanf("%s", str);

    if (isPalindrome(str)) {
        printf("这个字符串是回文。\n");
    } else {
        printf("这个字符串不是回文。\n");
    }

    return 0;
}