#include "Huffman.h"
#include <queue>
#include <string>
#include <iostream>

using namespace std;

Huffman::Huffman(string str) {
	buildCharacterMap(str);
}

void Huffman::buildCharacterMap(string str) {
	for (int i = 0; i < str.length(); i++) {
		updateCharFrequency(str[i]);
	}
}

void Huffman::updateCharFrequency(char character) {
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

void Huffman::printFrequenciesMap() const {
	for (auto itr = characterMap.begin(); itr != characterMap.end(); itr++) {
		char character = itr->first;
		struct Node charNode = itr->second;
		cout << character << ": " << charNode.frequency << endl;
	}
}