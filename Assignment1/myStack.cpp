/*****************************************************************************
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
 ****************************************************************************/

#include <cstdlib>
#include "myStack.h"


/*
 * Custom default constructor that initializes a myStack object
 * to have size 0, capacity 5, and a dynamic array equal in size
 * to the capacity value.
 */
template <class type>
myStack<type>::myStack()
{
	size = 0;
    capacity = 5;
    stackElements = new type[capacity];
}


/*
 * Copy constructor that deep copies an existing myStack object
 * into a newly created myStack object. Calls copyStack()
 * in order to create the new object. It also copies size
 * and capacity values into the new stack object.
 */
template <class type>
myStack<type>::myStack(const myStack<type>& copy)
{
    this->size = 0;
    this->copyStack(copy);
    this->size = copy.size;
    this->capacity = copy.capacity;
}


/*
 * Custom assignment operator for the myStack object class. If the
 * two objects being compared are not the same, this function deallocates
 * the dynamic array in the left-hand object and then deep copies the
 * right-hand object values into the left-hand object.
 */
template <class type>
const myStack<type>& myStack<type>::operator=(const myStack<type>& rhs)
{
	if (this != & rhs)
	{
        this->clearStack();
        this->copyStack(rhs);
	}

	return *this;
}


/*
 * Destructor of the myStack class. This calls the clearStack()
 * function that will deallocate stackElements and set the
 * capacity and size variables to 0.
 */
template <class type>
myStack<type>::~myStack()
{
	this->clearStack();
}


/*
 * Function that will push a type value onto the
 * top of the stack. If the stack is full, this
 * function will first double the size of it by
 * resizing stackElements and changing capacity.
 * Pushing will add the type value passed into
 * the function to the end (top) of stackElements.
 * Then, size will be incremented.
 */
template <class type>
void myStack<type>::push(const type& item)
{
	if (this->size == this->capacity)
    {
        type * tmp;
        tmp = new type[this->capacity * 2];
        for (int i = 0; i < this->capacity; i++)
        {
            tmp[i] = this->stackElements[i];
        }
        delete [] this->stackElements;
        this->stackElements = tmp;
        tmp = nullptr;
        this->capacity = this->capacity * 2;
    }

    this->stackElements[this->size] = item;
    this->size++;
}


/*
 * This function will return the value that is at the
 * top of a stack, without removing it. If there is no
 * elements in the stack, an error will be thrown.
 */
template <class type>
type myStack<type>::peek() const
{
	if (this->isEmpty())
    {
        throw std::out_of_range ("Error: Stack is empty, nothing to peek at ;)");
        return 0;
    }

    return this->stackElements[this->size - 1];
}


/*
 * This function returns the size of a myStack variable.
 */
template <class type>
std::size_t myStack<type>::getSize() const
{
	return this->size;
}


/*
 * This function returns the top (last) element of
 * a myStack variable and then removes that variable
 * from the stack by decrementing size. Technically,
 * the value will still exist in the dynamic array
 * stackElements, but it will either be overwritten
 * later or not be counted due to the size value.
 */
template <class type>
type myStack<type>::pop()
{
	this->size--;
    return this->stackElements[this->size];
}


/*
 * This function returns true if the size of a
 * myStack variable is 0, as in no elements exist
 * on that stack. It will be false otherwise.
 */
template <class type>
bool myStack<type>::isEmpty() const
{
	if (this->size == 0)
    {
        return true;
    }

    else
        return false;
}


/*
 * This function is used by the destructor of the class.
 * First, it will deallocate the stackElements dynamic
 * array of the stack, then it will set size and capacity
 * of the stack to 0.
 */
template <class type>
void myStack<type>::clearStack()
{
	delete [] this->stackElements;
    capacity = 0;
    size = 0;
}


/*
 * This function copies myStack variables into another
 * myStack variable. This function assume that the stack
 * to be copied into is already cleared. Then, this
 * function will deep copy values from copyThisStack into
 * the stack calling the function.
 */
template <class type>
void myStack<type>::copyStack(const myStack<type>& copyThisStack)
{
	this->capacity = copyThisStack.capacity;
    this->size = copyThisStack.size;
    this->stackElements = new type[copyThisStack.capacity];
    for (int i = 0; i < size; i++)
    {
        this->stackElements[i] = copyThisStack.stackElements[i];
    }
}

