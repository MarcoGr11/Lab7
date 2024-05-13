#include<iostream>
#include "DoubleList.h"
#include "stackArray.h"
#include "SingleList.h"
#include "queue.h"
#include "circularqueue.h"

int main() {

Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    if (queue.isEmpty()){
        std::cout<<"\nQueue empty";
    }else{
        std::cout<<"\nQueue peek: "<<queue.Peek();
    }

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);

    queue.dequeue();

    std::cout<<queue;

CircularQueue<int> circularQueue;
StackArray<int> stackArray;

    stackArray.Push(1);
    stackArray.Push(2);
    stackArray.Push(3);
    if (stackArray.IsEmpty()){
        std::cout<<"\nStack is empty:"<<std::endl;
    }else{
        std::cout<<"\nStack size:"<<stackArray.Size();
    }

stackArray.Push(1);
    stackArray.Push(2);
    stackArray.Push(3);
    stackArray.Push(4);
    stackArray.Push(5);
    stackArray.Push(6);

    stackArray.Pop();

    std::cout<<stackArray;


Stack<int> stack;

    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    if (stack.IsEmpty()){
        std::cout<<"\nStack is empty"<<std::endl;
    }else{
        std::cout<<"\nStack size:"<<stack.Size();
    }

stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Push(4);
    stack.Push(5);
    stack.Push(6);

    stack.Pop();

    std::cout<<stack;



SingleList<std::string> list;

list.pushBack("\nMax");
    list.pushBack("\nHello,");
    list.pushBack("\nGreetings from Stacey");
    std::cout<<list;
};