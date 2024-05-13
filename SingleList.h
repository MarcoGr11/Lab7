#include <iostream>
#include <memory>

template<typename T>
struct Node{
    T data; 
    std::shared_ptr<Node<T>> next; 

    Node(const T& value) : data(value), next(nullptr) {}

};


template<typename T>
class SingleList{
private:
    std::shared_ptr<Node<T>> head; 
    size_t size;
public:

    SingleList():head(nullptr),size(0){}

    // дод елемент на поч 
    void pushFront(const T& value);
    
    // дод елемент в кінець 
    void pushBack(const T& value);

    // вид 1 елемент 
    void popFront();
    
    // вид остан елемент
    void popBack();

    // перевантаж оператор доступ до елемент  індекс
    T& operator[](size_t index)const;


    void insertAt(size_t index,const T& value);
    
    void removeAt(size_t index);

    bool isEmpty() const;

    size_t Size() const;

    bool Find(const T& value)const;

    friend std::ostream& operator<<(std::ostream& os, const SingleList<T> list){
        std::shared_ptr<Node<T>> current = list.head;
        while (current != nullptr){
            os << current->data<< " ";
            current = current->next;
        }
        return os;
    }

};


// дод елемент в кінець 
template<typename T>
void SingleList<T>::pushBack(const T& value) {
    std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(value);
    if (head == nullptr) {
        head = std::move(newNode);
    } else {
        std::shared_ptr<Node<T>> current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = std::move(newNode);
    }
    size++;
}

// додав елемент на початок 
template<typename T>
void SingleList<T>::pushFront(const T& value) {
    std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(value);
    newNode->next = std::move(head);
    head = std::move(newNode);
    size++;
}

// вид останнього елемента 
template<typename T>
void SingleList<T>::popBack() {
    if (head == nullptr)
        throw std::out_of_range("List is empty");
    if (head->next == nullptr) {
        head.reset();
    } else {
        std::shared_ptr<Node<T>> current = head;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        current->next.reset();
    }
    size--;
}

// вид 1 елемента 
template<typename T>
void SingleList<T>::popFront() {
    if (head == nullptr)
        throw std::out_of_range("List is empty");
    head = std::move(head->next);
    size--;
}

// отрим елемент індексом
template<typename T>
T& SingleList<T>::operator[](size_t index) const {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    std::shared_ptr<Node<T>> current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

// вставка елемента заданим  індекс
template<typename T>
void SingleList<T>::insertAt(size_t index, const T& value) {
    if (index > size)
        throw std::out_of_range("Index out of range");
    if (index == 0) {
        pushFront(value);
    } else {
        std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(value);
        std::shared_ptr<Node<T>> current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        size++;
    }
}

// вид елемент за заданим індексом
template<typename T>
void SingleList<T>::removeAt(size_t index) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    if (index == 0) {
        popFront();
    } else {
        std::shared_ptr<Node<T>> current = head;
        for (size_t i = 0; i < index - 1; ++i) {
            current = current->next;
        }
        current->next = current->next->next;
        size--;
    }
}

template<typename T>
size_t SingleList<T>::Size() const {
    return size;
}
// перевір чи є порожн
template<typename T>
bool SingleList<T>::isEmpty() const {
    return size == 0;
}
template<typename T>
bool SingleList<T>::Find(const T& value) const {
    std::shared_ptr<Node<T>> current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}
