#include "Huffman.h"
#include <string>

using namespace std;

string useBasicTest();

int main() {
	Huffman run = Huffman(useBasicTest());
	run.decode();
	return 0;
}

string useBasicTest() {
	return "aakabbsdgssssd we,.wwewe23232 dsdsdsds";
}
