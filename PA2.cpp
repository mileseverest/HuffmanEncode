#include "PA2.h"

bool comp(HuffmanTree<char>* a, HuffmanTree<char>* b) // this funcion is a helper function to sort the huffmanTree in my huffmanTreeFromText function
{
	return a->getWeight() < b->getWeight(); // if gets the weight of the two obejcts and sorts them
}

bool toBool(char data) // converts the char into a bool value
{
	return data != '0'; // return the char as a bool value. If it does not equal 0, it will return 1, and if it does equal 0 , it will return 0
}

//PA #2 TODO: finds the smallest tree in a given forest, allowing for a single skip
int PA2::findSmallestTree(vector<HuffmanTree<char> *> forest, int index_to_ignore)
{
	// I didn't need this function

	return -1;
}

//PA #2 TOOD: Generates a Huffman character tree from the supplied text
HuffmanTree<char>* PA2::huffmanTreeFromText(vector<string> data)
{
	//Builds a Huffman Tree from the supplied vector of strings.
	//This function implement's Huffman's Algorithm as specified in page 
	//456 of the book.

	//In order for your tree to be the same as mine, you must take care 
	//to do the following:
	//1.	When merging the two smallest subtrees, make sure to place the 
	//      smallest tree on the left side!
	//2.	Have the newly created tree take the spot of the smallest 
	//		tree in the forest(e.g.vector[smallest] = merged_tree).
	//3.	Use vector.erase(begin() + second_smallest_index) to remove 
	//      the other tree from the forest.

	vector <HuffmanTree <char> *> tree; // new huffman tree
	char getData = '\0';

	int charArray[128];

	int k = 0, i = 0, j = 0;

	while (k < 128) // initialize array
	{
		charArray[k] = 0;

		k++;
	}

	// This takes each character in the text (data) and increments charArray
	// for each character (getData)
	while (j < data.size())
	{
		for (i = 0; i < data[j].size(); i++)
		{
			getData = data[j][i];

			charArray[(getData)]++;
		}

		j++;
	}

	// if the character exists in the text, it will be pushed to the vector tree
	for (i = 0; i < 128; i++)
	{
		if (charArray[i] != 0)
		{
			tree.push_back(new HuffmanTree<char>((char)(i), charArray[i]));
		}
	}

	sort(tree.begin(), tree.end(), comp); // sorts tree by weight from smallest to greatest


	while (tree.size() > 1) // while there is still items in the tree
	{
		HuffmanTree<char> *right = tree.at(0); // get the right value which is the smallest value by weight
		tree.erase(tree.begin()); // delete that value from the tree

		HuffmanTree<char> *left = tree.at(0); // get the left value which is the smallest value by weight
		tree.erase(tree.begin()); // delete that value from the tree

		HuffmanTree<char> *parent = new HuffmanTree<char>(left, right); // create a new HuffmanTree node which creates an internal node with left and right as the children
		tree.push_back(parent); // push that to the end of the tree vector

		sort(tree.begin(), tree.end(), comp); // sort it by weight since we pushed a new value in

	}

	return tree.front(); // return the tree vector
}

//PA #2 TODO: Generates a Huffman character tree from the supplied encoding map
//NOTE: I used a recursive helper function to solve this!
HuffmanTree<char>* PA2::huffmanTreeFromMap(unordered_map<char, string> huffmanMap)
{
	//Generates a Huffman Tree based on the supplied Huffman Map.Recall that a 
	//Huffman Map contains a series of codes(e.g. 'a' = > 001).Each digit(0, 1) 
	//in a given code corresponds to a left branch for 0 and right branch for 1.


	// I did not use this function, so it is incomplete

	int i = 0;
 
	HuffmanTree<char> *root = new HuffmanTree<char>('a', 0);
	HuffmanNode<char> *tree = root->getRoot();

	vector<char> keys;
	keys.reserve(huffmanMap.size());
	vector<string> vals;
	vals.reserve(huffmanMap.size());

	for (auto kv : huffmanMap) {
		keys.push_back(kv.first);
		vals.push_back(kv.second);
	}

	for (i = 0; i < vals.size(); i++)
	{
		helperTreeFromMap(tree, huffmanMap, vals[i]);
	}

	return nullptr;
}

