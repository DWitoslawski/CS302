#include "hashMap.h"
#include "hashMap.cpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	hashMap<string, int> h1;

	h1["Zap"] = 11;
	h1["Bam"] = 12;

	h1["Zap"] = h1["Zap"] - 1;
	h1["Bam"] = h1["Bam"] + h1["Zap"];

	hashMap<string, int> h2(h1);

	h2["Zap"] = 25;
	h2["Bam"] = h2["Zap"] - 10;

	hashMap<string, int> h3;

	h3["Wham"] = 13;
	h3["Zoom"] = 44;

	h3 = h2;

	h3["Zap"] = 30;
	h3["Bam"] = 44;

	cout << "h1 map" << endl;
	cout << "Zap: " << h1["Zap"] << endl;
	cout << "Bam:" << h1["Bam"] << endl;

	cout << endl;

	cout << "h2 map" << endl;
	cout << "Zap: " << h2["Zap"] << endl;
	cout << "Bam: " << h2["Bam"] << endl;
	
	cout << endl;

	cout << "h3 map" << endl;
	cout << "Zap: " << h3["Zap"] << endl;
	cout << "Bam: " << h3["Bam"] << endl;
	cout << "Wham: " << h3["Wham"] << endl;

	return 0;
}