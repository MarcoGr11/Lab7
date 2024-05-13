#include "DoubleList.h"
#include <iostream>
const int SIZE = 5;


template<typename T>
class Queue{
private:
    DoubleList<T> list;
    size_t capacity;
public:
    Queue() = default;
    Queue(const Queue& other) = default;
    Queue(Queue&& other) = default;

    ~Queue() = default;

    Queue& operator=(const Queue& other) = default;
    Queue& operator=(Queue&& other) noexcept = default;

    // Через двозвязний список:
    bool isEmpty()const{
        return list.Size() == 0;
    }
    bool isFull()const{
        return list.Size() == capacity;
    }
    void enqueue(const T& value){
        list.pushBack(value);
    }
    T dequeue(){
        if (isEmpty()){
            throw std::underflow_error("Queue is empty |'_'|");
        }
        T frontValue = list[0];
        list.popFront();
        return frontValue;
    }
    T Peek()const{
        if(isEmpty()){
            throw std::out_of_range("Queue is empty |'_'|");
        }
        return list[0];
    }


    friend std::ostream& operator<<(std::ostream& os, const Queue<T>& queue) {
        os << queue.list;
        return os;
    }
}; // Це черга
template<typename T>
class CircularQueue {
private:
    DoubleList<T> list;
    size_t capacity;  // ---- Макс. місткість черги
public:
    CircularQueue() = default;

    CircularQueue(size_t capacity) : list(), capacity(capacity) {}

    bool isEmpty()const{
        return list.Size() == 0;
    }

    bool isFull()const{
        return list.Size() == capacity;
    }

    void enqueue(const T& value){
        list.pushBack(value);
    }

    T dequeue(){
        if (isEmpty()){
            throw std::underflow_error("Queue is empty |'_'|");
        }
        T value = list[0];
        list.popFront();
        return value;
    }

    T peek() const{
        if(isEmpty()){
            throw std::out_of_range("Queue is empty |'_'|");
        }
        return list[0];
    }



    friend std::ostream& operator<<(std::ostream& os, const CircularQueue<T>& circularQueue) {
        os << circularQueue.list;
        return os;
    }
}; //Це циклічна черга