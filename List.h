#ifndef LIST_H_
#define LIST_H_

/**
 * Define List interface
 */
#include "Node.h"
template <class T>
class List
{
public:
    // Functional
    virtual void insertFront(T d) = 0; // Insert to front of list
    virtual void insertBack(T d) = 0; // Insert to back of list
    virtual T removeFront() = 0; // remove front node
    virtual T removeBack() = 0; // remove last node
    virtual T deletePos(int pos) = 0; // remove node at position
    virtual int find(T d) = 0; // find data exist in the list
    virtual Node<T>* remove(T d) = 0; // remove the node in list
    // Helper function
    virtual T getPos(int pos) = 0; // getter node at position
    virtual bool isEmpty() = 0; // check list empty
    virtual void printList() = 0; // print the list
    virtual unsigned int getSize() = 0; // get size of list
    virtual T* toArray() = 0; // convert list to array
};

#endif /* LIST_H_ */
