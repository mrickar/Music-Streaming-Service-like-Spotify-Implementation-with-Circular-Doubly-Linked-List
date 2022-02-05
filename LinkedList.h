#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse = false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template <class T>
LinkedList<T>::LinkedList()
{
    /* TODO */
    head = NULL;
    size = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    /* TODO */
    head = NULL;
    size = obj.size;
    Node<T> *headCur;
    Node<T> *headObj = obj.getFirstNode();
    if (headObj == NULL)
    {
        return;
    }
    for (int i = 0; i < size; i++)
    {
        Node<T> *tmp = new Node<T>(headObj->data);

        if (!head)
        {
            head = tmp;
            headCur = head;
            headObj = headObj->next;

            continue;
        }
        headCur->next = tmp;
        tmp->prev = headCur;

        headCur = headCur->next;
        headObj = headObj->next;
    }

    head->prev = headCur;
    headCur->next = head;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    /* TODO */
    Node<T> *tmp;
    for (int i = 0; i < size; i++)
    {
        tmp = head->next;
        delete head;
        head = tmp;
    }
    head = NULL;
}

template <class T>
int LinkedList<T>::getSize() const
{
    /* TODO */
    return size;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    /* TODO */
    return getFirstNode() ? false : true;
}

template <class T>
bool LinkedList<T>::contains(Node<T> *node) const
{
    /* TODO */
    if (getFirstNode() == NULL)
    {
        return false;
    }
    Node<T> *headCur = getFirstNode();
    for (int i = 0; i < size; i++)
    {
        if (headCur == node)
        {
            return true;
        }
        headCur = headCur->next;
    }
    return false;
}

template <class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    return head;
}

template <class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    if (!getFirstNode())
    {
        return NULL;
    }
    return getFirstNode()->prev;
}

template <class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    if (getFirstNode() == NULL)
    {
        return NULL;
    }
    Node<T> *headCur = getFirstNode();
    for (int i = 0; i < size; i++)
    {
        if (headCur->data == data)
        {
            return headCur;
        }
        headCur = headCur->next;
    }
    return NULL;
}

template <class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */

    if (index < 0 || index >= size || getFirstNode() == NULL)
    {
        return NULL;
    }
    Node<T> *headCur = getFirstNode();
    for (int i = 0; i < index; i++)
    {
        headCur = headCur->next;
    }
    return headCur;
}

template <class T>
void LinkedList<T>::insertAtTheFront(const T &data)
{
    /* TODO */
    size++;

    if (getFirstNode() == NULL)
    {

        Node<T> *tmp = new Node<T>(data);

        head = tmp;
        tmp->next = tmp;
        tmp->prev = tmp;
        return;
    }
    Node<T> *tmp = new Node<T>(data, getFirstNode()->prev, getFirstNode());
    tmp->prev->next = tmp;
    tmp->next->prev = tmp;
    head = tmp;
}

template <class T>
void LinkedList<T>::insertAtTheEnd(const T &data)
{
    /* TODO */
    size++;

    if (getFirstNode() == NULL)
    {

        Node<T> *tmp = new Node<T>(data);

        head = tmp;
        tmp->next = tmp;
        tmp->prev = tmp;
        return;
    }

    Node<T> *tmp = new Node<T>(data, getLastNode(), getFirstNode());
    tmp->next->prev = tmp;
    tmp->prev->next = tmp;
}

template <class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
    if (contains(node) == false)
    {
        return;
    }
    Node<T> *tmp = new Node<T>(data, node, node->next);
    tmp->next->prev = tmp;
    tmp->prev->next = tmp;
    size++;
}

template <class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k)
{
    /* TODO */
    if (k < 2 || getFirstNode() == NULL)
    {
        return;
    }
    Node<T> *headCur = getFirstNode();

    for (int i = 0, cnt = 1; i < size; i++, cnt++)
    {
        cnt %= k;
        if (cnt == k - 1)
        {
            Node<T> *tmp = new Node<T>(data, headCur, headCur->next);
            tmp->prev->next = tmp;
            tmp->next->prev = tmp;
            size++;
        }
        headCur = headCur->next;
    }
}

