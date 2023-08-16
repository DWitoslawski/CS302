/******************************************************************************
 Name: Daniel Witoslawski
 NSHE ID: 2000889468
 Assignment 5: Create a custom hashMap class that can be used to substitute for
    std::unordered_map. Use class hashMap to store keywords and category values.
    Once the maps are created, use them in order to read through description text
    and map those words to category keywords. If description text has the right
    amount of keywords for a category, then that category is properly applicable,
    and it will be printed to the console.
 Input: Input txt file that has information about number of cases, number of
    categories per case, category names, number of keywords in that category,
    number of keywords needed to be matched for a proper categorization, keywords,
    and description text to be parsed through.
 Output: If the description text has enough keywords from a specific category,
    this program will output that category name.
 *******************************************************************************/

#include "hashMap.h"
#include <cmath>
#include <string>
using namespace std;


/*
 * Overload the = operator for class hashMap. Deallocate the left-hand side of
 * the = and copy the hashMap from the right-hand side into the left-hand side
 * hashMap.
 */
template <class t1, class t2>
const hashMap<t1, t2>& hashMap<t1, t2>::operator=(const hashMap<t1, t2>& rhs)
{
	if (this != &rhs)
	{
		this->deallocateMap();
        this->copyMap(rhs);
	}

	return *this;
}


/*
 * Overload the [] operator for class hashMap in order to insert the tuple
 * {key : value} into the hashMap with syntax hashMap[key] = value. If items1
 * or items2 take up 20% or more of the capacity of the hashMap, then the
 * hashMap will need to be resized. The key passed into the [] operator will
 * be used in 2 custom hash functions in order to compute random indices in
 * the table1 and table2 arrays where a linked list will be stored. If the key
 * is found at table1[index1] or table2[index2], then the value associated with
 * that key will be returned. If the key is not found in the linked list of either
 * table1 at index1 or table2 at index2, then the {key : value} pair will be
 * passed into a new node in the first table available (value will be set to a
 * default for the type, to be overwritten when [] is called). However, if both
 * table1 at index1 and table2 at index2 are full (linked list of 2 nodes), then
 * the collision counter value will be incremented, the 2 hash functions will
 * recalculate new values for index1 and index2, and the searching/entering process
 * will start again.
 */
template <class t1, class t2>
t2& hashMap<t1, t2>::operator[](t1 key)
{
    // If load factor is reached, resize the tables
    if (static_cast<double>(this->items1) / this->capacity >= 0.2 || static_cast<double>(this->items2) / this->capacity >= 0.2)
        this->resize(this->capacity);

    /* Loop that will update the collision counter upon every collision until
     * key is found or entered into the table.
     */
    for (int collisionCounter = 0; ;collisionCounter++)
    {
        // Calculate index1 and index2 using h1, h2 and collisionCounter
        size_t index1 = (this->h1(key) + collisionCounter * this->h2(key)) % this->capacity;
        size_t index2 = (this->h2(key) + collisionCounter * this->h1(key)) % this->capacity;

        // check tables 1 and 2 for key
        if (this->table1[index1] != nullptr)
        {
            if (this->table1[index1]->key == key)
                return this->table1[index1]->value;
            else if (this->table1[index1]->link != nullptr && this->table1[index1]->link->key == key)
                return this->table1[index1]->link->value;
        }

        if (this->table2[index2] != nullptr)
        {
            if (this->table2[index2]->key == key)
                return this->table2[index2]->value;
            else if (this->table2[index2]->link != nullptr && this->table2[index2]->link->key == key)
                return this->table2[index2]->link->value;
        }
        // check tables 1 and 2 for key


        // if tables 1 and 2 don't have a match and aren't full, add a new node with {key : value}
        if (this->table1[index1] == nullptr || this->table1[index1]->link == nullptr)
        {
            node * newEntry = new node;
            newEntry->key = key;
            newEntry->value = t2();
            newEntry->link = this->table1[index1];
            this->table1[index1] = newEntry;

            if (newEntry->link != nullptr)
                this->items1++;

            return this->table1[index1]->value;
        }

        if (this->table2[index2] == nullptr || this->table2[index2]->link == nullptr)
        {
            node * newEntry = new node;
            newEntry->key = key;
            newEntry->value = t2();
            newEntry->link = this->table2[index2];
            this->table2[index2] = newEntry;

            if (newEntry->link != nullptr)
                this->items2++;

            return this->table2[index2]->value;
        }
        // if tables 1 and 2 don't have a match and aren't full, add a new node with {key : value}
    }
}


