#include "Huffman.h"
#include <string>
#include <fstream>

using namespace std;

string useBasicTest();
void callHuffmanOnFile(Huffman algo,string fileName);

int main() {
	Huffman huffmanAlgorithm = Huffman();
	string fileNames[20] = {
		"DNC2004.txt"
	};
	for (int i = 0; i < 1; i++) {
		callHuffmanOnFile(huffmanAlgorithm, fileNames[i]);
	}
	return 0;
}

string useBasicTest() {
	return "aakabbsdgssssd we,.wwewe23232 dsdsdsds";
}

void callHuffmanOnFile(Huffman algo, string fileName) {
	string text = "";
	ifstream file("input-files/" + fileName);
	if (file.is_open()) {
		string line = "";
		while (getline(file, line)) {
			text += line;
		}
		file.close();
	}
	algo.run(text, fileName);
}