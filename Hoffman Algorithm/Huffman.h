#ifndef HUFFMAN
#define HUFFMAN

#include <string>
#include <unordered_map>

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
};

class Huffman {
	private:
		struct Node *root;
		// allows incrementing a node's frequency if a specific character node has been added already
		unordered_map<char, Node> characterMap;
		void buildCharacterMap(string str);
		void updateCharFrequency(char character);
	public:
		Huffman(string str);
		void printFrequenciesMap() const;
};

#endif