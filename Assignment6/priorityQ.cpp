#include "priorityQ.h"
#include <cstdlib>
using namespace std;

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ() 
{
    heapArray = new priorityType[6];
    size = 0;
    capacity = 5;
    for (size_t i = 0; i <= 5; i++)
    {
        heapArray[i].key = "";
        heapArray[i].priority = 0;
    }
}

template <class t1, class t2>
priorityQ<t1, t2>::priorityQ(const priorityQ<t1, t2>& copy) 
{
    size = copy.size;
    capacity = copy.capacity;
    itemToPQ = copy.itemToPQ;
    heapArray = new priorityType[capacity + 1];
    for (size_t i = 0; i <= this->capacity; i++)
    {
        heapArray[i].key = copy.heapArray[i].key;
        heapArray[i].priority = copy.heapArray[i].priority;
    }
}

template <class t1, class t2>
const priorityQ<t1, t2>& priorityQ<t1, t2>::operator=(const priorityQ<t1, t2>& rhs)
{
    if (this != &rhs)
    {
        this->size = rhs.size;
        this->capacity = rhs.capacity;
        this->itemToPQ = rhs.itemToPQ;
        delete [] this->heapArray;
        this->heapArray = new priorityType[rhs.capacity + 1];
        for (size_t i = 0; i <= rhs.capacity; i++)
        {
            this->heapArray[i].key = rhs.heapArray[i].key;
            this->heapArray[i].priority = rhs.heapArray[i].priority;
        }
    }

    return *this;
}

template <class t1, class t2>
priorityQ<t1, t2>::~priorityQ()
{
    delete [] heapArray;
    itemToPQ.clear();
}

template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& priority)
{
    if (size == capacity)
    {
        capacity *= 2;
        priorityType * x = heapArray;
        heapArray = new priorityType[capacity + 1];
        for (size_t i = 0; i <= capacity; i++)
        {
            heapArray[i].key = "";
            heapArray[i].priority = 0;
        }

        for (size_t i = 0; i <= size; i++)
            heapArray[i] = x[i];
       delete [] x;
    }

    size++;
    heapArray[size].key = key;
    heapArray[size].priority = priority;
    itemToPQ[key] = size;
    bubbleUp(size);
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front()
{
    if (size == 1)
    {
        itemToPQ.erase(heapArray[1].key);
        size--;
        return;
    }
    itemToPQ.erase(heapArray[1].key);
    heapArray[1] = heapArray[size];
    heapArray[size].key = "";
    heapArray[size].priority = 0;
    itemToPQ[heapArray[1].key] = 1;
    size--;
    bubbleDown(1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::decrease_priority(const t1& key, const t2& priority)
{
    heapArray[itemToPQ[key]].priority = priority;
    bubbleUp(itemToPQ[key]);
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
    return heapArray[1].priority;
}

template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
    return heapArray[1].key;
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{
    if (this->size == 0)
        return true;

    return false;
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
    size_t parentIndex = index / 2;
    if (parentIndex == 0)
        return;

    if (heapArray[index].priority < heapArray[parentIndex].priority)
    {
        itemToPQ[heapArray[index].key] = itemToPQ[heapArray[parentIndex].key];
        itemToPQ[heapArray[parentIndex].key] = index;

        priorityType temp;
        temp.key = heapArray[index].key;
        temp.priority = heapArray[index].priority;
        heapArray[index].key = heapArray[parentIndex].key;
        heapArray[index].priority = heapArray[parentIndex].priority;
        heapArray[parentIndex].key = temp.key;
        heapArray[parentIndex].priority = temp.priority;

        bubbleUp(parentIndex);
    }
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
    size_t leftChildIndex = index * 2, rightChildIndex = index * 2 + 1;
    size_t lesserChildIndex;

    if (leftChildIndex > size)
        return;

    if (rightChildIndex > size)
        lesserChildIndex = leftChildIndex;

    if (leftChildIndex <= size && rightChildIndex <= size)
    {
        if (heapArray[leftChildIndex].priority < heapArray[rightChildIndex].priority)
            lesserChildIndex = leftChildIndex;
        else
            lesserChildIndex = rightChildIndex;
    }

    if(heapArray[index].priority > heapArray[lesserChildIndex].priority)
    {
        itemToPQ[heapArray[index].key] = lesserChildIndex;
        itemToPQ[heapArray[lesserChildIndex].key] = index;

        priorityType temp;
        temp.key = heapArray[index].key;
        temp.priority = heapArray[index].priority;
        heapArray[index].key = heapArray[lesserChildIndex].key;
        heapArray[index].priority = heapArray[lesserChildIndex].priority;
        heapArray[lesserChildIndex].key = temp.key;
        heapArray[lesserChildIndex].priority = temp.priority;

        bubbleDown(lesserChildIndex);
    }
}