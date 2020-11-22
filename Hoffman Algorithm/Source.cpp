#include "Huffman.h"
#include <string>

using namespace std;

string useBasicTest();

int main() {
	Huffman run = Huffman(useBasicTest());
	run.printFrequenciesMap();
	return 0;
}

string useBasicTest() {
	return "aaabbsdssssd wewwewe23232 dsdsdsds";
}
