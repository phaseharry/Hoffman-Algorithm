#include "Huffman.h"
#include <queue>
#include <string>
#include <iostream>

using namespace std;

Huffman::Huffman(string str) {
	encode(str);
}

// Encodes the string by making a Huffman tree and turning the string into a encoded binary string 
void Huffman::encode(string str) {
	buildCharacterMap(str);
	buildMinHeap();
	buildHuffmanTree();
	encodedString = encodeString(str);
}

string Huffman::encodeString(string str) {
	string encoding = "";
	for (int i = 0; i < str.length(); i++) {
		encoding += characterMap.at(str[i]).code;
	}
	return encoding;
}

void Huffman::decode() {
	string decodeString = "";
	int i = 0;
	while (i < encodedString.length()) {

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

// After building the Huffman Tree, go to its leaf nodes to the characters
// and assign the character node's code 
void Huffman::assignHuffmanCodeToChar(struct Node* node, string str) {
	if (node->left) assignHuffmanCodeToChar(node->left, str + "0");
	if (node->right) assignHuffmanCodeToChar(node->right, str + "1");
	if (!node->left && !node->right) {
		cout << node->character << ": " << str << endl;
		struct Node *charNode = &characterMap.at(node->character);
		charNode->code = str;
	}
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
