/**
 * @file queue.h
 * Definition of the Queue class.
 */
#ifndef QUEUE_H
#define QUEUE_H

#include "ordering_structure.h"
#include "deque.h"

/**
 * Queue class: represents a standard queue. It is templated to hold elements of
 * any type. 
 */
template <class T>
class Queue : public OrderingStructure<T>
{
  public:
    /**
     * Adds the parameter object to the back of the Queue.
     * @param newItem object to be added to the Queue.
     */
    void enqueue(const T& newItem);

    /**
     * Removes the object at the front of the Queue, and returns it to
     * the caller. You may assume that this function is only called
     * when the Queue is non-empty.
     * @return The item that used to be at the front of the Queue.
     */
    T dequeue();

    /**
     * Adds an element to the ordering structure.
     *
     * @see OrderingStructure::add()
     */
    void add(const T& theItem);

    /**
     * Removes an element from the ordering structure.
     *
     * @see OrderingStructure::remove()
     */
    T remove();

    /**
     * Finds the object at the front of the Queue, and returns it to
     * the caller. Unlike pop(), this operation does not alter the
     * queue. You may assume that this function is only called when the
     * Queue is non-empty.
     * @return The item at the front of the queue.
     */
    T peek();

    /**
     * Determines if the Queue is empty.
     * @return bool which is true if the Queue is empty, false
     *	otherwise.
     */
    bool isEmpty() const;

  private:
    Deque<T> myQueue; 
    // arbitarily say L is the exit end and R is the entry end
    // since popL() only
};
#include "queue.cpp"
#endif