template <class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    /* TODO */
    if (getFirstNode() == NULL || contains(node) == false)
    {
        return;
    }

    size--;

    Node<T> *headCur = getFirstNode();
    if (node == getFirstNode())
    {
        if (size == 0)
        {
            delete head;
            head = NULL;
            return;
        }
        headCur = headCur->next;

        headCur->prev = getFirstNode()->prev;
        getFirstNode()->prev->next = headCur;

        delete getFirstNode();

        head = headCur;
    }
    else
    {
        node->next->prev = node->prev;
        node->prev->next = node->next;
        delete node;
    }
}

template <class T>
void LinkedList<T>::removeNode(const T &data)
{
    /* TODO */
    while (Node<T> *deletedNode = getNode(data))
    {
        removeNode(deletedNode);
    }
}

template <class T>
void LinkedList<T>::removeAllNodes()
{
    /* TODO */
    if (getFirstNode() == NULL)
    {
        return;
    }

    Node<T> *headCur = getFirstNode();
    Node<T> *tmp;
    for (int i = 0; i < size; i++)
    {
        tmp = headCur->next;
        delete headCur;
        headCur = tmp;
    }
    size = 0;
    head = NULL;
}

template <class T>
void LinkedList<T>::removeEveryKthNode(int k)
{
    /* TODO */
    if (getFirstNode() == NULL || k < 2)
    {
        return;
    }

    Node<T> *headCur = getFirstNode()->next;

    for (int i = 2; headCur != getFirstNode(); i++)
    {
        if (i == k)
        {
            Node<T> *deletedNode = headCur;
            headCur = headCur->next;
            removeNode(deletedNode);
            i = 0;
            continue;
        }
        headCur = headCur->next;
    }
}

template <class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2)
{
    /* TODO */
    if (!contains(node1) || !contains(node2) || node1 == node2)
    {
        return;
    }

    if (node1->next == node2)
    {
        node1->next = node2->next;
        node2->next = node1;

        node2->prev = node1->prev;
        node1->prev = node2;

        node2->prev->next = node2;

        node1->next->prev = node1;
    }
    else if (node2->next == node1)
    {
        node2->next = node1->next;
        node1->next = node2;

        node1->prev = node2->prev;
        node2->prev = node1;

        node1->prev->next = node1;

        node2->next->prev = node2;
    }
    else
    {
        Node<T> *tmp = node2->next;
        node2->next = node1->next;
        node1->next = tmp;

        tmp = node2->prev;
        node2->prev = node1->prev;
        node1->prev = tmp;

        node2->next->prev = node2;
        node2->prev->next = node2;

        node1->next->prev = node1;
        node1->prev->next = node1;
    }

    if (node1 == getFirstNode())
    {
        head = node2;
    }
    else if (node2 == getFirstNode())
    {
        head = node1;
    }
}

template <class T>
void LinkedList<T>::shuffle(int seed)
{
    /* TODO */
    for (int i = 0; i < size; i++)
    {
        swap(getNodeAtIndex(i), getNodeAtIndex((i * i + seed) % size));
    }
}

template <class T>
void LinkedList<T>::print(bool reverse) const
{
    if (this->isEmpty())
    {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse)
    {
        // traverse in reverse order (last node to first node).

        Node<T> *node = this->getLastNode();

        do
        {
            std::cout << *node << std::endl;
            node = node->prev;
        } while (node != this->getLastNode());
    }
    else
    {
        // traverse in normal order (first node to last node).

        Node<T> *node = this->getFirstNode();

        do
        {
            std::cout << *node << std::endl;
            node = node->next;
        } while (node != this->getFirstNode());
    }
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
    if (&rhs == this)
    {
        return *this;
    }

    removeAllNodes();
    size = rhs.size;
    if (size == 0)
    {
        head = NULL;
        return *this;
    }

    Node<T> *rhsHead = rhs.getFirstNode();
    Node<T> *headCur;
    for (int i = 0; i < size; i++)
    {
        Node<T> *tmp = new Node<T>(rhsHead->data);

        if (i == 0)
        {
            head = tmp;
            headCur = head;
            rhsHead = rhsHead->next;
            continue;
        }
        headCur->next = tmp;
        tmp->prev = headCur;

        headCur = headCur->next;
        rhsHead = rhsHead->next;
    }
    headCur->next = head;
    head->prev = headCur;
    return *this;
}

#endif //LINKEDLIST_H
