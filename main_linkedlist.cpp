#include <iostream>

#include "LinkedList.h"
using namespace std;
int main()
{
    LinkedList<int> *llist = new LinkedList<int>;

    llist->insertAtTheFront(1);
    llist->insertAtTheEnd(2);
    llist->insertAtTheEnd(4);
    llist->insertAtTheEnd(5);

    llist->print();

    cout<<"\n"<<llist->getNodeAtIndex(3)->data;



    return 0;
}
