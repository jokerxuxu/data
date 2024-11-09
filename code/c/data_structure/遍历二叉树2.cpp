#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char value[10];                                         //dataΪchar�� 
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

//������㺯�� 
TreeNode* createNode(char* value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->value, value);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//ʹ�ò��������ʽ����ڵ㡣
TreeNode* insertLevelOrder(char elements[][10], int i, int n) {
    TreeNode* root = NULL;
    if (i < n && strcmp(elements[i], "0") != 0) {
        root = createNode(elements[i]);
        root->left = insertLevelOrder(elements, 2 * i + 1, n);
        root->right = insertLevelOrder(elements, 2 * i + 2, n);
    }
    return root;
}
//ǰ��+���򹹽�������
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

//������� 
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%s ", root->value);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

//������� 
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%s ", root->value);
        inorderTraversal(root->right);
    }
}

//������� 
void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%s ", root->value);
    }
}

int main() {
    printf("������ڵ�ֵ���Կո�ָ�: ");
    char input[256];
    fgets(input, sizeof(input), stdin);                         //�ӱ�׼�����ȡһ�����ݣ��洢�� input �����С�

    char elements[100][10];
    int n = 0;
    char* token = strtok(input, " \n");
    while (token != NULL) {
        strcpy(elements[n++], token);
        token = strtok(NULL, " \n");
    }

    TreeNode* root = insertLevelOrder(elements, 0, n);

    printf("ǰ�����: ");
    preorderTraversal(root);
    printf("\n�������: ");
    inorderTraversal(root);
    printf("\n�������: ");
    postorderTraversal(root);
    printf("\n");

    return 0;
}