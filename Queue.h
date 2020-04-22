#ifndef QUEUE_H_
#define QUEUE_H_
/**
 * Queue define and implement
 */

#include "LinkedList.h"

template<class T>
class Queue {
public:
    Queue();
    ~Queue();
    void insert(T d);
    T remove();
    T peak();
    bool isEmpty();
    int getSize();
    void printQueue();
private:
    LinkedList<T>* listData;
};

/**
 * Default constructor
 */
template<class T>
inline Queue<T>::Queue()
{
    listData = new LinkedList<T>();
}

/**
 * De-structor
 */
template<class T>
Queue<T>::~Queue()
{
    delete listData;
}

/**
 * Insert data to the queue
 */
template<class T>
void Queue<T>::insert(T data)
{
    listData->insertBack(data);
}

/**
 * Return and Remove first element in the list
 * @return: return the first element data
 */
template<class T>
T Queue<T>::remove()
{
    try
    {
        return listData->removeFront();
    }
    catch (const runtime_error& error)
    {
        throw runtime_error("Queue is empty, can not remove");
    }
}

/**
 * Return the value of first element in the list
 * @return: Return the first element data
 */
template<class T>
T Queue<T>::peak()
{
    try
    {
        return listData->getPos(0);
    }
    catch (const runtime_error& error)
    {
        throw runtime_error("Queue is empty, can not peak");
    }

}

/**
 * Check queue empty or not
 * @return: True if queue is empty. Otherwise is false
 */
template<class T>
bool Queue<T>::isEmpty()
{
    return listData->isEmpty();
}

/**
 * Get size of queue
 * @return size of queue
 */
template<class T>
int Queue<T>::getSize()
{
    return listData->getSize();
}

template<class T>
void Queue<T>::printQueue()
{
    return listData->printList();
}
#endif /* QUEUE_H_ */
