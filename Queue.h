#pragma once

#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

class Queue {
private:
    bool IsEmpty(Node* node);
    void Print(Node* node);
    void PrintReverse(Node* node);
    int GetSeries(Node* node);

public:
    Node* front;
    Node* back;

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

struct QueueClean {
    Node* head;
    Node* tail;
};

struct Queue16
{
    Node16* head;
    Node16* tail;
};

struct Queue32
{
    Node32* head;
    Node32* tail;
};

#endif // !QUEUE_H