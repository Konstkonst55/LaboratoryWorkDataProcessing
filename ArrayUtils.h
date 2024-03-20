#pragma once

#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <vector>
#include <string>
#include "Point.h"
#include <functional>
#include "PhoneBook.h"
#include "MathUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <iostream>

using namespace std;

using sortersFType = function<void(int*, int, int*, int*)>;
using fillersFType = function<void(int*, int)>;

using searchersFType = function<void(int*, int, int, int*)>;

void FillInc(int arr[], int len);
void FillDec(int arr[], int len);
void FillRand(int arr[], int len);

int CheckSum(int arr[], int len);
void PrintMas(int arr[], int len);
int RunNumber(int arr[], int len);
void swap(int* a, int* b);

void SelectSort(int arr[], int len, int* m, int* c);
void SelectSortBetter(int arr[], int len, int* m, int* c);

void BubbleSort(int arr[], int len, int* m, int* c);
void BubbleSortBetter(int arr[], int len, int* m, int* c);

void ShakerSort(int arr[], int len, int* m, int* c);

void InsertSort(int arr[], int len, int* m, int* c);
void InsertSortWithStep(int arr[], int len, int* m, int* c, int step);

void ShellSort(int arr[], int len, int* m, int* c);
void ShellSortKnut(int arr[], int len, int* m, int* c);

string getKnutSteps(int len);
string getImpSteps(int len);

bool ComparePhoneBooks(const PhoneBook& pb1, const PhoneBook& pb2);
void ShellSortKnutPhoneBook(PhoneBook arr[], int len, bool (*comparator)(const PhoneBook&, const PhoneBook&) = ComparePhoneBooks, bool isAsc = true);
void PrintPhoneBook(PhoneBook arr[], int len);
int BSearchPhoneBook(PhoneBook arr[], int len, string key, string field = "surname");
vector<int> BSearchAllPhoneBookSurname(PhoneBook arr[], int len, string key);

int BSearch(int arr[], int len, int key, int* c);
int BSearchImp(int arr[], int len, int key, int* c);
vector<int> BSearchAll(int arr[], int len, int key, int* c);
vector<int> BSearchAllImp(int arr[], int len, int key, int* c);

vector<vector<string>> GetSortData(const vector<sortersFType>& sorters, const vector<fillersFType>& fillers, const int min, const int max, const int step, int (*ct)(int) = nullptr, int (*mt)(int) = nullptr, const bool allowN = true, const bool allowMC = true);
vector<vector<string>> GetSearchData(const vector<searchersFType>& searchers, const int min, const int max, const int step, int (*ct)(int) = nullptr, const bool allowN = false);

vector<Point> CreatePoints(const vector<vector<string>>& data, const int startRow = 0, const int colX = 0, const int colY = 1);
vector<vector<string>> VerticalVectorVectorConcatenate(const vector<vector<string>>&vec1, const vector<vector<string>>&vec2, const int vec1Start = 0, const int vec2Start = 0);

#endif // !ARRAY_UTILS_H