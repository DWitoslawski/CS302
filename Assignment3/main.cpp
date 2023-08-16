/******************************************************************************
 Name: Daniel Witoslawski
 NSHE ID: 2000889468
 Assignment 3: A program that will take input values from a txt file that represent
    a binary tree and output if that tree is balanced or not. It will recursively
    construct a binary tree via pointers in a preorder fashion, then it will
    recursively measure from the bottom up if each node is balanced. If all nodes
    are balanced, then the tree balances. If any node is unbalanced, so is the tree.
    Finally, the program will recursively deallocate all the nodes created from
    heap memory and exit.
 Input: txt file representing a binary tree (not necessarily balances)
 Output: A std::cout statement that will print out if the tree is balanced or not.
 *******************************************************************************/

#include "binaryTreeClasses.h"
#include <iostream>


/*
 * This function recursively builds a binary tree using text from an input file.
 * If a line starts with Joint, the left and right arm values are read and stored
 * in local variables. Then, the function will call buildTree() on the left child
 * and then the right child nodes. If a line starts with Goped, Bike, or Car, then
 * the function will construct a new node of that type and initialize it with the
 * relevant private variables. It will also set its right and left pointer values
 * to nullptr. Once a function returns up to a parent node, the parent will assign
 * that child's arm length via setArmLength (and the previously stored local variable
 * arm values). Once the function has recursively worked its way up to the root node,
 * it will return the pointer value of that node to main as * root.
 */
binTreeNode* buildTree()
{
    int leftArm, rightArm;
    double w, e, t, f, b;

    std::string node;
    std::cin >> node;

    if (node == "Joint")
    {
        binTreeNode * r = new binTreeNode;

        std::cin >> leftArm >> rightArm;

        r->setLeft(buildTree());
        binTreeNode * left = r->getLeft();
        left->setArmLength(leftArm);

        r->setRight(buildTree());
        binTreeNode * right = r->getRight();
        right->setArmLength(rightArm);

        return r;
    }

    if (node == "Goped")
    {
        std::cin >> w >> e >> t;
        goped * leaf = new goped(w, e, t);
        leaf->setLeft(nullptr);
        leaf->setRight(nullptr);
        return leaf;
    }

    if (node == "Bike")
    {
        std::cin >> w >> f;
        bike * leaf = new bike(w, f);
        leaf->setLeft(nullptr);
        leaf->setRight(nullptr);
        return leaf;
    }

    if (node == "Car")
    {
        std::cin >> w >> e >> t >> b;
        car * leaf = new car(w, e, t, b);
        leaf->setLeft(nullptr);
        leaf->setRight(nullptr);
        return leaf;
    }
}


/*
 * This function recursively gets the weight and arm length of each node and
 * uses that information to compare the torque received from the left and right
 * child of each Joint node. First, it checks if the current node has a weight
 * value of 0.0. If not, the current node is a leaf node with a weight value. The
 * function will return the weight of the current node to the parent node. If the
 * current node is a Joint, then the function will call getObjectsWeight recursively
 * on the left child and then the right child. If the weight returned is -1, then the
 * function returns -1 up to main (unbalanced tree). Otherwise, this function will
 * take the torque of each child node and compare them. If they are equal, the function
 * will return the weight of the left + right children. If not, the function will return
 * -1 up to main.
 */
double getObjectsWeight(binTreeNode * r)
{
    if (r->getWeight() == 0.0)
    {
        binTreeNode * left = r->getLeft();
        double leftWeight = getObjectsWeight(left);
        if (leftWeight == -1)
            return -1;
        int leftArm = left->getArmLength();

        binTreeNode * right = r->getRight();
        double rightWeight = getObjectsWeight(right);
        if (rightWeight == -1)
            return -1;
        int rightArm = right -> getArmLength();

        if ((rightWeight * rightArm) != (leftWeight * leftArm))
            return -1;

        return leftWeight + rightWeight;
    }

    return r->getWeight();
}


/*
 * This function recursively deallocates each node in the binary
 * tree. First, it checks if the current node is a leaf node (if
 * left == nullptr and right == nullptr). If so, the function deletes
 * that node and sets r to nullptr, then returns. If the left or right
 * child is not a nullptr, then the function calls deallocateTree()
 * recursively on the non-null node. Once the function returns all the
 * way up to the root node, the root r is deleted and set to nullptr.
 */
void deallocateTree(binTreeNode * r)
{
    if (r->getLeft() == nullptr && r->getRight() == nullptr)
    {
        delete r;
        r = nullptr;
        return;
    }

    if (r->getLeft() != nullptr)
        deallocateTree(r->getLeft());
    if (r->getRight() != nullptr)
        deallocateTree(r->getRight());

    delete (binTreeNode *) r;
    r = nullptr;
}

int main()
{
    binTreeNode * root = buildTree ();

    if (getObjectsWeight(root) != -1.0)
        std::cout << " Crane can lift the items\n" ;
    else
        std::cout << " Well this is awkward\n" ;

    deallocateTree(root);

    return 0;
}
