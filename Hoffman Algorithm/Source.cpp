#include "Huffman.h"
#include <string>
#include <fstream>

using namespace std;

string useBasicTest();
void callHuffmanOnFile(Huffman algo,string fileName);

int main() {
	Huffman huffmanAlgorithm = Huffman();
	string fileNames[20] = {
		"DNC2004.txt",
		"Parliament2011.txt",
		"BarackObama2016DNC.txt",
		"ChaosMonkey.txt",
		"GrantPark2008.txt",
		"LoremIpsum1.txt",
		"LoremIpsum2.txt",
		"LoremIpsum3.txt",
		"LoremIpsum4.txt",
		"LoremIpsum5.txt",
		"LoremIpsum6.txt",
		"LoremIpsum7.txt",
		"LoremIpsum8.txt",
		"LoremIpsum9.txt",
		"LoremIpsum10.txt",
		"LoremIpsum11.txt",
		"LoremIpsum12.txt",
		"LoremIpsum13.txt",
		"MichelleObama2016DNC.txt",
		"SnowdenInterview.txt",
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