
#include "Queue.h"
#include <random>
#include <iostream>

using namespace std;

Queue::Queue() : _front(nullptr), _back(nullptr) { }

bool Queue::IsEmpty(Node* node) {
    return node == nullptr;
}

void Queue::Print(Node* node) {
    if (IsEmpty(node)) {
        return;
    }

    cout << "[" << node->data << "] ";
    Print(node->next);
}

void Queue::PrintReverse(Node* node) {
    if (IsEmpty(node)) {
        return;
    }

    PrintReverse(node->next);
    cout << "[" << node->data << "] ";
}

int Queue::GetSeries(Node* node) {
    if (IsEmpty(node)) {
        return 0;
    }

    int count = 1;
    int prev = node->data;
    node = node->next;
    
    while (!IsEmpty(node)) {
        if (node->data <= prev) {
            count++;
            prev = node->data;
        }
    
        node = node->next;
    }
    
    return count;
}

void Queue::FillInc(int start, int end) {
    for (int i = start; i <= end; i++) {
        Enqueue(i);
    }
}

void Queue::FillDec(int start, int end) {
    for (int i = start; i >= end; i--) {
        Enqueue(i);
    }
}

void Queue::FillRand(int count, int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);

    for (int i = 0; i < count; i++) {
        Enqueue(dis(gen));
    }
}

int Queue::GetSum() {
    int sum = 0;
    Node* temp = _front;

    while (!IsEmpty(temp)) {
        sum += temp->data;
        temp = temp->next;
    }

    return sum;
}

int Queue::GetSeries() {
    return GetSeries(_front);
}

void Queue::Enqueue(int data) {
    Node* newNode = new Node(data);

    if (IsEmpty(_back)) {
        _front = _back = newNode;
        return;
    }

    _back->next = newNode;
    _back = newNode;
}

int Queue::Dequeue() {
    if (IsEmpty()) {
        return -1;
    }

    Node* temp = _front;
    int data = temp->data;
    _front = _front->next;

    if (IsEmpty()) {
        _back = nullptr;
    }

    delete temp;
    return data;
}

void Queue::Clear() {
    Node* current = _front;

    while (!IsEmpty(current)) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    _front = nullptr;
    _back = nullptr;
}

bool Queue::IsEmpty() {
    return _front == nullptr;
}

void Queue::Print() {
    Print(_front);
}

void Queue::PrintReverse() {
    PrintReverse(_front);
}
