#include <iostream>
#include <queue>
#include <vector>
#include <sstream>

using namespace std;

struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string x) : value(x), left(NULL), right(NULL) {}
};

TreeNode* insertLevelOrder(vector<string>& elements, int i, int n) {
    TreeNode* root = nullptr;
    if (i < n) {
        root = new TreeNode(elements[i]);
        root->left = insertLevelOrder(elements, 2 * i + 1, n);
        root->right = insertLevelOrder(elements, 2 * i + 2, n);
    }
    return root;
}

void preorderTraversal(TreeNode* root) {
    if (root) {
        cout << root->value << " ";
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

void inorderTraversal(TreeNode* root) {
    if (root) {
        inorderTraversal(root->left);
        cout << root->value << " ";
        inorderTraversal(root->right);
    }
}

void postorderTraversal(TreeNode* root) {
    if (root) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->value << " ";
    }
}

int main() {
    cout << "请输入节点值，以空格分隔: ";
    string input;
    getline(cin, input);
    stringstream ss(input);
    vector<string> elements;
    string temp;

    while (ss >> temp) {
        elements.push_back(temp);
    }

    int n = elements.size();
    TreeNode* root = insertLevelOrder(elements, 0, n);

    cout << "前序遍历: ";
    preorderTraversal(root);
    cout << "\n中序遍历: ";
    inorderTraversal(root);
    cout << "\n后序遍历: ";
    postorderTraversal(root);
    cout << endl;

    return 0;
}