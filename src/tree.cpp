#include <iostream>
#include <stack>
#include <list>

/**
 *    已知先序遍历和中序遍历,构造二叉树
 *    思路:
 *        如下图分别画出了先序遍历以及中序遍历的节点分布规律，在中序遍历中找到根节点，递归的处理左右子树即可
 *     
 *        根           -----------------------左子树--------------------------             -----------------------右子树-----------------
 *     preLeft   preleft+1                          pIndex-inLeft+preLeft             pIndex-inLeft+preLeft+1       preRight
 * 
 *     inLeft                                                           pIndex-1    pIndex              pIndex+1                                        inRight
 *     -----------------------左子树--------------------------        根                   -----------------------右子树-----------------
 * */
typedef struct Node {
    int data;
    Node* left;
    Node* right;
} Tree;

int preNodes[] = {3,9,20,15,7};
int inNodes[] = {9,3,15,20,7};

Node* buildTree(int pre[],int preLeft,int preRight,int in[],int inLeft,int inRight) {
     std::cout << sizeof(pre)/sizeof(int);
}
void preOrder(Tree* root) {
    if(root == nullptr) {
        return;
    }
    std::stack<Node*> nodes;
    nodes.push(root);
    while(!nodes.empty()) {
        auto node = nodes.top();
        nodes.pop();
        std::cout << node->data;
        if(node->left) {
            nodes.push(node->left);
        }
    }
}

void inOrder(Tree* root) {
    if(root == nullptr) {
        return;
    }
    std::stack<Node*> nodes;
    nodes.push(root);
}

void postOrder(Tree* root) {
    if(root == nullptr) {
        return;
    }
    std::stack<Node*> nodes;
    nodes.push(root);
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
