
#include "ListUtils.h"
#include <iostream>

using namespace std;

#pragma region Templates

template Node16* PushStack(Node16* top, int data);
template Node32* PushStack(Node32* top, int data);
template Node16* FillStackIncreasing(int n);
template Node32* FillStackIncreasing(int n);
template Node16* FillStackDecreasing(int n);
template Node32* FillStackDecreasing(int n);
template Node16* FillStackRandom(int n);
template Node32* FillStackRandom(int n);
template Node* PushQueue(Node** front, Node** rear, int data);
template Node16* PushQueue(Node16** front, Node16** rear, int data);
template Node32* PushQueue(Node32** front, Node32** rear, int data);
template void FillQueueIncreasing(Node** front, Node** rear, int n);
template void FillQueueIncreasing(Node16** front, Node16** rear, int n);
template void FillQueueIncreasing(Node32** front, Node32** rear, int n);
template void FillQueueDecreasing(Node** front, Node** rear, int n);
template void FillQueueDecreasing(Node16** front, Node16** rear, int n);
template void FillQueueDecreasing(Node32** front, Node32** rear, int n);
template void FillQueueRandom(Node** front, Node** rear, int n);
template void FillQueueRandom(Node16** front, Node16** rear, int n);
template void FillQueueRandom(Node32** front, Node32** rear, int n);
template void QueueFillInc(int n, Node16* (&head), Node16* (&tail));
template void QueueFillInc(int n, Node32* (&head), Node32* (&tail));
template void QueueFillDec(int n, Node16* (&head), Node16* (&tail));
template void QueueFillDec(int n, Node32* (&head), Node32* (&tail));
template void QueueFillRand(int n, Node16* (&head), Node16* (&tail));
template void QueueFillRand(int n, Node32* (&head), Node32* (&tail));
template void PrintList(Node16* node);
template void PrintList(Node32* node);
template int SumList(Node16* node);
template int SumList(Node32* node);
template int CountSeries(Node16* node);
template int CountSeries(Node32* node);
template int CountNodes(Node16* node);
template int CountNodes(Node32* node);
template void DeleteAll(Node** head);
template void DeleteAll(Node16** head);
template void DeleteAll(Node32** head);
template void DeleteAll(Node** front, Node** rear);
template void DeleteAll(Node16** front, Node16** rear);
template void DeleteAll(Node32** front, Node32** rear);
template void DeleteList(Node16* (&head), Node16* (&tail));
template void DeleteList(Node32* (&head), Node32* (&tail));

#pragma endregion

template<typename T> T* PushStack(T* top, int data) {
    T* tmp = new T;
    tmp->data = data;
    tmp->next = top;

    return tmp;
}

template<typename T> T* FillStackIncreasing(int n) {
    T* top = nullptr;

    for (int i = 1; i <= n; ++i) {
        top = PushStack(top, i);
    }

    return top;
}

template<typename T> T* FillStackDecreasing(int n) {
    T* top = nullptr;

    for (int i = n; i > 0; --i) {
        top = PushStack(top, i);
    }

    return top;
}

template<typename T> T* FillStackRandom(int n) {
    T* top = nullptr;

    for (int i = 0; i < n; ++i) {
        top = PushStack(top, rand() % 100);
    }

    return top;
}

template<typename T> T* PushQueue(T** front, T** rear, int data) {
    T* tmp = new T;
    tmp->data = data;
    tmp->next = nullptr;

    if (*rear == nullptr) {
        *front = *rear = tmp;
    }
    else {
        (*rear)->next = tmp;
        *rear = tmp;
    }

    return tmp;
}

template<typename T> void FillQueueIncreasing(T** front, T** rear, int n) {
    for (int i = 1; i <= n; ++i) {
        PushQueue(front, rear, i);
    }
}

template<typename T> void FillQueueDecreasing(T** front, T** rear, int n) {
    for (int i = n; i > 0; --i) {
        PushQueue(front, rear, i);
    }
}

template<typename T> void FillQueueRandom(T** front, T** rear, int n) {
    srand(time(0));

    for (int i = 0; i < n; ++i) {
        PushQueue(front, rear, rand() % 100);
    }
}

template<typename T> void QueueFillInc(int n, T* (&head), T* (&tail)) {
    int i = 1;
    T* p;
    head = tail = new T;
    head->next = tail->next = 0;
    tail->data = i;
    i++;

    do
    {
        p = new T;
        p->data = i;
        tail->next = p;
        tail = p;
        i++;

    } while (i <= n);

    tail->next = 0;
}

template<typename T> void QueueFillDec(int n, T* (&head), T* (&tail)) {
    int i = n;
    T* p;
    head = tail = new T;
    head->next = tail->next = 0;
    tail->data = i;
    i--;

    do
    {
        p = new T;
        p->data = i;
        tail->next = p;
        tail = p;
        i--;

    } while (i > 0);

    tail->next = 0;
}

template<typename T> void QueueFillRand(int n, T* (&head), T* (&tail)) {
    int i = 1;
    T* p;
    head = tail = new T;
    head->next = tail->next = 0;
    tail->data = rand() % (n * 2);
    i++;

    do
    {
        p = new T;
        p->data = rand() % (n * 2);
        tail->next = p;
        tail = p;
        i++;

    } while (i <= n);

    tail->next = 0;
}

template<typename T> void PrintList(T* node) {
    while (node != nullptr) {
        cout << "[" << node->data << "]" << " ";
        node = node->next;
    }

    cout << endl;
}

template<typename T> int SumList(T* node) {
    int sum = 0;

    while (node != nullptr) {
        sum += node->data;
        node = node->next;
    }

    return sum;
}

template<typename T> int CountSeries(T* node) {
    if (node == nullptr) return 0;
    int count = 1;
    int prev = node->data;
    node = node->next;

    while (node != nullptr) {
        if (node->data < prev) {
            ++count;
            prev = node->data;
        }
        node = node->next;
    }

    return count;
}

template<typename T> int CountNodes(T* head) {
    int count = 0;
    T* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

template<typename T> void DeleteAll(T** head) {
    T* current = *head;
    T* next;

    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }

    *head = nullptr;
}

template<typename T> void DeleteAll(T** front, T** rear) {
    while (*front != nullptr) {
        T* temp = *front;
        *front = (*front)->next;
        delete temp;
    }

    *rear = nullptr;
}

template<typename T> void DeleteList(T* (&head), T* (&tail)) {
    T* p, * t;

    for (p = head; p; p = t)
    {
        t = p->next;
        delete p;
    }

    head = tail = NULL;
}

void PrintListForward(Node* node) {
    if (node == nullptr) return;
    cout << "[" << node->data << "] ";
    PrintListForward(node->next);
}

void PrintListBackward(Node* node) {
    if (node == nullptr) return;
    PrintListBackward(node->next);
    cout << "[" << node->data << "] ";
}