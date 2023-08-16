#include "hashMap.h"
#include "hashMap.cpp"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	hashMap<string, int> people;

	people["Tim"] = 7;
    people["Joy"] = 9;
	people["Sky Blue"] = 15;
	people["Red Foo"] = 1;
	people["Ickus"] = 44;
	people["Phil"] = 2;
	people["Lil"] = 12;

	people["Joy"] = people["Red Foo"] + 20;
	people["Sky Blue"] = people["Joy"] - 10;
	people["Earthworm Jim"] = people["Tim"] - 6;
	people["Angelica"] = people["Phil"] - 12;
	people["Oblina"] = people["Earthworm Jim"] + 10;
	people["Ickus"] = 22;
	people["Rocko"] = people["Ickus"] - 10;

	cout << "Tim: " << people["Tim"] << endl;
	cout << "Joy: " << people["Joy"] << endl;
	cout << "Sky Blue: " << people["Sky Blue"] << endl;
	cout << "Red Foo: " << people["Red Foo"] << endl;
	cout << "Earthworm Jim: " << people["Earthworm Jim"] << endl;
	cout << "Ickus: " << people["Ickus"] << endl;
	cout << "Oblina: " << people["Oblina"] << endl;
	cout << "Angelica: " << people["Angelica"] << endl;
	cout << "Phil: " << people["Phil"] << endl;
	cout << "Lil: " << people["Lil"] << endl;
	cout << "Rocko: " << people["Rocko"] << endl;

	return 0;
}