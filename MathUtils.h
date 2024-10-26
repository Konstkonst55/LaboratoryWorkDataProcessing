#pragma once

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

int GetRandomInt(int min = 0, int max = 9);
double GetRandomDouble(double min = 0.0, double max = 9.0);

int GetCTheorSelectSort(int n);
int GetMTheorSelectSort(int n);

int GetCTheorBubbleSort(int n);
int GetMTheorBubbleSort(int n);

int GetCTheorShakerSort(int n);
int GetMTheorShakerSort(int n);

int GetCTheorInsertSort(int n);
int GetMTheorInsertSort(int n);

int GetCTheorShellSort(int n);
int GetMTheorShellSort(int n);

int GetCTheorBSearch(int n);
int GetCTheorBSearchImp(int n);

int GetCTheorBSearchAll(int n);
int GetCTheorBSearchAllImp(int n);

int GetCTheorHeapSort(int n);
int GetMTheorHeapSort(int n);

int GetCTheorQuickSort(int n);
int GetMTheorQuickSort(int n);

int GetCTheorMergeSort(int n);
int GetMTheorMergeSort(int n);

#endif // !MATH_UTILS_H
