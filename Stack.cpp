
#include "Stack.h"
#include <random>
#include <iostream>

using namespace std;

Stack::Stack() : _top(nullptr) { }

bool Stack::IsEmpty(Node* node) {
    return node == nullptr;
}

void Stack::Print(Node* node) {
    if (IsEmpty(node)) {
        return;
    }

    cout << "[" << node->data << "] ";
    Print(node->next);
}

void Stack::PrintReverse(Node* node) {
    if (IsEmpty(node)) {
        return;
    }

    PrintReverse(node->next);
    cout << "[" << node->data << "] ";
}

int Stack::GetSeries(Node* node) {
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

void Stack::FillInc(int start, int end) {
    for (int i = start; i <= end; i++) {
        Push(i);
    }
}

void Stack::FillDec(int start, int end) {
    for (int i = start; i >= end; i--) {
        Push(i);
    }
}

void Stack::FillRand(int count, int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);

    for (int i = 0; i < count; i++) {
        Push(dis(gen));
    }
}

int Stack::GetSum() {
    int sum = 0;
    Node* temp = _top;

    while (!IsEmpty(temp)) {
        sum += temp->data;
        temp = temp->next;
    }

    return sum;
}

int Stack::GetSeries() {
    return GetSeries(_top);
}

void Stack::Push(int data) {
    Node* newNode = new Node(data);
    newNode->next = _top;
    _top = newNode;
}

void Stack::Pop() {
    if (IsEmpty()) {
        return;
    }

    Node* temp = _top;
    _top = _top->next;
    delete temp;
}

int Stack::Peek() {
    return IsEmpty() ? -1 : _top->data;
}

void Stack::Clear() {
    Node* current = _top;

    while (!IsEmpty(current)) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    _top = nullptr;
}

bool Stack::IsEmpty() {
    return _top == nullptr;
}

void Stack::Print() {
    Print(_top);
}

void Stack::PrintReverse() {
    PrintReverse(_top);
}