void PA2::helperTreeFromMap(HuffmanNode<char>* node, unordered_map<char, string> map, string path)
{
	/*int i = 0, j = 0;
	char getChar = '\0';

	HuffmanInternalNode<char> *internalNode = dynamic_cast<HuffmanInternalNode<char> *> (node);
	HuffmanNode<char> *left = internalNode->getLeftChild();

	if (node == nullptr)
	{
		node = new HuffmanInternalNode<char>(nullptr, nullptr);
		
	}

	for (j = 0; j < path.size(); j++)
	{
		for (i = 0; i < path.size(); i++)
		{
			getChar = path[j];

			if (getChar == '0')
			{
				if (left)
				{
					helperTreeFromMap(internalNode->getLeftChild(), map, path);
				}

				else
				{
					
				}
			}
		}
	}*/

}

//PA #2 TODO: Generates a Huffman encoding map from the supplied Huffman tree
//NOTE: I used a recursive helper function to solve this!
unordered_map<char, string> PA2::huffmanEncodingMapFromTree(HuffmanTree<char> *tree)
{
	//Generates a Huffman Map based on the supplied Huffman Tree.  Again, recall 
	//that a Huffman Map contains a series of codes(e.g. 'a' = > 001).Each digit(0, 1) 
	//in a given code corresponds to a left branch for 0 and right branch for 1.  
	//As such, a given code represents a pre-order traversal of that bit of the 
	//tree.  I used recursion to solve this problem.

	unordered_map<char, string> result{}; // result map
	
	string path = ""; // initialize path

	HuffmanNode<char> *root = tree->getRoot(); // get the root as a huffmanNode

	helperToMapFromTree(root, result, path); // helper function

	return result;
}

void PA2::helperToMapFromTree(HuffmanNode<char>* node, unordered_map<char, string>& map, string path)
{
	if (!(node->isLeaf())) // if the current node is not a leaf
	{
		HuffmanInternalNode<char> *internalNode = dynamic_cast<HuffmanInternalNode<char> *> (node); // cast it as an internal node
		
		helperToMapFromTree(internalNode->getLeftChild(), map, path.append("0")); // recursive call to the left, adding a '0' to the path
		path.pop_back(); // deletes the 0 from the path
		helperToMapFromTree(internalNode->getRightChild(), map, path.append("1")); // recursive call to the right, adding a '1' to the path
		path.pop_back(); // deletes the 1 from the path
	}

	else // if it is a leaf node
	{
		HuffmanLeafNode<char> *LeafNode = dynamic_cast<HuffmanLeafNode<char> *> (node); // cast it as a leaf node

		map[LeafNode->getValue()] = path; // we now have the path to the current leaf node because of the recusive calls, so store that path with the value in map
	}
}



//PA #2 TODO: Writes an encoding map to file.  Needed for decompression.
void PA2::writeEncodingMapToFile(unordered_map<char, string> huffmanMap, string file_name)
{
	//Writes the supplied encoding map to a file.  My map file has one 
	//association per line (e.g. 'a' and 001).  Each association is separated by 
	//a sentinel value.  In my case, I went with a double pipe (||).

	ofstream outFile; // create our file
	outFile.open(file_name); // open the file

	int i = 0;

	vector<char> keys; // keys gets the character from the huffmanMap
	keys.reserve(huffmanMap.size());
	vector<string> vals; // vals get the values from the huffmanMap
	vals.reserve(huffmanMap.size());

	for (auto kv : huffmanMap) // push the keys and values into the respecive vectors this allows easier acess to the values later
	{ 
		keys.push_back(kv.first);
		vals.push_back(kv.second);
	}

	for (i = 0; i < huffmanMap.size(); i++) // traverse through the huffmanMap
	{
		outFile << keys.at(i) << "|" << vals.at(i) << "|" << endl; // add keys and corresponding vals to the file with a '|' seperating them
	}
}

