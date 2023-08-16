#include "hashMap.h"
#include "hashMap.cpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	hashMap<string, int> h;

	h["Zap"] = 11;
	h["Bam"] = 12;

	h["Zap"] = h["Zap"] - 1;
	h["Bam"] = h["Bam"] + h["Zap"];

	cout << "Zap: " << h["Zap"] << endl;
	cout << "Bam: " << h["Bam"] << endl;

	return 0;
}