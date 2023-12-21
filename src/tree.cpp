#include <iostream>
#include <stack>
#include <list>
#include <queue>
#include <vector>

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

using namespace  std;

typedef struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
} Tree;

int preNodes[] = {3,9,20,15,7};
int inNodes[] = {9,3,15,20,7};

TreeNode* buildTree(int pre[],int preLeft,int preRight,int in[],int inLeft,int inRight) {
     std::cout << sizeof(pre)/sizeof(int);
}

void preOrderRecursive(Tree* root,vector<int>& result) {
    if(nullptr == root) {
        return;
    }
    result.emplace_back(root->data);
    if(root->left){
        preOrderRecursive(root->left,result);
    }
    if(root->right){
        preOrderRecursive(root->right,result);
    }    
} 
void inOrderRecursive(Tree* root,vector<int>& result) {
    if(nullptr == root) {
        return;
    }
    if(root->left){
        inOrderRecursive(root->left,result);
    }
    result.emplace_back(root->data);
    if(root->right){
        inOrderRecursive(root->right,result);
    }    
} 
void postOrderRecursive(Tree* root,vector<int>& result) {
    if(nullptr == root) {
        return;
    }
    if(root->left){
        postOrderRecursive(root->left,result);
    }
    if(root->right){
        postOrderRecursive(root->right,result);
    }
    result.emplace_back(root->data);
}

void preOrderNonRecursive(Tree* root,vector<int>& result) {
    if(root == nullptr) {
        return;
    }

    //把根节点入栈
    stack<TreeNode*> nodes;
    nodes.push(root);

    while(!nodes.empty()) {
        //弹出中节点，并访问
        TreeNode* node = nodes.top();
        nodes.pop();
        result.emplace_back(node->data);

        //先入右子树，这样右子树后出。
        if(node->right)nodes.push(node->right);

        //后入左子树，这样左子树先出。
        if(node->left)nodes.push(node->left);
    }
}

void inOrderNonRecursive(Tree* root,vector<int>& result) {
    if(root == nullptr) {
        return;
    }
    TreeNode* node = root;
    stack<TreeNode*> nodes;

    while(!nodes.empty() || !node) {
        //先要走到最底层，将沿途节点存入栈
        if(!node) {
            nodes.push(node);
            node = node->left;
        } else {
            //到达底层，开始弹出，访问节点，并将右子树入栈
            node = nodes.top();
            nodes.pop();
            
            //访问该节点
            result.emplace_back(node->data);
            
            //遍历该节点的右子树
            node = node->right;
        }
    }
}

//采取特殊的先序遍历(中右左)，再逆转一次，就是后序(左右中)
void postOrderNonRecursive(Tree* root,vector<int>& result) {
    if(root == nullptr) {
        return;
    }
    //把根节点入栈
    stack<TreeNode*> nodes;
    nodes.push(root);

    while(!nodes.empty()) {
        //弹出中节点，并访问
        TreeNode* node = nodes.top();
        nodes.pop();
        result.emplace_back(node->data);

        //先入左子树，这样左子树后出。
        if(node->left)nodes.push(node->left);

        //再入右子树，这样右子树先出。
        if(node->right)nodes.push(node->right);
    }

    std::reverse(result.begin(),result.end());
}

void levelOrder(Tree* root,vector<vector<int>>& result) {
    if(nullptr == root) {
        return;
    }
    queue<TreeNode*> nodes;
    nodes.push(root);

    while(!nodes.empty()) {
        int size = nodes.size();
        result.push_back(vector<int>());

        //遍历这一层节点,并把这一层的子节点入队列
        for(int i=0;i<size;i++) {
            TreeNode* node = nodes.front();
            nodes.pop();
            result.back().push_back(node->data);
            if(node->left){
                nodes.push(node->left);
            }
            if(node->right){
                nodes.push(node->right);
            }
        }
    }
}


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
