/******************************************************************************
 Name: Daniel Witoslawski
 NSHE ID: 2000889468
 Assignment 2: This program tests different matryoshka doll representations
    as input files. The program recursively checks each nested doll in order to
    determine if the matryoshka test case is valid or invalid.
 Input: An input text file of int values representing a matryoshka doll that will
    be used to populate a vector<int>. The int values taken from the file will be
    checked to see if they represent a valid augmented matryoshka doll.
 Output: cout statement saying that the matryoshka is either valid or invalid
 *******************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

/*
 * Recursive function used to check the matryoshka vector to determine
 * if the matryoshka is valid or not. Input is the doll vector, left index,
 * and right index. First check base cases. If the doll passed into the
 * function is empty, then 0 is returned. If the doll passed into the
 * function fails (first value is not negative or the vector's size is
 * not a multiple of 2), then the error code -1 is returned. A loop is
 * created that compares the values of the vector at indices l and r. If
 * the values match, recursively call the function twice. One function call
 * will be for a doll from index l+1 to index r-1 (representing what is nested
 * directly inside the current doll). The other function call will be for a
 * doll from r+1 to r+i (representing a second doll that exists via index r
 * moving to the left - if index r did not move, then the doll will be size 0
 * and return 0). If a -1 error code was returned from either function, the
 * inner dolls were not valid, and the loop will continue, searching for another
 * set of matching values. If a doll or set of dolls nested within a larger doll
 * has a larger combined value than its parent, error code -2 will be returned
 * up to main, where it will be determined that the matryoshka is invalid.
 */
int checkMatryoshka(const vector<int> &doll, int l, int r)
{
    if (l >= r) // implies doll of size 0
        return 0;

    if (doll[l] >= 0 || (r - l) % 2 != 1)
        return -1; //error code value to represent failed vector

    for (int i = 0; l != r; i++) //using i to track how many times r has moved to the left
    {
        if (abs(doll[l]) == doll[r])
        {
            int leftDoll = checkMatryoshka(doll, l+1, r-1);
            if (leftDoll == -1)
            {
                r--;
                continue;
            }
            if (leftDoll == -2)
                return -2; //if invalid matryoshka, pass that value up to main

            int rightDoll = checkMatryoshka(doll, r+1, r+i);
            if (rightDoll == -1)
            {
                r--;
                continue;
            }
            if (rightDoll == -2)
                return -2; //if invalid matryoshka, pass that value up to main

            if (doll[r] <= leftDoll)
                return -2; //error code value to represent an invalid matryoshka

            return abs(doll[l]) + rightDoll;
        }

        r--;
    }

    return -2; //if the vector has been looped through and there was no match for element l, then the matryoshka is invalid
}

int main()
{
    vector<int> matryoshka;
    int dollSize;

    // loop to read in input values into the doll vector
    for (int i = 0; !cin.eof(); i++)
    {
        cin >> dollSize;
        matryoshka.push_back(dollSize);
    }

    matryoshka.pop_back();

    int check = checkMatryoshka(matryoshka, 0, matryoshka.size() - 1);

    if (check == -2)
    {
        cout << ":-( Try again." << endl;
        return 0;
    }

    cout << ":-) matryoshka!" << endl;

    return 0;
}

