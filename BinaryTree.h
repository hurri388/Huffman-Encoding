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
template<class T>
void Inorder(TreeNode<T>* root)
{
	if (!root)
	{
		return;
	}
	Inorder(root->left);
	cout << root->data << endl;
	Inorder(root->right);
}