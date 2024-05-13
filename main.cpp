#include "lab_7dvoz.h"
#include "lab_7odnozv.h"
#include <iostream>

using namespace std;

int main() {
    SingleList<int> sList;
    sList.pushBack(10);
    sList.pushBack(20);
    sList.pushFront(5);
    cout << "Single-linked list after adding items: " << sList << endl;

    // видал елеметн 
    sList.popFront();
    sList.popBack();
    cout << "Single-linked list after deleting items: " << sList << endl;

    // доступ до елемент за індекс
    if (!sList.isEmpty()) {
        cout << "Element at position 0: " << sList[0] << endl;
    }
    DoubleList<int> dList;
    dList.pushBack(30);
    dList.pushBack(40);
    dList.pushFront(25);
    cout << " A two-way list after adding items:" << dList <<endl;

    // видал елемент
    dList.popFront();
    dList.popBack();
    cout << "A double-valued list after deleting items: " << dList << endl;

    // доступ  елемент за індекс
    if (!dList.isEmpty()) {
        cout << "Element at position 0: " << dList[0] << endl;
    }

    return 0;
}
