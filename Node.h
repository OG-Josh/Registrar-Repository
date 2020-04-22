#ifndef NODE_H_
#define NODE_H_

/**
 * Node class using for List and Queue
 */
template<class T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;
    //constructor
    Node();
    Node(T d);
    ~Node();
};

template<class T>
Node<T>::Node() {
    next = nullptr;
    prev = nullptr;
}

template<class T>
Node<T>::Node(T d) {
    data = d;
    next = nullptr;
    prev = nullptr;
}

template<class T>
Node<T>::~Node() {
    next = nullptr;
    prev = nullptr;
}

#endif /* NODE_H_ */
