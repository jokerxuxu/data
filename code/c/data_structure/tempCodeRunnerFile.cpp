#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char value[10];                                         //data为char型 
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

//创建结点函数 
TreeNode* createNode(char* value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->value, value);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//使用层序遍历方式插入节点。
TreeNode* insertLevelOrder(char elements[][10], int i, int n) {
    TreeNode* root = NULL;
    if (i < n && strcmp(elements[i], "0") != 0) {
        root = createNode(elements[i]);
        root->left = insertLevelOrder(elements, 2 * i + 1, n);
        root->right = insertLevelOrder(elements, 2 * i + 2, n);
    }
    return root;
}
//前序+中序构建二叉树
/*
TreeNode* buildTree(char inOrder[][10], char preOrder[][10], int inStart, int inEnd, int* preIndex, int n) {
    if (inStart > inEnd) {
        return NULL;
    }

    TreeNode* root = createNode(preOrder[*preIndex]);
    (*preIndex)++;

    if (inStart == inEnd) {
        return root;
    }

    int inIndex = search(inOrder, inStart, inEnd, root->value);

    root->left = buildTree(inOrder, preOrder, inStart, inIndex - 1, preIndex, n);
    root->right = buildTree(inOrder, preOrder, inIndex + 1, inEnd, preIndex, n);

    return root;
}
*/

//先序遍历 
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%s ", root->value);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

//中序遍历 
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s ", root->value);
        inorderTraversal(root->right);
    }
}

//后序遍历 
void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%s ", root->value);
    }
}

int main() {
    printf("请输入节点值，以空格分隔: ");
    char input[256];
    fgets(input, sizeof(input), stdin);                         //从标准输入读取一行数据，存储在 input 数组中。

    char elements[100][10];
    int n = 0;
    char* token = strtok(input, " \n");
    while (token != NULL) {
        strcpy(elements[n++], token);
        token = strtok(NULL, " \n");
    }

    TreeNode* root = insertLevelOrder(elements, 0, n);

    printf("前序遍历: ");
    preorderTraversal(root);
    printf("\n中序遍历: ");
    inorderTraversal(root);
    printf("\n后序遍历: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}