/*
 * Function to resize the hashMap once the load factor has been reached. First, set items1
 * and items2 to 0 in order to prevent infinite recursion. Store capacity before updating
 * it by incrementing amount passed into the function. New ** pointers x and y will be
 * created and point to table1 and table2 respectively. Table1 and table2 will then be
 * allocated new dynamic arrays of size [capacity + amount]. This function then loops
 * through the previous capacity and checks the array at each index. If nodes are stored
 * there, then those {key : value} tuples will be passed into table1 or table2 using
 * the custom [] operator with syntax hashMap[key] = value. Once a node has been copied
 * into table1 or table2, it is deallocated. Once the function has gone through every
 * node at every index of x and y (and deallocated them), the function will then deallocate
 * the dynamic arrays pointed to by x and y. The previous table1 and table2 will have
 * been completely copied over to new tables with updated capacity and deallocated. I did
 * not originally initialize all the pointers in the new table1 and table2 from index
 * capacity to index capacity+amount. Those pointers must be set to nullptr.
 */
template <class t1, class t2>
void hashMap<t1, t2>::resize(size_t amount)
{
    this->items1 = this->items2 = 0;
    size_t loopCapacity = this->capacity;

	node ** x, ** y;

    x = this->table1;
    y = this->table2;

    this->table1 = new node*[this->capacity + amount];
    this->table2 = new node*[this->capacity + amount];

    this->capacity = this->capacity + amount;

    // Initialize pointers for entire dynamic array
    for (size_t i = 0; i < this->capacity; i++)
        this->table1[i] = this->table2[i] = nullptr;

    for (size_t i = 0; i < loopCapacity; i++)
    {
        // base case, x and y are both empty at index i
        if (x[i] == nullptr && y[i] == nullptr)
            continue;

        // table 1
        if (x[i] != nullptr)
        {
            (*this)[x[i]->key] = x[i]->value;

            if (x[i]->link != nullptr)
            {
                (*this)[x[i]->link->key] = x[i]->link->value;

                delete x[i]->link;
                x[i]->link = nullptr;
            }

            delete x[i];
        }
        // table 1


        // table 2
        if (y[i] != nullptr)
        {
            (*this)[y[i]->key] = y[i]->value;

            if (y[i]->link != nullptr)
            {
                (*this)[y[i]->link->key] = y[i]->link->value;

                delete y[i]->link;
                y[i]->link = nullptr;
            }

            delete y[i];
        }
        // table 2
    }

    // Deallocate previous table1 and table2
    delete [] x;
    delete [] y;
}


/*
 * Function that deep copies one hashMap into another (used by = operator).
 * First, items1, items2, and capacity are copied. Then, new table1 and table2
 * dynamic arrays are allocated for *this. This function will then loop through
 * the capacity of map. For each index that holds nodes in table1 or table2 of map,
 * a new node is allocated in *this, and the key and value fields are copied into
 * the new node. If there are 2 nodes in the linked list at map[i], link in the newly
 * created node will point to another new node that is allocated. The key and value
 * fields are copied into that node. If the nodes don't exist at map[i], then
 * nullptr will be assigned to the pointer in table1 or table2 at index i.
 */
