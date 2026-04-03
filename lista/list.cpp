#include "lista.h"
#include <iostream>

void displayList(bool success, Alist<short> &shortList);

void checkState(Alist<short> &shortList);

int main()
{
    Alist<short> shortList(3);

    short num;

    int i = 0;

    bool success;

    checkState(shortList);

    num = 10;

    success = shortList.insertFront(num);

    if (success)
        std::cout << "insert front: " << num << std::endl;

    displayList(success, shortList);

    num = 20;

    success = shortList.insertAtIndex(num, i);

    if (success)
        std::cout << "insert index: " << i
                    << ": " << num << std::endl;

    displayList(success, shortList);

    num = 30;

    success = shortList.insertBack(num, i);

    if (success)
        std::cout << "insert back: " << num << std::endl;

    displayAlist(success, shortList);

    return 0;
}

void displayAlist(bool success, Alist<short> &shortList)
{
    short min;

    int cap,
        numVal;
    
    if (success)
    {
        short.display();
        short.getSamallest(min);
        cap = short.getCapacity();
        numVal = short.getNumValues();

        if (numVal > 0)
            std::cout << "capacity: " << cap
                        << "\tnumVal: " << numVal
                        << "\tsmallest: " << min
                        << std::endl;
        else
            std::cout << "capacity: " << cap
                        << "\tnumvalues: " << numVal
                        << std::endl;
    }

    checkState(shortList);
}

void CheckState(Alist <short> &shortList)
{
    if (shortList.isFull())
        std::cerr << "list is full\n\n";
    else if (shortList.isEmpty())
        std::cerr << "List is empty\n\n";
}