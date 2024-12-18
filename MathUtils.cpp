
#include "MathUtils.h"
#include <stdlib.h>
#include <math.h>
#include <random>

int GetRandomInt(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distr(min, max);

	return distr(gen);
}

double GetRandomDouble(double min, double max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distr(min, max);

	return distr(gen);
}

int GetCTheorSelectSort(int n) {
	return (n * n - n) / 2;
}

int GetMTheorSelectSort(int n) {
	return 3 * (n - 1);
}

int GetCTheorBubbleSort(int n) {
	return (n * n - n) / 2;
}

int GetMTheorBubbleSort(int n) {
	return 3 * GetCTheorBubbleSort(n);
}

int GetCTheorShakerSort(int n) {
	return (n * n - n) / 2;
}

int GetMTheorShakerSort(int n) {
	return 3 * GetCTheorShakerSort(n);
}

int GetCTheorInsertSort(int n) {
	return (n * n - n) / 4;
}

int GetMTheorInsertSort(int n) {
	return GetCTheorInsertSort(n) + n - 1;
}

int GetCTheorShellSort(int n) {
	return pow(n, 1.2) / 2;
}

int GetMTheorShellSort(int n) {
	return pow(n, 1.2) / 2;
}

int GetCTheorBSearch(int n) {
	return 2 * log2(n);
}

int GetCTheorBSearchImp(int n) {
	return log2(n);
}

// ------------- ? ------------- //
int GetCTheorBSearchAll(int n) {
	return 2 * log2(n);
}

// ------------- ? ------------- //
int GetCTheorBSearchAllImp(int n) {
	return log2(n);
}

int GetCTheorHeapSort(int n) {
	return 2 * n * log2(n) + n + 2;
}

int GetMTheorHeapSort(int n) {
	return n * log2(n) + 6.5 * n - 4;
}

int GetCTheorQuickSort(int n) {
	return n * log2(n);
}

int GetMTheorQuickSort(int n) {
	return n * log2(n);
}

int GetCTheorMergeSort(int n) {
	return n * log2(n);
}

int GetMTheorMergeSort(int n) {
	return n * log2(n);
}
