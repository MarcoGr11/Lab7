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

    // Додавання елемента в кінець списку
    void pushBack(const T& value);
    
    // Додавання елемента на початок списку
    void pushFront(const T& value);

    // Видалення останнього елемента списку
    void popBack();
    
    // Видалення першого елемента списку
    void popFront();


    // Вставка елемента за заданим індексом
    void insertAt(size_t index, const T& value);
    
    // Видалення елемента за заданим індексом
    void removeAt(size_t index);

    size_t Size() const { return size; }
    
    bool isEmpty() const { return size == 0; }

    bool Find(const T& value) const;

    // Отримання елемента списку за індексом
    T& operator[](size_t index) const;
    // Вивід списку у потік
    friend std::ostream& operator<<(std::ostream& os, const DoubleList<T>& list) {
        std::shared_ptr<Node2<T>> current = list.head;
        while (current != nullptr) {
            os << current->data << " ";
            current = current->next;
        }
        return os;
    }

};

// Додавання елемента в кінець списку
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

// Додавання елемента на початок списку
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

// Видалення останнього елемента списку
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

// Видалення першого елемента списку
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

// Вставка елемента за заданим індексом
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

// Видалення елемента за заданим індексом
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

// Пошук елемента в списку
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

// Отримання елемента списку за індексом
template<typename T>
T& DoubleList<T>::operator[](size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    std::shared_ptr<Node2<T>> current = getNode(index);
    return current->data;
}

// Отримання вузла списку за індексом
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
