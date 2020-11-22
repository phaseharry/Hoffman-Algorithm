#include "Huffman.h"
#include <queue>
#include <string>
#include <iostream>

using namespace std;

Huffman::Huffman(string str) {
	encode(str);
}

void Huffman::encode(string str) {
	buildCharacterMap(str);
	//printFrequenciesMap();
	buildMinHeap();
	buildHuffmanTree();
	//printHuffmanTree();
}

void Huffman::buildMinHeap() {
	for (auto itr = characterMap.begin(); itr != characterMap.end(); itr++) {
		struct Node *charNode = &itr->second;
		minHeap.push(charNode);
	}
}
void Huffman::buildHuffmanTree() {
	struct Node *left, *right, *top;
	while (minHeap.size() != 1) {
		left = minHeap.top(); minHeap.pop();
		right = minHeap.top(); minHeap.pop();
		//cout << left->character << ": " << left->frequency << endl;
		//cout << right->character << ": " << right->frequency << endl;
		top = new Node('$', left->frequency + right->frequency);
		//cout << top->character << ": " << top->frequency << endl;
		top->left = left;
		top->right = right;
		//cout << "top left: " << top->left->character << endl;
	 	//cout << "top right: " << top->right->character << endl << endl;
		minHeap.push(top);
	}
	//cout << "ROOT NODE: " << minHeap.top()->character << ": " << minHeap.top()->frequency << endl;
	printHuffmanCode(minHeap.top(), "");
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
		cout << character << ": " << charNode.frequency << endl;
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

void Huffman::printHuffmanCode(struct Node* node, string str) const {
	if (node->left) printHuffmanCode(node->left, str + "0");
	if (node->right) printHuffmanCode(node->right, str + "1");
	if (!node->left && !node->right) {
		cout << node->character << ": " << str << endl;
	}
}

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
