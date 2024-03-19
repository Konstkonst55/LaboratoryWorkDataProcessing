#pragma once

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <stdlib.h>
#include <math.h>

int GetRandomInt(int min = 0, int max = 9);

int GetCTheorSelectSort(int n);
int GetMTheorSelectSort(int n);

int GetCTheorBubbleSort(int n);
int GetMTheorBubbleSort(int n);

int GetCTheorShakerSort(int n);
int GetMTheorShakerSort(int n);

int GetCTheorInsertSort(int n);
int GetMTheorInsertSort(int n);

int GetCTheorBSearch(int n);
int GetCTheorBSearchImp(int n);

int GetCTheorBSearchAll(int n);
int GetCTheorBSearchAllImp(int n);

#endif // !MATH_UTILS_H
