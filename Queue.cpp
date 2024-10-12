
#include "Queue.h"
#include <random>
#include <iostream>

using namespace std;

Queue::Queue() : front(nullptr), back((Node*)&(front)) { }

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
    Node* temp = front;

    while (!IsEmpty(temp)) {
        sum += temp->data;
        temp = temp->next;
    }

    return sum;
}

int Queue::GetSeries() {
    return GetSeries(front);
}

void Queue::Enqueue(int data) {
    Node* newNode = new Node(data);

    if (IsEmpty(back)) {
        front = back = newNode;
        return;
    }

    back->next = newNode;
    back = newNode;
}

int Queue::Dequeue() {
    if (IsEmpty()) {
        return -1;
    }

    Node* temp = front;
    int data = temp->data;
    front = front->next;

    if (IsEmpty()) {
        back = nullptr;
    }

    delete temp;
    return data;
}

void Queue::Clear() {
    Node* current = front;

    while (!IsEmpty(current)) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    front = nullptr;
    back = nullptr;
}

bool Queue::IsEmpty() {
    return front == nullptr;
}

void Queue::Print() {
    Print(front);
}

void Queue::PrintReverse() {
    PrintReverse(front);
}
