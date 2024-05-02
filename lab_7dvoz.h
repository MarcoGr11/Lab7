#include <iostream>
using namespace std;
#include "memory"

using namespace std;

template<typename T>
struct Node2 {
    T data;
    shared_ptr<Node2<T>> next;
    shared_ptr<Node2<T>> prev;
};

template<typename T>
class DoubleList {
private:
    shared_ptr<Node2<T>> head;
    shared_ptr<Node2<T>> tail;
    size_t size;

    shared_ptr<Node2<T>> getNode(size_t index) const; //допомагає нам отримувати доступ до вузлів у списку за їхнім порядковим номером.

public:
    DoubleList() : head(nullptr), tail(nullptr), size(0) {}

    //---Метод вставки---
    void pushBack(const T& value);
    void pushFront(const T& value);

    //---Метод видалення--
    void popBack();
    void popFront();

    //---Додавання та віднімання за індексом--
    void insertAt(size_t index, const T& value);
    void removeAt(size_t index);

    //---Методи для роботи з розміром---
    size_t Size() const { return size; }
    bool isEmpty() const { return size == 0; }

    //---Метод пошуку---
    bool Find(const T& value) const;

    //--Метод доступу за індексом---
    T& operator[](size_t index) const;

    //---Stream insertion---
    friend ostream& operator<<(ostream& os, const DoubleList<T>& list) {
        shared_ptr<Node2<T>> current = list.head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

};

template<typename T>
void DoubleList<T>::pushBack(const T& value) {
    unique_ptr<Node2<T>> newNode = make_unique<Node2<T>>();
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = tail;
    if (tail != nullptr) {
        tail->next = move(newNode);
        tail = tail->next;
    } else {
        head = move(newNode);
        tail = head;
    }
    size++;
}

template<typename T>
void DoubleList<T>::pushFront(const T& value) {
    unique_ptr<Node2<T>> newNode = make_unique<Node2<T>>();
    newNode->data = value;
    newNode->next = head;
    newNode->prev = nullptr;
    if (head != nullptr) {
        head->prev = move(newNode);
    } else {
        tail = move(newNode);
    }
    head = newNode->prev;
    size++;
}

template<typename T>
void DoubleList<T>::popBack() {
    if (tail == nullptr)
        throw out_of_range("List is empty");
    if (head == tail) {
        head.reset();
    } else {
        tail->prev->next.reset();
    }
    tail = tail->prev;
    size--;
}

template<typename T>
void DoubleList<T>::popFront() {
    if (head == nullptr)
        throw out_of_range("List is empty");
    if (head == tail) {
        tail.reset();
    } else {
        head->next->prev.reset();
    }
    head = head->next;
    size--;
}

template<typename T>
void DoubleList<T>::insertAt(size_t index, const T& value) {
    if (index > size)
        throw out_of_range("Index out of range");
    if (index == 0) {
        pushFront(value);
    } else if (index == size) {
        pushBack(value);
    } else {
        shared_ptr<Node2<T>> current = getNode(index);
        unique_ptr<Node2<T>> newNode = make_unique<Node2<T>>();
        newNode->data = value;
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next.reset(newNode.release());   // повертає вказівник який зберігається в unique_ptr і забирає його
        current->prev = current->prev->next;
        size++;
    }
}

template<typename T>
void DoubleList<T>::removeAt(size_t index) {
    if (index >= size)
        throw out_of_range("Index out of range");
    if (index == 0) {
        popFront();
    } else if (index == size - 1) {
        popBack();
    } else {
        shared_ptr<Node2<T>> current = getNode(index);
        current->prev->next = current->next;
        current->next->prev = current->prev;
        size--;
    }
}
template<typename T>
bool DoubleList<T>::Find(const T& value) const {
    shared_ptr<Node2<T>> current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}
template<typename T>
T& DoubleList<T>::operator[](size_t index) const {
    if (index >= size)
        throw out_of_range("Index out of range");
    shared_ptr<Node2<T>> current = getNode(index);
    return current->data;
}

template<typename T>
shared_ptr<Node2<T>> DoubleList<T>::getNode(size_t index) const {
    if (index >= size)
        throw out_of_range("Index out of range");
    shared_ptr<Node2<T>> current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}