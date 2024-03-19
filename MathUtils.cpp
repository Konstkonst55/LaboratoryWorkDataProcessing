
#include "MathUtils.h"

int GetRandomInt(int min, int max) {
	return min + rand() % (max - min + 1);
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

int GetCTheorBSearch(int n) {
	return 2 * log2(n);
}

int GetCTheorBSearchImp(int n) {
	return log2(n);
}

// ---- ? ---- //
int GetCTheorBSearchAll(int n) {
	return 2 * log2(n);
}

// ---- ? ---- //
int GetCTheorBSearchAllImp(int n) {
	return log2(n);
}