#include <iostream>
#include "list.h"

int main() {
    LinkedList<int> list1;

    for (int i = 0; i < 12; i++) {
        list1.push_tail(i);
    }

    std::cout << "List1: ";
    list1.print();

    list1.pop_head();
    list1.delete_node(6);
    list1.delete_node(3);

    std::cout << "List1(changed): ";
    list1.print();


    LinkedList<int> list2(15, 0, 130);

    std::cout << "List2: ";
    list2.print();


    LinkedList<float> list3(5, 1, 2);

    std::cout << "List3: ";
    list3.print();


    LinkedList<int> list4;

    for (int i = 0; i < 6; i++) {
        list4.push_head(i);
    }

    std::cout << "List4: ";
    list4.print();


    LinkedList<int> list_er;

    for (int i = 1; i <= 30; i++) {
        list_er.push_tail(i);
    }

    eratosthenes(list_er);

    std::cout << "List_er: ";
    list_er.print();


    LinkedList<int> list5;

    for (int i = 1; i <= 30; i++) {
        list5.push_tail(i);
    }

    LinkedList<int> temp(list5);

    for (int i = 0; i < list5.count(); i++) {
        if (!is_prime(list5[i])) {
            temp.delete_node(list5[i]);
        }
    }
    
    list5 = temp;

    std::cout << "List5: ";
    list5.print();

    LinkedList<int> lst(5, 1, 10);
    LinkedList<int> lst1(3, 1, 4);
    lst.print();
    lst1.print();

    lst.push_head(lst1);
    std::cout << lst.count() << "\n";
    lst.print();
    return 0;
}