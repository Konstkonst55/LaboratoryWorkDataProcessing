#pragma once

#ifndef LIST_UTILS_H
#define LIST_UTILS_H

#include "Node.h"

template<typename T> T* PushStack(T* top, int data);
template<typename T> T* FillStackIncreasing(int n);
template<typename T> T* FillStackDecreasing(int n);
template<typename T> T* FillStackRandom(int n);

template<typename T> T* PushQueue(T** front, T** rear, int data);
template<typename T> void FillQueueIncreasing(T** front, T** rear, int n);
template<typename T> void FillQueueDecreasing(T** front, T** rear, int n);
template<typename T> void FillQueueRandom(T** front, T** rear, int n);

template<typename T> void QueueFillInc(int n, T* (&head), T* (&tail));
template<typename T> void QueueFillDec(int n, T* (&head), T* (&tail));
template<typename T> void QueueFillRand(int n, T* (&head), T* (&tail));

template<typename T> void PrintList(T* node);
template<typename T> int SumList(T* node);
template<typename T> int CountSeries(T* node);
template<typename T> int CountNodes(T* head);

template<typename T> void DeleteAll(T** head);
template<typename T> void DeleteAll(T** front, T** rear);
template<typename T> void DeleteList(T* (&head), T* (&tail));

void PrintListForward(Node* node);

void PrintListBackward(Node* node);

#endif // !LIST_UTILS_H