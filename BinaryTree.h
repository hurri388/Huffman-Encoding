#pragma once
#include"Queue.h"
template<class T>
struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	T data;
};

template<class T>
TreeNode<T>* getNode(T data, TreeNode<T>* left, TreeNode<T>* right)
{
    TreeNode<T>* temp_root = new TreeNode<T>;
    temp_root->left = left;
    temp_root->right = right;
    temp_root->data = data;
	return temp_root;
}
