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

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator++(int)
{
	iterator current(position);
	position = position->next;

	return current;
}

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator++()
{
	position = position->next;

	return *this;
}

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator--(int)
{
	iterator current(position);
	position = position->prev;

	return current;
}

template <class type>
typename LL<type>::iterator LL<type>::iterator::operator--()
{
	position = position->prev;

	return *this;
}


/*
 * Custom default constructor for the LL class. This
 * constructor initializes a LL object to contain a
 * dummy node with next and prev node pointers that
 * both point to itself.
 */
template <class type>
LL<type>::LL()
{
	dummy = new node;
    dummy->next = dummy;
    dummy->prev = dummy;
}


/*
 * Custom copy constructor for the LL class. This
 * constructor starts by initializing a dummy node in this,
 * then setting the next and prev pointer values of dummy to
 * point to itself. Once dummy is properly initialized, the
 * copyList() function in this is called, passing in the LL object
 * copy that was originally passed into the copy constructor. copyList()
 * will deep copy the nodes in copy into this.
 */
template <class type>
LL<type>::LL(const LL<type>& copy)
{
    this->dummy = new node;
    this->dummy->next = this->dummy;
    this->dummy->prev = this->dummy;
    this->copyList(copy);
}


/*
 * This function copies a list rhs into the list that
 * was used to call the function. If the two lists have
 * the same nodes, nothing changes. If the lists are
 * different, this function clears the list before copying
 * the nodes from rhs into it using copyList() (which
 * repeatedly calls tailInsert() until the lists are the
 * same).
 */
template <class type>
const LL<type>& LL<type>::operator=(const LL<type>& rhs)
{
	if (this != &rhs)
	{
		this->clearList();
        this->copyList(rhs);
	}

	return *this;
}


/*
 * This custom destructor calls clearList() in
 * order to remove and deallocate all the nodes
 * in the list until only dummy is left. clearList()
 * uses headRemove() repeatedly until dummy is
 * left. Once that is done, this function
 * deallocates dummy.
 */
template <class type>
LL<type>::~LL()
{
	this->clearList();
    delete dummy;
}


/*
 * This function will insert a new node into the
 * front of the LL object. It will insert the new
 * node between the current front of the list and
 * the dummy node. If the list is empty, the node's
 * next and previous values will point to dummy, and
 * vice versa. The item value of the new node will
 * be the value passed into the function.
 */
template <class type>
void LL<type>::headInsert(const type& item)
{
	node * head;
    head = new node;
    head->item = item;
    head->next = this->dummy->next;
    head->prev = this->dummy;
    this->dummy->next->prev = head;
    this->dummy->next = head;
}


/*
 * This function will insert a new node into the
 * end of the LL object. It will insert the new
 * node between the current end of the list and
 * the dummy node. If the list is empty, the node's
 * next and previous values will point to dummy, and
 * vice versa. The item value of the new node will
 * be the value passed into the function.
 */
template <class type>
void LL<type>::tailInsert(const type& item)
{
	node * tail;
    tail = new node;
    tail->item = item;
    tail->next = this->dummy;
    tail->prev = this->dummy->prev;
    this->dummy->prev->next = tail;
    this->dummy->prev = tail;
}


/*
 * This function will first check to see if
 * the list is not empty. If it is not, then
 * this function will create a temporary node
 * pointer that points to the head of the list.
 * The tmp pointer will make dummy->next point to
 * the node after head, and it will make the node
 * after head's prev point to dummy. This will
 * remove head from the list. Once that is done,
 * the tmp pointer will be used to deallocate
 * the removed head node.
 */
template <class type>
void LL<type>::headRemove()
{
    if (this->isEmpty() == true)
        return;

    node * tmp;
    tmp = this->dummy->next;
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    delete tmp;
    tmp = nullptr;
}


/*
 * This function will first check to see if
 * the list is not empty. If it is not, then
 * this function will create a temporary node
 * pointer that points to the tail of the list.
 * The tmp pointer will make dummy->prev point to
 * the node before tail, and it will make the node
 * before tail's next point to dummy. This will
 * remove tail from the list. Once that is done,
 * the tmp pointer will be used to deallocate
 * the removed tail node.
 */
template <class type>
void LL<type>::tailRemove()
{
    if (this->isEmpty() == true)
        return;

    node * tmp;
    tmp = this->dummy->prev;
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    delete tmp;
    tmp = nullptr;
}


/*
 * This function removes the node that is pointed
 * to by the passed in iterator object at it->position.
 * It creates a temporary node pointer that points to
 * the iterator node. Then, before the node is removed,
 * the function moves it to the next node in the list.
 * If it is at the end of the list, the function will
 * instead move it to the previous node in the list,
 * as that will be the new end after node removal.
 * After the node is logically removed, it is then
 * deallocated.
 */
template <class type>
void LL<type>::removeAtPosition(LL<type>::iterator & it)
{
	node * tmp = it.position;
    if (it == --(this->end()))
        it--;
    else
        it++;
    tmp->next->prev = tmp->prev;
    tmp->prev->next = tmp->next;
    delete tmp;
    tmp = nullptr;
}


/*
 * This function clears out a linked list object
 * by repeatedly calling the headRemove() function
 * until the list is empty. headRemove() makes sure
 * to deallocate each node after removing it from
 * the list.
 */
template <class type>
void LL<type>::clearList()
{
	while(this->isEmpty() == false)
    {
        this->headRemove();
    }
}


/*
 * This function takes a linked list object
 * that is passed into the function, and it
 * deep copies all nodes into the list that
 * called the function. It first clears the
 * list by calling clearList(). The copying is
 * done by calling tailInsert() using the item
 * in each node of copyThisList while traversing
 * through the list from left to right.
 */
template <class type>
void LL<type>::copyList(const LL<type>& copyThisList)
{
	this->clearList();
    node * tmp;
    tmp = copyThisList.dummy->next;
    while(tmp != copyThisList.dummy)
    {
        this->tailInsert(tmp->item);
        tmp = tmp->next;
    }
}