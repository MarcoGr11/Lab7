#include <iostream>
#include <memory> 

template<typename T>
struct Node2 {
    T data; 
    std::shared_ptr<Node2<T>> next; 
    std::shared_ptr<Node2<T>> prev; 
};

template<typename T>
class DoubleList {
private:
    std::shared_ptr<Node2<T>> head; // вказ початок списку
    std::shared_ptr<Node2<T>> tail; // вказ кінець списку
    size_t size; 

    std::shared_ptr<Node2<T>> getNode(size_t index) const; //отрим доступ порядк номер

public:
    DoubleList() : head(nullptr), tail(nullptr), size(0) {}

    // дод елемент в кінець 
    void pushBack(const T& value);
    
    // дод елемента на почат
    void pushFront(const T& value);

    // вид останнього елемента
    void popBack();
    
    // вид першого елемента 
    void popFront();


    // вставка елемента за  задан індекс 
    void insertAt(size_t index, const T& value);
    
    // видалення елемент за задан індекс
    void removeAt(size_t index);

    size_t Size() const { return size; }
    
    bool isEmpty() const { return size == 0; }

    bool Find(const T& value) const;

    // отрим елемента списку за індекс
    T& operator[](size_t index) const;
    // вивід списку у потік
    friend std::ostream& operator<<(std::ostream& os, const DoubleList<T>& list) {
        std::shared_ptr<Node2<T>> current = list.head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

};

// дод елемента в кінець 
template<typename T>
void DoubleList<T>::pushBack(const T& value) {
    std::shared_ptr<Node2<T>> newNode = std::make_shared<Node2<T>>();
    newNode->data = value;
    newNode->next = nullptr;
    newNode->prev = tail;
    if (tail != nullptr) {
        tail->next = newNode;
        tail = tail->next;
    } else {
        head = std::move(newNode);
        tail = head;
    }
    size++;
}

// дод елемента на початок 
template<typename T>
void DoubleList<T>::pushFront(const T& value) {
    std::shared_ptr<Node2<T>> newNode = std::make_shared<Node2<T>>();
    newNode->data = value;
    newNode->next = head;
    newNode->prev = nullptr;
    if (head != nullptr) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
    size++;
}

// вид останнього елемента 
template<typename T>
void DoubleList<T>::popBack() {
    if (tail == nullptr)
        throw std::out_of_range("List is empty");
    if (head == tail) {
        head.reset();
    } else {
        tail->prev->next.reset();
    }
    tail = tail->prev;
    size--;
}

// вид першого елемента 
template<typename T>
void DoubleList<T>::popFront() {
    if (head == nullptr)
        throw std::out_of_range("List is empty");
    if (head == tail) {
        tail.reset();
    } else {
        head->next->prev.reset();
    }
    head = head->next;
    size--;
}

// встав елемента за заданим індексом
template<typename T>
void DoubleList<T>::insertAt(size_t index, const T& value) {
    if (index > size)
        throw std::out_of_range("Index out of range");
    if (index == 0) {
        pushFront(value);
    } else if (index == size) {
        pushBack(value);
    } else {
        std::shared_ptr<Node2<T>> current = getNode(index);
        std::unique_ptr<Node2<T>> newNode = std::make_unique<Node2<T>>();
        newNode->data = value;
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next.reset(newNode.release()); 
        current->prev = current->prev->next;
        size++;
    }
}

// вид елемента за заданим індекс
template<typename T>
void DoubleList<T>::removeAt(size_t index) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    if (index == 0) {
        popFront();
    } else if (index == size - 1) {
        popBack();
    } else {
        std::shared_ptr<Node2<T>> current = getNode(index);
        current->prev->next = current->next;
        current->next->prev = current->prev;
        size--;
    }
}

// пошук елемента
template<typename T>
bool DoubleList<T>::Find(const T& value) const {
    std::shared_ptr<Node2<T>> current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// отрим елемента списку за індексом
template<typename T>
T& DoubleList<T>::operator[](size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    std::shared_ptr<Node2<T>> current = getNode(index);
    return current->data;
}

// отрим  вузла списку за індексом
template<typename T>
std::shared_ptr<Node2<T>> DoubleList<T>::getNode(size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    std::shared_ptr<Node2<T>> current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}
