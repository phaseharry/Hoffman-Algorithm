#ifndef HUFFMAN
#define HUFFMAN

#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>

using namespace std;

struct Node {
	char character;
	int frequency;
	string code;
	struct Node *left, *right;
	Node(char ch) {
		character = ch;
		frequency = 1;
		left = right = NULL;
	}
	Node(char ch, int freq) {
		character = ch;
		frequency = freq;
		left = right = NULL;
	}
};

// Helper method used to compare character node's frequency for the priority queue (min heap)
struct CompareCharNodes {
	bool operator()(Node *n1, Node *n2) {
		return n1->frequency > n2->frequency;
	}
};

class Huffman {
	private:
		string encodedString;
		// allows incrementing a node's frequency if a specific character node has been added already
		unordered_map<char, Node> characterMap;
		priority_queue<Node*, vector<Node*>, CompareCharNodes> minHeap;
		Node* huffmanTree;
		string fileName;
		void buildCharacterMap(string str);
		void buildHuffmanTree();
		void buildMinHeap();
		void writeEncodedStringToFile();
		void writeDecodedStringToFile();
		string compressEncodedString();
		void assignHuffmanCodeToChar(struct Node* node, string str);
		string encodeString(string str);
		char decodeHelper(string str, int &idx);
		char byteToCharacter(string byte);
		string characterToByte(char letter);
	public:
		Huffman();
		void encode(string str);
		string decode(string str);
		void run(string str, string fileName);
		void printMinHeapVals();
		void printFrequenciesMap() const;
		void printHuffmanTree() const;
};

#endif