#pragma once
#include"Queue.h"
template<class T>
struct TreeNode {
	TreeNode* left;
	TreeNode* right;
	T data;
};
template<class T>
void print2DUtil(TreeNode<T>* root, int space)
{
	// Base case  
	if (root == NULL)
		return;

	// Increase distance between levels  
	space += COUNT;

	// Process right child first  
	print2DUtil(root->right, space);

	// Print current node after space  
	// count  
	cout << endl;
	for (int i = COUNT; i < space; i++)
		cout << " ";
	cout << root->data << "\n";

	// Process left child  
	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()  
template<class T>
void print2D(TreeNode<T> * root)
{
	// Pass initial space count as 0  
	print2DUtil(root, 0);
}
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
class Tree {
	TreeNode<T>* root;
public:
	Tree();
	TreeNode<T>* insert(T data, TreeNode<T>* left, TreeNode<T>* right);
	~Tree();
	void RecursiveDeletion(TreeNode<T>* node);
};

template<class T>
inline Tree<T>::Tree()
{
	root = NULL;
}

template<class T>
inline TreeNode<T>* Tree<T>::insert(T data, TreeNode<T>* left, TreeNode<T>* right)
{
	root = new TreeNode<T>;
	root->left = left;
	root->right = right;
	root->data = data;
}

template<class T>
inline Tree<T>::~Tree()
{
	RecursiveDeletion(root);
}

template<class T>
inline void Tree<T>::RecursiveDeletion(TreeNode<T>* node)
{
	if (node)
	{
		RecursiveDeletion(node->left);
		RecursiveDeletion(node->right);
		delete node;
	}
}
