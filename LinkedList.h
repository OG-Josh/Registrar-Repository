/**
 * Linked list implement
 */
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <iostream>
#include <exception>
#include "List.h"

using namespace std;

template<class T>
class LinkedList: public List<T> {
public:
    LinkedList();
    ~LinkedList();
    void insertFront(T d);
    void insertBack(T d);
    T removeFront();
    T removeBack();
    T deletePos(int pos);
    int find(T d);
    Node<T>* remove(T d);
    T getPos(int pos);
    bool isEmpty();
    void printList();
    unsigned int getSize();
    T* toArray();
private:
    Node<T>* front;
    Node<T>* back;
    unsigned int size;
};

/**
 * Constructore
 */
template<class T>
LinkedList<T>::LinkedList() {
    front = nullptr;
    back = nullptr;
    size = 0;
}

/**
 * Destructor
 */
template<class T>
LinkedList<T>::~LinkedList() {
    Node<T>* currentNode = front;
    Node<T>* previous = nullptr;
    while (currentNode != nullptr) {
        // Traverse all node in linked list. Then free them
        previous = currentNode;
        currentNode = currentNode->next;
        delete previous;
        previous = nullptr;
    }
}

/**
 * Insert new node to front.
 */
template<class T>
void LinkedList<T>::insertFront(T data) {
    Node<T>* newNode = new Node<T>(data);
    // Check list empty or not first
    if (isEmpty()) {
        back = newNode;
    } else {
        // Insert to front of list
        front->prev = newNode;
        newNode->next = front;
    }
    // new node will be come to front node
    front = newNode;
    // Increase size of list
    size++;
}

/**
 * Insert new node to back
 */
template<class T>
void LinkedList<T>::insertBack(T data) {
    Node<T>* newNode = new Node<T>(data);
    // Check list empty or not first
    if (isEmpty()) {
        front = newNode;
    } else {
        // Insert to front of list
        back->next = newNode;
        newNode->prev = back;
    }
    // New node will become to new back node
    back = newNode;
    // Increase size of list
    size++;
}

/**
 * Remove front node of list
 * @return: data of current front node.
 * throw if list is empty
 */
template<class T>
T LinkedList<T>::removeFront() {
    if (isEmpty()) {
        throw runtime_error("List is empty. Can not remove front node");
    }
    // If is not empty. We can remove this
    Node<T>* currentFront = front;
    if (size == 1) {
        // List just contain 1 node. Remove this mean all front back become to null
        back = nullptr;
    } else {
        // Change previous node of next node
        front->next->prev = nullptr;
    }
    front = front->next;
    T data = currentFront->data;
    // delete current node
    currentFront->next = nullptr;
    delete currentFront;
    size--;
    return data;
}

/**
 * Remove back node
 * @return: data of current back node.
 * throw if list is empty
 */
template<class T>
T LinkedList<T>::removeBack() {
    if (isEmpty()) {
        throw runtime_error("List is empty. Can not remove back node");
    }
    Node<T> *currentBack = back;
    if (size == 1) {
        front = nullptr;
    } else {
        back->prev->next = nullptr;
    }
    back = back->prev;
    T data = currentBack->data;
    currentBack->prev = nullptr;
    delete currentBack;
    size--;
    return data;
}

/**
 * Delete node at position
 * @return: data of node remove
 * throw if invalid pos, out of bounds.
 */
template<class T>
T LinkedList<T>::deletePos(int pos) {
    if (pos > (int)size || pos < 0) {
        throw runtime_error("Out of bounds list. Can not delete position");
    }
    int index = 0;
    Node<T>* currentNode = front;
    Node<T>* previousNode = nullptr;
    // Move current node to position
    while (index != pos) {
        previousNode = currentNode;
        currentNode = currentNode->next;
        index++;
    }
    // Assume this is position need to remove. TODO: In case delete pos front or back. Need handle more
    // Make previous next point to current next
    previousNode->next = currentNode->next;
    // Current node is node will be remove
    currentNode->next = nullptr;
    T data = currentNode->data;
    delete currentNode;
    // decrease size
    size--;
    return data;
}

/**
 * Find node in the linked list
 * @return: The position of node in linked list. If not found, return -1
 */
template<class T>
int LinkedList<T>::find(T data) {
    int index = 0;
    Node<T>* currentNode = front;
    // Traverse all node and find
    while (currentNode != nullptr) {
        if (currentNode->data == data) {
            // Found!! Just break and return function
            break;
        }
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == nullptr) {
        // We move to end list. Can not found.
        index = -1;
    }
    return index;
}

/**
 * Remove node have data from the linked list
 * @return: The node remove. Return nullptr if the linked list don't contain the data
 */
template<class T>
Node<T>* LinkedList<T>::remove(T data) {
    if (isEmpty()) {
        throw runtime_error("List is empty. Can not remove any node.");
    }
    Node<T>* currentNode = front;
    while (currentNode->data != data) {
        currentNode = currentNode->next;
        if (currentNode == nullptr) {
            // Move to end of linked list. Mean no found node in list
            return nullptr;
        }
    }
    // Assume we are found node with data
    if (currentNode == front) {
        // if node remove is front
        front = currentNode->next;
    } else if (currentNode == back) {
        // if node remove is back
        currentNode->prev->next = currentNode->next;
        back = currentNode->prev;
    } else {
        currentNode->prev->next = currentNode->next;
        currentNode->next->prev = currentNode->prev;
    }
    currentNode->next = nullptr;
    currentNode->prev = nullptr;
    size--;
    return currentNode;
}

/**
 * Get data of node at position
 * @return: data of node in position.
 * Throw if position is invalid or out of bound
 */
template<class T>
T LinkedList<T>::getPos(int pos) {
    if (isEmpty()) {
        throw runtime_error("List is empty. Can not get position");
    }
    if (pos > (int)size || pos < 0) {
        throw runtime_error("Out of bounds list. Can not get position");
    }
    Node<T>* currentNode = front;
    int index = 0;
    while (index != pos) {
        currentNode = currentNode->next;
        if (currentNode == nullptr)
            return (T) 0;    //cast to type T to prevent throwing warnings
        index++;
    }
    return currentNode->data;
}

/**
 * Check linked list is empty.
 * @return True if list is empty. Other is false
 */
template<class T>
bool LinkedList<T>::isEmpty() {
    if (size == 0)
        return true;
    return false;
}

/**
 * Print all data of linked list. Using for debug
 */
template<class T>
void LinkedList<T>::printList() {
    Node<T>* currentNode = front;
    while (currentNode != nullptr) {
        cout << currentNode->data << endl;
        currentNode = currentNode->next;
    }
}

/**
 * Get size of linked list
 * @return: size of linked list
 */
template<class T>
unsigned int LinkedList<T>::getSize() {
    return size;
}

/**
 * Convert linked list to array
 * @return: Array contain all element of linked list
 */
template<class T>
T* LinkedList<T>::toArray() {
    T* result = new T[size];
    unsigned int index = 0;
    Node<T>* currentNode = front;
    while (currentNode != NULL) {
        result[index] = currentNode->data;
        ++index;
        currentNode = currentNode->next;
    }
    return result;
}

#endif /* LINKEDLIST_H_ */
