#pragma once

#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

class Queue {
private:
    Node* _front;
    Node* _back;

    bool IsEmpty(Node* node);
    void Print(Node* node);
    void PrintReverse(Node* node);
    int GetSeries(Node* node);

public:
    Queue();

    void FillInc(int start, int end);
    void FillDec(int start, int end);
    void FillRand(int count, int min, int max);
    int GetSum();
    int GetSeries();
    void Enqueue(int data);
    int Dequeue();
    void Clear();
    bool IsEmpty();
    void Print();
    void PrintReverse();
};

#endif // !QUEUE_H