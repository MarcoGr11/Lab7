#include <iostream>
#include <memory> // Для використання умних вказівників

// Структура, що представляє вузол списку
template<typename T>
struct Node{
    T data; // Дані, що зберігаються в вузлі
    std::shared_ptr<Node<T>> next; // Вказівник на наступний вузол у списку

    // Конструктор для створення нового вузла з заданим значенням
    Node(const T& value) : data(value), next(nullptr) {}

};

// Клас для роботи з однозв’язним списком
template<typename T>
class SingleList{
private:
    std::shared_ptr<Node<T>> head; // Вказівник на початок списку
    size_t size; // Розмір списку
public:

    // Конструктор за замовчуванням
    SingleList():head(nullptr),size(0){}

    // Додавання елемента на початок списку
    void pushFront(const T& value);
    
    // Додавання елемента в кінець списку
    void pushBack(const T& value);

    // Видалення першого елемента списку
    void popFront();
    
    // Видалення останнього елемента списку
    void popBack();

    // Перевантаження оператора доступу до елементів за індексом
    T& operator[](size_t index)const;


    // Вставка елемента за заданим індексом
    void insertAt(size_t index,const T& value);
    
    // Видалення елемента за заданим індексом
    void removeAt(size_t index);

    // Перевірка, чи список порожній
    bool isEmpty() const;

    // Отримання розміру списку
    size_t Size() const;

    // Пошук елемента в списку
    bool Find(const T& value)const;

    // Вивід списку у потік
    friend std::ostream& operator<<(std::ostream& os, const SingleList<T> list){
        std::shared_ptr<Node<T>> current = list.head;
        while (current != nullptr){
            os << current->data<< " ";
            current = current->next;
        }
        return os;
    }

};


// Додавання елемента в кінець списку
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

// Додавання елемента на початок списку
template<typename T>
void SingleList<T>::pushFront(const T& value) {
    std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(value);
    newNode->next = std::move(head);
    head = std::move(newNode);
    size++;
}

// Видалення останнього елемента списку
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

// Видалення першого елемента списку
template<typename T>
void SingleList<T>::popFront() {
    if (head == nullptr)
        throw std::out_of_range("List is empty");
    head = std::move(head->next);
    size--;
}

// Отримання елемента списку за індексом
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

// Вставка елемента за заданим індексом
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

// Видалення елемента за заданим індексом
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

// Отримання розміру списку
template<typename T>
size_t SingleList<T>::Size() const {
    return size;
}

// Перевірка, чи список порожній
template<typename T>
bool SingleList<T>::isEmpty() const {
    return size == 0;
}

// Пошук елемента в списку
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
