/******************************************************************************
 Name: Daniel Witoslawski
 NSHE ID: 2000889468
 Assignment 1: Create a linked list of stack objects in order to simulate
    the "Accordian" card game. Each node in the linked list contains a
    stack object that represents a stack of cards (can be added to or
    taken away from). Once the game has come to an end based on the rules,
    the list of stacks will be output one by one. The game is won if there
    is only one stack left at the end.
 Input: txt file with 52 two-letter strings (letters represent card and
 suit, respectively).
 Output: Number of stacks: top of each stack and number of cards in each stack
    Ex: 6 Stacks : 2 H :40 QC :8 3 D :1 9 S :1 7 H :1 5 C :1
 *******************************************************************************/

#include "LL.h"
#include "LL.cpp"
#include "myStack.h"
#include "myStack.cpp"
#include <iostream>
#include <string>
using namespace std;


int main()
{
    LL< myStack<string> > accordian;
    LL< myStack<string> > ::iterator it, neighbor;
    myStack<string> temp;
    string card;
    bool neighborFlag;

	/*
	 * Loop through input file until EOF, then push each string (card)
	 * onto temp stack. Then, tail insert a stack of size 1 into accordian.
	 */

    while (!cin.eof())
    {
        cin >> card;
        temp.push(card);
        accordian.tailInsert(temp);
        temp.pop();
    }

    accordian.tailRemove();

    /*
     * This section tests if accordian was populated correctly.

       for (it = accordian.begin(); it != accordian.end(); it++)
        cout << (*it).peek() << " ";

    cout << endl;
     */

    /*
     * Loop to simulate the logic of the game. The game follows the iterator it.
     * To begin, set it to the start of the accordian list. If it points to a node
     * that has a third left neighbor, compare the values. If they match, pop the
     * stack at node it and push it into node neighbor. If there is no match or
     * 3rd left neighbor, check if node it has a left neighbor and compare the values.
     * If there is a match, the same logic of pop and push applies. Once a match
     * has been made, update iterator it to where the popped stack was pushed onto.
     * Check to see if another move can be made from the new iterator it node. If not,
     * move it to the next node and continue the game. Once moves run out, output results.
     */

    it = accordian.begin();

    while (it != accordian.end()) {
        neighbor = it;
        neighborFlag = true;

        /*
         * Loop to check if iterator it has a third neighbor. If decrementing thirdNeighbor
         * 3 times would be out of bounds, set neighbor to nullptr.
         */

        for (int i = 0; i < 3; i++)
        {
            if (neighbor == accordian.begin()) {
                neighborFlag = false;
                break;
            }

            neighbor--;
        }

        /*
         * Check if node it matches neighbor (third neighbor). If so, pop the stack at node it
         * and push into node neighbor. If it is empty, remove the node. Set it = neighbor and
         * start the game from there (restart the loop).
         */
        if (neighborFlag)
        {
            if ((*neighbor).peek()[0] == (*it).peek()[0] or (*neighbor).peek()[1] == (*it).peek()[1])
            {
                (*neighbor).push((*it).pop());

                if ((*it).isEmpty())
                    accordian.removeAtPosition(it);

                it = neighbor;
                continue;
            }
        }

        /* Check to see if left neighbor of node it exists. If so, move neighbor iterator
         * to that position for checks. If not (if node it is at the beginning of the list),
         * move onto the next stack.
         */


        if (it == accordian.begin())
        {
            it++;
            continue;
        }

        neighbor = it;
        neighbor--;

        /*
         * Check if node it matches neighbor (left neighbor). If so, pop the stack at node it
         * and push into node neighbor. If node it is empty, remove the node. Set it = neighbor and
         * start the game from there (restart the loop).
         */
        if ( (*neighbor).peek()[0] == (*it).peek()[0] or (*neighbor).peek()[1] == (*it).peek()[1] )
        {
            (*neighbor).push((*it).pop());

            if ((*it).isEmpty())
                accordian.removeAtPosition(it);

            it = neighbor;
            continue;
        }

        // If no matches to third neighbor or neighbor, move it to the next node and continue the game.
        it++;

    }

    int i = 0;

    for (it = accordian.begin(); it != accordian.end(); it++)
    {
        i++;
    }

    cout << endl << i << " Stacks:";

    for (it = accordian.begin(); it != accordian.end(); it++)
    {
        i = 0;
        cout << " " << (*it).peek() << ":";

        while(!(*it).isEmpty())
        {
            (*it).pop();
            i++;
        }

        cout << i;
    }

    cout << endl << endl;

    return 0;
}