//PA #2 TODO: Reads an encoding map from a file.  Needed for decompression.
unordered_map<char, string> PA2::readEncodingMapFromFile(string file_name)
{
	//Creates a Huffman Map from the supplied file.Essentially, this is the 
	//inverse of writeEncodingMapToFile.  Be sure to use my StringSplitter class 
	//to make your life easier!

	unordered_map<char, string> result{};

	ifstream file;
	file.open(file_name);
	string line;
	vector<string> temp;

	while (getline(file, line)) // get the line from the file
	{
		temp = StringSplitter::split(line, "|"); // split the string at '|' 

		const char *tempChar = temp.at(0).c_str(); // get the character from the temp vector
		
		result[*tempChar] = temp.at(1); // set the result map as the character and the frequency value

	}

	return result;
}

//PA #2 TODO: Converts a vector of bits (bool) back into readable text using the supplied Huffman map
string PA2::decodeBits(vector<bool> bits, unordered_map<char, string> huffmanMap)
{
	//Uses the supplied Huffman Map to convert the vector of bools (bits) back into text.
	//To solve this problem, I converted the Huffman Map into a Huffman Tree and used 
	//tree traversals to convert the bits back into text.

	// to solve this problem, I traversed through the bits adding them to a string
	// 1 by 1 until a match was found. When a match was found, I decoded it to the proper character
	// and cleared the string to start over and find the next character
	ostringstream result{};
	int i = 0, j = 0;
	HuffmanTree<char> *tree;

	string temp = "\0";

	vector<char> keys; // gets the characters
	keys.reserve(huffmanMap.size());
	vector<string> vals; // gets the weight
	vals.reserve(huffmanMap.size());

	for (auto kv : huffmanMap) 
	{
		keys.push_back(kv.first);
		vals.push_back(kv.second);
	}

	//tree = huffmanTreeFromMap(huffmanMap);

	while (i < bits.size()) // while we are going through the bits
	{
		if (bits[i] == 1) // if the bit is a 1
		{
			temp.append("1"); // add a 1 to the string
		}

		else if (bits[i] == 0) // if the bit is a 0
		{
			temp.append("0"); // add a 0 to the string
		}

		for (j = 0; j < vals.size(); j++) // check to see if the string is a huffman code for a character
		{
			if (temp.compare(vals[j]) == 0) // if it is an existing code
			{
				result.put(keys[j]); // put the character into result
				temp.clear(); // clear our string
			}
		}

		i++;
	}

	return result.str();
}

//PA #2 TODO: Using the supplied Huffman map compression, converts the supplied text into a series of bits (boolean values)
vector<bool> PA2::toBinary(vector<string> text, unordered_map<char, string> huffmanMap)
{
	int i = 0, j = 0, k = 0, l = 0;
	char getChar = '\0';
	vector<bool> result{};

	vector<char> keys; // once again getting the char keys
	keys.reserve(huffmanMap.size());
	vector<string> vals; // getting the frequency values
	vals.reserve(huffmanMap.size());

	for (auto kv : huffmanMap) 
	{
		keys.push_back(kv.first);
		vals.push_back(kv.second);
	}

	while (j < text.size()) // while we are traversing through our  text
	{
		for (i = 0; i < text[j].size(); i++)
		{
			getChar = text[j][i]; // get the current character

			for (k = 0; k < huffmanMap.size(); k++) // traverse through huffman map
			{
				if (getChar == keys.at(k)) // get the key for the current character
				{
					for (l = 0; l < vals[k].size(); l++) // we have the key (ex. 0110) and we use our toBool function 
					{                                    // to convert it into a bool value one character of the string at a time
						bool temp = toBool(vals[k][l]); // get bool value

						result.push_back(temp); // push the bool value into the vector
					}
				}
			}
		}

		j++;
	}

	return result;
}