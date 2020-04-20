#include"Queue.h"
#include"BinaryTree.h"
#include<fstream>
#include<string>
void HuffManTree(const string filename)
{
	ifstream file(filename);
	string input;
	while (!file.eof())
	{
		string temp;
		getline(file, temp);
		input += temp;
	}
	Array_Queue<TreeNode<char>*>array_queue;
	char ascii = 0;
	for (int i = 0; i <= 127; i++)
	{
		ascii = i;
		int freq = 0;
		for (auto j = input.begin(); j != input.end(); j++)
		{
			if (*j == ascii)
			{
				freq++;
			}
		}
		if (freq > 0)
		{
			TreeNode<char>* l = nullptr;
			TreeNode<char>* r = nullptr;
			array_queue.EnQueue(getNode(ascii,l,r), freq);
		}
	}
	while (array_queue.QueueSize() > 1)
	{
		int f1 = array_queue.getFrequency();
		TreeNode<char>* left = array_queue.DeQueue();
		int f2 = array_queue.getFrequency();
		TreeNode<char>* right = array_queue.DeQueue();
		array_queue.EnQueue(getNode('*', left, right), f1+f2);
	}
	TreeNode<char>* root = array_queue.DeQueue();
	print2D(root);
}
int main()
{
	HuffManTree("original.txt");

}