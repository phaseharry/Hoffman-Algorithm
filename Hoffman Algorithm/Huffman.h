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
		struct Node *root;
		// allows incrementing a node's frequency if a specific character node has been added already
		unordered_map<char, Node> characterMap;
		// bool compare(Node const& n1, Node const& n2);
		priority_queue<Node*, vector<Node*>, CompareCharNodes> minHeap;
		void buildCharacterMap(string str);
		void buildHuffmanTree();
		void buildMinHeap();
	public:
		Huffman(string str);
		void encode(string str);
		void printFrequenciesMap() const;
		void printMinHeapVals();
		void printHuffmanTree() const;
		void printHuffmanCode(struct Node* node, string str) const;
};

#endif