#include "Huffman.h"
#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>  

using namespace std;

Huffman::Huffman() {}

void Huffman::run(string str, string file) {
	encodedString = "";
	huffmanTree = NULL;
	characterMap.clear();
	minHeap = priority_queue<Node*, vector<Node*>, CompareCharNodes>();
	fileName = file;
	encode(str);
	//decode(encodedString);
}

// Encodes the string by making a Huffman tree and turning the string into a encoded binary string 
void Huffman::encode(string str) {
	buildCharacterMap(str);
	buildMinHeap();
	buildHuffmanTree();
	printFrequenciesMap();
	printHuffmanTree();
	encodedString = encodeString(str);
	writeEncodedStringToFile();
	writeDecodedStringToFile();
}

// Encodes a given string once a Huffman Tree has been built
string Huffman::encodeString(string str) {
	string encoding = "";
	for (int i = 0; i < str.length(); i++) {
		encoding += characterMap.at(str[i]).code;
	}
	return encoding;
}

// Decodes the encoded string
string Huffman::decode(string str) {
	string decodedString = "";
	int i = 0;
	while (i < encodedString.length()) {
		decodedString += decodeHelper(str, i);
	}
	cout << decodedString << endl;
	return decodedString;
}

// Returns a character once we finished a Huffman code traversal
char Huffman::decodeHelper(string str, int &idx) {
	struct Node* currentNode = huffmanTree;
	stack<Node*> huffmanStack;
	huffmanStack.push(huffmanTree);
	while (!huffmanStack.empty()) {
		Node* currentNode = huffmanStack.top();
		huffmanStack.pop();
		// if currentNode does not have a left or right, then we know its a character left node
		if (currentNode->left == NULL && currentNode->right == NULL) {
			return currentNode->character;
		}
		// go left if the current encoded character == 0, 
		// else if it equals 1, go right
		if (str[idx] == '0') {
			huffmanStack.push(currentNode->left);
		} else if (str[idx] == '1') {
			huffmanStack.push(currentNode->right);
		}
		idx++;
	}
}

// Helper method to build the min heap used to build the Huffman Tree
void Huffman::buildMinHeap() {
	for (auto itr = characterMap.begin(); itr != characterMap.end(); itr++) {
		struct Node *charNode = &itr->second;
		minHeap.push(charNode);
	}
}

// Builds the Huffman Tree and then assigns the code to the Character Nodes
void Huffman::buildHuffmanTree() {
	struct Node *left, *right, *top;
	while (minHeap.size() != 1) {
		left = minHeap.top(); minHeap.pop();
		right = minHeap.top(); minHeap.pop();
		top = new Node('$', left->frequency + right->frequency);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}
	huffmanTree = minHeap.top();
	assignHuffmanCodeToChar(huffmanTree, "");
}

// Store the frequency count of all unique characters in a map
void Huffman::buildCharacterMap(string str) {
	for (int i = 0; i < str.length(); i++) {
		char character = str[i];
		// if it is not in our HashTable, then create a node and have it mapped to that character
		// else increment the frequency count the node's frequency
		if (characterMap.find(character) == characterMap.end()) {
			struct Node charNode = Node(character);
			characterMap.insert({ character, charNode });
		} else {
			struct Node *charNode = &characterMap.at(character);
			charNode->frequency += 1;
		}
	}
}

// After building the Huffman Tree, go to its leaf nodes to the characters and assign the character node's code 
void Huffman::assignHuffmanCodeToChar(struct Node* node, string str) {
	if (node->left) assignHuffmanCodeToChar(node->left, str + "0");
	if (node->right) assignHuffmanCodeToChar(node->right, str + "1");
	if (!node->left && !node->right) {
		//cout << node->character << ": " << str << endl;
		struct Node *charNode = &characterMap.at(node->character);
		charNode->code = str;
	}
}

// Writes the encoded string into an output file
void Huffman::writeEncodedStringToFile() {
	ofstream outputFile("encoded-files/" + fileName + ".huf", ios::out | ios::binary);
	if (!outputFile) {
		cout << "Cannot open file" << endl;
		return;
	}
	for (int i = 0; i < encodedString.length(); i++) {
		outputFile << encodedString[i];
	}
	outputFile.close();
}

// Reads from the encoded file and decodes it and writes it the '/decoded-files' path
void Huffman::writeDecodedStringToFile() {
	// Read in the encoded file
	ifstream encodedFile("encoded-files/" + fileName);
	string text = "";
	if (encodedFile.is_open()) {
		string line = "";
		while (getline(encodedFile, line)) {
			text += line;
		}
		encodedFile.close();
	}
	// Decode the string using the Huffman Tree
	string decodedString = "";
	int i = 0;
	while (i < text.length()) {
		decodedString += decodeHelper(text, i);
	}
	// Output it again to verify that it is the same text as the original input
	ofstream outputFile("decoded-files/" + fileName, ios::out | ios::binary);
	if (!outputFile) {
		cout << "Cannot open file" << endl;
		return;
	}
	for (int i = 0; i < encodedString.length(); i++) {
		outputFile << encodedString[i];
	}
	outputFile.close();
}

// Used for testing purposes to ensure that we have the right count of characters mapped to the correct character
void Huffman::printFrequenciesMap() const {
	for (auto itr = characterMap.begin(); itr != characterMap.end(); itr++) {
		char character = itr->first;
		struct Node charNode = itr->second;
		cout << character << ": " << charNode.frequency << " and code: " << charNode.code << endl;
	}
}

// Used for testing purposes to ensure that our minHeap was correctly ordered
void Huffman::printMinHeapVals() {
	while (!minHeap.empty()) {
		cout << minHeap.top()->character << ": " << minHeap.top()->frequency << endl;
		minHeap.pop();
	}
	cout << endl;
}

// Helper that presents the Human Tree level by level
void Huffman::printHuffmanTree() const {
	Node *rootNode = minHeap.top();
	vector<Node*> level{ rootNode };
	while (level.size() > 0) {
		int length = level.size();
		for (int i = 0; i < length; i++) {
			Node *currentNode = level.front();
			level.erase(level.begin());
			cout << currentNode->character << ": " << currentNode->frequency << "     ";
			if (currentNode->left != NULL) level.push_back(currentNode->left);
			if (currentNode->right != NULL) level.push_back(currentNode->right);
		}
		cout << endl;
	}
}
