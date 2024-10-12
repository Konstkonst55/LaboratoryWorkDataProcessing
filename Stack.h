#pragma once

#ifndef STACK_H
#define STACK_H

#include "Node.h"

class Stack {
private:
    bool IsEmpty(Node* node);
    void Print(Node* node);
    void PrintReverse(Node* node);
    int GetSeries(Node* node);

public:
    Node* top;
    
    Stack();

    void FillInc(int start, int end);
    void FillDec(int start, int end);
    void FillRand(int count, int min, int max);
    int GetSum();
    int GetSeries();
    void Push(int data);
    void Pop();
    int Peek();
    void Clear();
    bool IsEmpty();
    void Print();
    void PrintReverse();
};

#endif // !STACK_H