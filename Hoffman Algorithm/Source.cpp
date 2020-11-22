#include "Huffman.h"
#include <string>
#include <fstream>

using namespace std;

string useBasicTest();

int main() {
	string text = "";
	ifstream file("DNC2004.txt");
	if (file.is_open()) {
		string line = "";
		while (getline(file, line)) {
			text += line;
		}
		file.close();
	}
	Huffman run = Huffman(text);
	run.decode();
	return 0;
}

string useBasicTest() {
	return "aakabbsdgssssd we,.wwewe23232 dsdsdsds";
}