template <class t1, class t2>
void hashMap<t1, t2>::copyMap(const hashMap<t1, t2>& map)
{
    this->items1 = map.items1;
    this->items2 = map.items2;
    this->capacity = map.capacity;

    this->table1 = new node*[map.capacity];
    this->table2 = new node*[map.capacity];

    for (size_t i = 0; i < map.capacity; i++)
    {
        if (map.table1[i] == nullptr && map.table2[i] == nullptr)
        {
            this->table1[i] = this->table2[i] = nullptr;
            continue;
        }

        if (map.table1[i] != nullptr)
        {
            this->table1[i] = new node;
            table1[i]->key = map.table1[i]->key;
            table1[i]->value = map.table1[i]->value;

            if (map.table1[i]->link != nullptr)
            {
                this->table1[i]->link = new node;
                table1[i]->link->key = map.table1[i]->link->key;
                table1[i]->link->value = map.table1[i]->link->value;
                this->table1[i]->link->link = nullptr;
            }
            else
                this->table1[i]->link = nullptr;
        }
        else
            this->table1[i] = nullptr;


        if (map.table2[i] != nullptr)
        {
            this->table2[i] = new node;
            table2[i]->key = map.table2[i]->key;
            table2[i]->value = map.table2[i]->value;

            if (map.table2[i]->link != nullptr)
            {
                this->table2[i]->link = new node;
                table2[i]->link->key = map.table2[i]->link->key;
                table2[i]->link->value = map.table2[i]->link->value;
                this->table2[i]->link->link = nullptr;
            }
            else
                this->table2[i]->link = nullptr;
        }
        else
            this->table2[i] = nullptr;
    }
}

/*
 * This function deallocates nodes and dynamic arrays associated with a hashMap
 * that calls this function (used by = operator and destructor). This function
 * loops through the capacity of *this. If table1[i] or table2[i] contain any
 * nodes, then those nodes are deallocated. Once the function has gone through
 * every index of table1 and table2, then no more nodes will exist within the
 * structure (all have been deallocated). Finally, this function will deallocate
 * the dynamic arrays table1 and table2.
 */
template <class t1, class t2>
void hashMap<t1, t2>::deallocateMap()
{
	for (size_t i = 0; i < this->capacity; i++)
    {
        if (this->table1[i] == nullptr && this->table2[i] == nullptr)
            continue;

        if (this->table1[i] != nullptr)
        {
            if (this->table1[i]->link != nullptr)
            {
                delete this->table1[i]->link;
                this->table1[i]->link = nullptr;
            }

            delete this->table1[i];
            this->table1[i] = nullptr;
        }

        if (this->table2[i] != nullptr)
        {
            if (this->table2[i]->link != nullptr)
            {
                delete this->table2[i]->link;
                this->table2[i]->link = nullptr;
            }

            delete this->table2[i];
            this->table2[i] = nullptr;
        }
    }

    delete [] table1;
    delete [] table2;

    table1 = table2 = nullptr;
}


/*
 * Custom hash function that takes in a string value and converts it to a
 * numerical value. It takes each character, and multiplies its ASCII value
 * by 10^i based on its position in the string. These values are summed up
 * for every character in the string from left to right.
 */
template <class t1, class t2>
size_t hashMap<t1, t2>::h1(const string& s) const
{
    size_t sum = 0;
    size_t tmp;

    for (size_t i = 0; i < s.length() - 1; i++)
    {
        tmp = pow(10, i);
        tmp *= s[i];
        sum += tmp;
    }

    return sum;
}


/*
 * Custom hash function that takes in a string value and converts it to a
 * numerical value. It takes each character, and multiplies its ASCII value
 * by 10^i based on its position in the string. These values are summed up
 * for every character in the string from right to left.
 */
template <class t1, class t2>
size_t hashMap<t1, t2>::h2(const string& s) const
{
    size_t sum = 0;
    size_t tmp;

    for (size_t i = 0; i < s.length() - 1; i++)
    {
        tmp = pow(10, i);
        tmp *= s[s.length() - 1 - i];
        sum +=tmp;
    }

    return sum;
}