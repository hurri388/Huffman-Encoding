#include"Queue.h"
#include"BinaryTree.h"
#include"Map.h"
#include<fstream>
#include<string>
int InDecimal(string binary)
{
	int decimal = 0;
	int power = binary.length() - 1;
	for (int i = 0; binary[i] != '\0'; i++, power--)
	{
		decimal += pow(2, power) * (binary[i] - '0');
	}
	return decimal;
}
void SevenBitBlocks(string input, Array_Queue<int>&bitwise_characters)
{
	string sevenbits;
	int count = 1;
	for (auto i = input.begin(); i != input.end(); i++)
	{
		sevenbits += *i;
		if (count == 7)
		{
			bitwise_characters.EnQueue(InDecimal(sevenbits), 1);
			sevenbits.clear();
			count = 1;
			continue;
		}
		count++;
	}
	if (count != 7)
	{
		while (count != 8)
		{
			sevenbits += "0";
			count++;
		}
	}
	bitwise_characters.EnQueue(InDecimal(sevenbits), 1);
}
void HuffManDecoding(TreeNode<char>* root, int& i, string encoded, string& decoded)
{

	if (!root)
		return;
	else if (root->left == NULL && root->right == NULL)
	{
		decoded += root->data;
		return;
	}
	i++;
	if (encoded[i] == '0')
		HuffManDecoding(root->left, i, encoded, decoded);
	else
		HuffManDecoding(root->right, i, encoded, decoded);
}
void HuffManEncoding(TreeNode<char>* root, map<char, string>&EncodedString, string code)
{
	if (!root)
		return;
	else if (!(root->left && root->right))
	{
		EncodedString.insert(root->data, code);
	}
	HuffManEncoding(root->left, EncodedString, code + "0"); 
	HuffManEncoding(root->right, EncodedString, code + "1");
}
void HuffManTree(const string filename)
{
	ifstream file(filename);
	string input;
	if (!file.is_open())
	{
		cout << "Error opening file\n";
		return;
	}
	while (!file.eof())
	{
		string temp;
		getline(file, temp);
		input += temp;
	}
	Array_Queue<TreeNode<char>*>array_queue;
	char ascii = 0;
	int totalBitsOriginal = 0;
	int totalUnique = 0;
	cout << "Characters and their frequencies : " << endl;
	for (int i = 0; i <= 127; i++)
	{
		ascii = i;
		int freq = 0;
		for (auto j = input.begin(); j != input.end(); j++)
		{
			if (*j == ascii)
			{
				freq++;
				totalBitsOriginal += 7;
			}
		}
		if (freq > 0)
		{
			totalUnique += 1;
			TreeNode<char>* l = nullptr;
			TreeNode<char>* r = nullptr;
			array_queue.EnQueue(getNode(ascii,l,r), freq);
			cout << "  " << ascii << "  : " << freq << endl;
			
		}
	}

	cout << "Total Size in Bits of original string : " << totalBitsOriginal << endl;
	cout << "Total unique characters in original string : " << totalUnique << endl;

	while (array_queue.QueueSize() > 1)
	{
		int f1 = array_queue.getFrequency();
		TreeNode<char>* left = array_queue.DeQueue();
		int f2 = array_queue.getFrequency();
		TreeNode<char>* right = array_queue.DeQueue();
		array_queue.EnQueue(getNode('*', left, right), f1+f2);
	}
	string code = "";
	TreeNode<char>* root = array_queue.DeQueue();
	cout << "Printing Tree Inorderly : " << endl;
	Inorder(root);
	
	map<char, string>huffman_Encoded;
	HuffManEncoding(root, huffman_Encoded, code);
	cout << "Character and its encoding : " << endl;

	ofstream outfile("encoded.txt");
	outfile << "Character and its encoding : " << "\n";
	for (int i = 0; i != huffman_Encoded.Size(); i++)
	{
		cout << "  " << huffman_Encoded.getFirst(i) << " : " << huffman_Encoded.getSecond(i) << endl;
		outfile << "  " << huffman_Encoded.getFirst(i) << " : " << huffman_Encoded.getSecond(i) << "\n";
	}

	string Entire_Encoded_String;
	for (auto i = input.begin(); i != input.end(); i++)
	{
		for (int j = 0; j != huffman_Encoded.Size(); j++)
		{
			if (*i == huffman_Encoded.getFirst(j))
			{
				Entire_Encoded_String += huffman_Encoded.getSecond(j);
				break;
			}
		}
	}

	cout << "Size of encoded.txt in bits is : " << Entire_Encoded_String.size() << endl;

	Array_Queue<int>bitwise_characters;
	SevenBitBlocks(Entire_Encoded_String, bitwise_characters);
	outfile << "Seven bit block wise encoding of entire string : " << "\n";
	int a;
	char b;
	while (bitwise_characters.QueueSize() != 0)
	{
		outfile << "ASCII : ";
		a = bitwise_characters.DeQueue();
		outfile << " " << a;
		b = a;
		outfile << "   associated Character : " << b << "\n";
	}
	outfile << "\n\n Entire Encoded string is : \n";
	outfile << Entire_Encoded_String;
	outfile.close();
	ifstream infile("encoded.txt");
	int index = -1;
	string decoded;
	cout << "Decoding...."<<endl;
	ofstream ofile("reconstructed.txt");
	while (index < (int)Entire_Encoded_String.size() - 2)
		HuffManDecoding(root, index, Entire_Encoded_String, decoded);
	ofile << decoded;
	cout << "As compared to the original string the encoded string's data has been compressed by : " << 100.0-((Entire_Encoded_String.size() / (float)(totalBitsOriginal))*100)<<"%!!"<<endl;
}
int main()
{
	HuffManTree("original.txt");

}