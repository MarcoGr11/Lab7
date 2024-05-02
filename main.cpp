#include "lab_7dvoz.h"
#include "lab_7odnozv.h"
#include <iostream>

using namespace std;

int main() {
    // Створення однозв'язного списку
    SingleList<int> sList;
    sList.pushBack(10);
    sList.pushBack(20);
    sList.pushFront(5);
    cout << "Single-linked list after adding items: " << sList << std::endl;

    // Видалення елементів
    sList.popFront();
    sList.popBack();
    cout << "Single-linked list after deleting items: " << sList << std::endl;

    // Доступ до елементу за індексом
    if (!sList.isEmpty()) {
        cout << "Element at position 0: " << sList[0] << std::endl;
    }

    // Створення двозв'язного списку
    DoubleList<int> dList;
    dList.pushBack(30);
    dList.pushBack(40);
    dList.pushFront(25);
    cout << " A two-way list after adding items:" << dList << std::endl;

    // Видалення елементів
    dList.popFront();
    dList.popBack();
    cout << "A double-valued list after deleting items: " << dList << std::endl;

    // Доступ до елементу за індексом
    if (!dList.isEmpty()) {
        cout << "Element at position 0: " << dList[0] << std::endl;
    }

    return 0;
}
