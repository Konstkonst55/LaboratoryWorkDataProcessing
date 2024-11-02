
#include "ArrayUtils.h"
#include "MathUtils.h"
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <random>

void FillInc(int arr[], int len) {
	for (int i = 0; i < len; i++) arr[i] = i + 1;
}

void FillDec(int arr[], int len) {
	for (int i = 0; i < len; i++) arr[i] = len - i;
}

void FillRand(int arr[], int len) {
	for (int i = 0; i < len; i++) arr[i] = GetRandomInt(0, len * 2);
}

void FillRandUniq(int arr[], int len) {
	std::vector<int> numbers;
	numbers.reserve(len);

	for (int i = 0; i < len; ++i) numbers.push_back(i);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(numbers.begin(), numbers.end(), gen);

	for (int i = 0; i < len; ++i) arr[i] = numbers[i];
}

int CheckSum(int arr[], int len) {
	int sum = 0;

	for (int i = 0; i < len; i++) sum += arr[i];

	return sum;
}

int RunNumber(int arr[], int len) {
	int count = 0;

	for (int i = 0; i < len; i++) if (arr[i] > arr[i + 1]) count++;

	return count;
}

void PrintMas(int arr[], int len) {
	for (int i = 0; i < len; i++) printf("[%d] ", arr[i]);
}

void Swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void SelectSort(int arr[], int len, int* m, int* c) {
	for (int step = 0; step < len - 1; step++) {
		int minIndex = step;

		for (int i = step + 1; i < len; i++) { 
			(*c)++;
			if (arr[i] < arr[minIndex])
				minIndex = i;
		}

		Swap(&arr[minIndex], &arr[step]); (*m) += 3;
	}
}

void SelectSortBetter(int arr[], int len, int* m = 0, int* c = 0) {
	bool changed;

	for (int step = 0; step < len - 1; step++) {
		int minIndex = step;
		changed = false;

		for (int i = step + 1; i < len; i++) {
			(*c)++;
			if (arr[i] < arr[minIndex]) {
				minIndex = i;
				changed = true;
			}
		}

		if (changed) {
			Swap(&arr[minIndex], &arr[step]);
			(*m) += 3;
		}
	}
}

void BubbleSort(int arr[], int len, int* m, int* c) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			(*c)++;
			if (arr[j] > arr[j + 1]) {
				Swap(&arr[j], &arr[j + 1]);
				(*m) += 3;
			}
		}
	}
}

void BubbleSortBetter(int arr[], int len, int* m, int* c) { // T.T
	bool swapped;

	for (int i = 0; i < len; i++) {
		swapped = false;

		for (int j = 0; j < len - i - 1; j++) {
			(*c)++;
			if (arr[j] > arr[j + 1]) {
				Swap(&arr[j], &arr[j + 1]);
				swapped = true; (*m) += 3;
			}
		}

		if (!swapped) break;
	}
}

void ShakerSort(int arr[], int len, int* m, int* c) {
	int left = 0, right = len - 1, k = right;

	do {
		for (int j = right; j > left; j--) {
			(*c)++;
			if (arr[j] < arr[j - 1]) {
				Swap(&arr[j], &arr[j - 1]); (*m) += 3;
				k = j;
			}
		}

		left = k;

		for (int j = left; j < right; j++) {
			(*c)++;
			if (arr[j] > arr[j + 1]) {
				Swap(&arr[j], &arr[j + 1]); (*m) += 3;
				k = j;
			}
		}

		right = k;

	} while (left < right);
}

void InsertSort(int arr[], int len, int* m, int* c) {
	for (int i = 1; i < len; i++) {
		int key = arr[i]; (*m)++;
		int j = i - 1;

		while (j >= 0) {
			(*c)++;
			if (arr[j] <= key) break;
			arr[j + 1] = arr[j]; (*m)++;
			j -= 1;
		}

		arr[j + 1] = key; (*m)++;
	}
}

void InsertSortWithStep(int arr[], int len, int* m, int* c, int step) {
	for (int i = step; i < len; i++) {
		int key = arr[i]; (*m)++;
		int j = i - step;

		while (j >= 0) {
			(*c)++;
			if (arr[j] <= key) break;
			arr[j + step] = arr[j]; (*m)++;
			j -= step;
		}

		arr[j + step] = key; (*m)++;
	}
}

void ShellSort(int arr[], int len, int* m, int* c) {
	int step = 1;
	while (step < len / 3) step = step * 3 + 1;

	while (step > 0) {
		InsertSortWithStep(arr, len, m, c, step);
		step = (step - 1) / 3; 
	}
}

void ShellSortKnut(int arr[], int len, int* m, int* c) {
	int max = (log2(len)) - 1;
	int* hArr = new int[max];
	hArr[0] = 1;
	for (int i = 1; i < max; i++) hArr[i] = 2 * hArr[i - 1] + 1;

	int temp, k, j, l = max - 1;
	for (k = hArr[l]; l >= 0; l--, k = hArr[l]) {
		for (int i = k; i < len; i++) {
			temp = arr[i]; (*m)++;
			j = i - k;

			while (j >= 0 && temp < arr[j]) {
				(*c)++;
				arr[j + k] = arr[j];
				j -= k;
				(*m)++;
			}

			if (j < 0) (*c)--;

			arr[j + k] = temp; (*m)++;
		}
	}

	delete[] hArr;
}

string GetKnutSteps(int len) {
	int h1 = 1, h = h1, i;

	for (h, i = 2; i + 1 < log2(len); h = 2 * h + 1, i++);

	return to_string(h1) + "..." + to_string(h);
}

string GetImpSteps(int len) {
	int h1 = 1, h = h1;

	while (h < len / 3) h = h * 3 + 1;

	return to_string(h1) + "..." + to_string(h);
}

bool ComparePhoneBooksAsc(const PhoneBook& pb1, const PhoneBook& pb2) {
	return pb1.surname == pb2.surname ? (pb1.name == pb2.name ? pb1.phone < pb2.phone : pb1.name < pb2.name) : pb1.surname < pb2.surname;
}

bool ComparePhoneBooksDesc(const PhoneBook& pb1, const PhoneBook& pb2) {
	return pb1.surname == pb2.surname ? (pb1.name == pb2.name ? pb1.phone > pb2.phone : pb1.name > pb2.name) : pb1.surname > pb2.surname;
}

bool ComparePhoneBookAscSurname(const PhoneBook& pb1, const PhoneBook& pb2) {
	return pb1.surname < pb2.surname;
}

bool ComparePhoneBookAscName(const PhoneBook& pb1, const PhoneBook& pb2) {
	return pb1.name < pb2.name;
}

void ShellSortKnutPhoneBook(PhoneBook arr[], int len, bool (*comparator)(const PhoneBook&, const PhoneBook&)) {
	int max = (log2(len)) - 1;
	int* hArr = new int[max];
	hArr[0] = 1;
	for (int i = 1; i < max; i++) hArr[i] = 2 * hArr[i - 1] + 1;

	PhoneBook temp;
	int k, j, l = max - 1;

	for (k = hArr[l]; l >= 0; l--, k = hArr[l]) {
		for (int i = k; i < len; i++) {
			temp = arr[i];
			j = i - k;

			while (j >= 0 && comparator(temp, arr[j])) {
				arr[j + k] = arr[j];
				j -= k;
			}

			arr[j + k] = temp;
		}
	}

	delete[] hArr;
}

void ShellSortKnutPhoneBookIdx(PhoneBook pbArr[], int idArr[], int len, bool (*comparator)(const PhoneBook&, const PhoneBook&)) {
	int max = (log2(len)) - 1;
	int* hArr = new int[max];
	hArr[0] = 1;
	for (int i = 1; i < max; i++) hArr[i] = 2 * hArr[i - 1] + 1;

	int k, l = max - 1;

	for (k = hArr[l]; l >= 0; l--, k = hArr[l]) {
		for (int i = k; i < len; i++) {
			int tempId = idArr[i];
			int j = i - k;

			while (j >= 0 && comparator(pbArr[tempId], pbArr[idArr[j]])) {
				idArr[j + k] = idArr[j];
				j -= k;
			}

			idArr[j + k] = tempId;
		}
	}

	delete[] hArr; 
}

void PrintPhoneBook(PhoneBook arr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("[%d] %s %s   %s   %s\n", i, arr[i].surname.c_str(), arr[i].name.c_str(), arr[i].phone.c_str(), arr[i].address.c_str());
	}
}

void PrintPhoneBookIdx(PhoneBook pbArr[], int idArr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("[%d] %s %s   %s   %s\n", idArr[i], pbArr[idArr[i]].surname.c_str(), pbArr[idArr[i]].name.c_str(), pbArr[idArr[i]].phone.c_str(), pbArr[idArr[i]].address.c_str());
	}
}

vector<int> BSearchAllPhoneBookSurname(PhoneBook arr[], int len, string key) {
	vector<int> indexes;
	int l = 0, r = len - 1, m = 0;

	while (l < r) {
		m = l + (r - l) / 2;

		if (arr[m].surname < key) l = m + 1;
		else r = m;
	}

	if (arr[l].surname == key) {
		indexes.push_back(l);
		int temp = l + 1;

		while (temp < len) {
			if (arr[temp].surname != key) break;

			indexes.push_back(temp++);
		}
	}

	return indexes;
}

vector<int> BSearchAllPhoneBookIdxSurname(PhoneBook arr[], int idArr[], int len, string key) {
	vector<int> indexes;
	int l = 0, r = len - 1, m = 0;

	while (l < r) {
		m = l + (r - l) / 2;

		if (arr[idArr[m]].surname < key) l = m + 1;
		else r = m;
	}

	if (arr[idArr[l]].surname == key) {
		indexes.push_back(idArr[l]);
		int tempId = l + 1;

		while (tempId < len) {
			if (arr[idArr[tempId]].surname != key) break;

			indexes.push_back(idArr[tempId++]);
		}
	}

	return indexes;
}

int BSearch(int arr[], int len, int key, int* c) {
	int l = 0, r = len - 1;

	while (l <= r) {
		int m = l + (r - l) / 2;

		(*c)++;
		if (arr[m] == key) return m;

		(*c)++;
		if (arr[m] < key) l = m + 1;
		else r = m - 1;
	}

	return -1;
}

int BSearchImp(int arr[], int len, int key, int* c) {
	int l = 0, r = len;

	while (l < r) {
		int m = l + (r - l) / 2;

		(*c)++;
		if (arr[m] < key) l = m + 1;
		else r = m;
	}

	(*c)++;
	return arr[r] == key ? l : -1;
}

vector<int> BSearchAll(int arr[], int len, int key, int* c) {
	vector<int> indexes;
	int l = 0, r = len - 1;

	while (l <= r) {
		int m = l + (r - l) / 2;

		(*c)++;
		if (arr[m] == key) {
			indexes.push_back(m);
			int temp = m - 1;

			while (temp >= 0) {
				(*c)++;
				if (arr[temp] != key) break;

				indexes.push_back(temp--);
			}

			temp = m + 1;

			while (temp < len) {
				(*c)++;
				if (arr[temp] != key) break;

				indexes.push_back(temp++);
			}

			break;
		}

		(*c)++;
		if (arr[m] < key) l = m + 1;
		else r = m - 1;
	}

	return indexes;
}

vector<int> BSearchAllImp(int arr[], int len, int key, int* c) {
	vector<int> indexes;
	int l = 0, r = len - 1, m = 0;

	while (l < r) {
		m = l + (r - l) / 2;

		(*c)++;
		if (arr[m] < key) l = m + 1;
		else r = m;
	}

	(*c)++;
	if (arr[l] == key) {
		indexes.push_back(l);
		int temp = l + 1;

		while (temp < len) {
			(*c)++;
			if (arr[temp] != key) break;

			indexes.push_back(temp++);
		}
	}

	return indexes;
}

void BuildHeap(int arr[], int l, int r, int* m, int* c) {
	int x = arr[l], i = l, j = 2 * i; (*m)++;

	while (1) {
		j = 2 * i;

		if (j >= r) break;

		(*c)++;
		if ((j < r) && (arr[j + 1] >= arr[j])) j++;

		(*c)++;
		if (x >= arr[j]) break;
		
		arr[i] = arr[j]; (*m)++;
		i = j;
	}

	arr[i] = x; (*m)++;
}

void HeapSort(int arr[], int len, int* m, int* c) {
	int l = floor(len / 2), r;

	while (l + 1 > 0) {
		BuildHeap(arr, l, len, m, c);
		l--;
	}

	r = len;
	
	while (r > 1) {
		Swap(&arr[0], &arr[r - 1]); (*m) += 3;
		r--;
		BuildHeap(arr, 0, r - 1, m, c);
	}
}

int _recCounter = 0;

void QuickSort(int arr[], int l, int r, int* m, int* c, int* maxRec) {
	_recCounter = 0;
	_recCounter++;

	if (maxRec && _recCounter > *maxRec)
		*maxRec = _recCounter;

	int pivot = arr[l], i = l, j = r;

	while (i <= j) {
		if (c) (*c)++;
		while (arr[i] < pivot) {
			i++;
			if (c) (*c)++;
		}

		if (c) (*c)++;
		while (arr[j] > pivot) {
			j--;
			if (c) (*c)++;
		}

		if (i <= j) {
			Swap(&arr[i], &arr[j]);
			if (m) (*m) += 3;
			i++;
			j--;
		}
	}

	if (l < j) QuickSort(arr, l, j, m, c, maxRec);
	if (i < r) QuickSort(arr, i, r, m, c, maxRec);

	_recCounter--;
}

void QuickSortImp(int arr[], int l, int r, int* m, int* c, int* maxRec) {
	_recCounter++;
	if (_recCounter > *maxRec) *maxRec = _recCounter;

	while (l < r) {
		int pivot = arr[l], i = l, j = r;

		while (i < j) {
			(*c)++;
			while (arr[i] < pivot) {
				i++;
				(*c)++;
			}

			(*c)++;
			while (arr[j] > pivot) {
				j--;
				(*c)++;
			}

			if (i <= j) {
				Swap(&arr[i++], &arr[j--]); (*m) += 3;
			}
		}

		if (j - l < r - i) {
			QuickSortImp(arr, l, j, m, c, maxRec);
			l = i;
		}
		else {
			QuickSortImp(arr, i, r, m, c, maxRec);
			r = j;
		}
	}

	_recCounter--;
}

void MMerge(Node** a, int q, Node** b, int r, QueueClean* c, int& C, int& M) {
	while (q != 0 && r != 0)
	{
		C++;
		if ((*a)->data <= (*b)->data)
		{
			M++;
			c->tail->next = *a;
			c->tail = *a;
			*a = (*a)->next;
			q--;
		}
		else
		{
			M++;
			c->tail->next = *b;
			c->tail = *b;
			*b = (*b)->next;
			r--;
		}
	}
	while (q > 0)
	{
		M++;
		c->tail->next = *a;
		c->tail = *a;
		*a = (*a)->next;
		q--;
	}
	while (r > 0)
	{
		M++;
		c->tail->next = *b;
		c->tail = *b;
		*b = (*b)->next;
		r--;
	}
}

int MSplit(Node* S, Node** a, Node** b, int& M) {
	Node* k, * p;
	*a = S;
	*b = S->next;
	int n = 1;
	k = *a;
	p = *b;

	while (p != NULL)
	{
		n++;
		k->next = p->next;
		k = p;
		p = p->next;
	}

	M += n;

	return n;
}

void MergeSort(Node* (&S), Node* (&tail), int& C, int& M) {
	C = M = 0;
	Node* a;
	Node* b;
	int n = MSplit(S, &a, &b, M);
	int p = 1;
	int q, r;
	QueueClean c[2];

	while (p < n)
	{
		c[0].tail = (Node*)&(c[0].head);
		c[1].tail = (Node*)&(c[1].head);

		int i = 0;
		int m = n;

		while (m > 0)
		{
			if (m >= p)
				q = p;
			else
				q = m;

			m = m - q;

			if (m >= p)
				r = p;
			else
				r = m;

			m = m - r;
			MMerge(&a, q, &b, r, &c[i], C, M);
			i = 1 - i;
		}

		a = c[0].head;
		b = c[1].head;
		p = 2 * p;
	}

	c[0].tail->next = nullptr;
	S = c[0].head;
	tail = c[0].tail;
}

void DigitalSort(Node16* (&s), Node16* (&tail), int& m, bool isDec) {
	int KDI[2] = { 1, 0 }, L = 2;
	int k;
	Node16* temp, *p;
	Queue16 q[256];
	unsigned char d;

	for (int j = L - 1; j >= 0; j--) {
		for (int i = 0; i <= 255; i++) {
			q[i].tail = (Node16*)&(q[i].head);
		}

		p = s;
		k = KDI[j];

		while (p != NULL) {
			m++;
			d = p->digit[k];
			q[d].tail->next = p;
			q[d].tail = p;
			p = p->next;
		}

		temp = p = (Node16*)&s;

		int i = isDec ? 255 : 0, sign = isDec ? -1 : 1;

		while (i > -1 && i < 256) {
			if (q[i].tail != (Node16*)&(q[i].head)) {
				m++;
				p->next = q[i].head;
				p = q[i].tail;
			}

			i += sign;
		}

		p->next = NULL;
	}
}

void DigitalSort(Node32* (&s), Node32* (&tail), int& m, bool isDec) {
	int KDI[4] = { 3, 2, 1, 0 }, L = 4, k;
	Node32* temp, *p;
	Queue32 q[256];
	unsigned char d;

	for (int j = L - 1; j >= 0; j--) {
		for (int i = 0; i <= 255; i++) {
			q[i].tail = (Node32*)&(q[i].head);
		}

		p = s;
		k = KDI[j];

		while (p != NULL) {
			m++;
			d = p->digit[k];
			q[d].tail->next = p;
			q[d].tail = p;
			p = p->next;
		}

		temp = p = (Node32*)&s;

		int i = isDec ? 255 : 0, sign = isDec ? -1 : 1;

		while (i > -1 && i < 256) {
			if (q[i].tail != (Node32*)&(q[i].head)) {
				m++;
				p->next = q[i].head;
				p = q[i].tail;
			}

			i += sign;
		}

		p->next = NULL;
	}
}

vector<vector<string>> GetSortData(const vector<sortersFType>& sorters, const vector<fillersFType>& fillers, const int min, const int max, const int step, int (*ct)(int), int (*mt)(int), const bool allowN, const bool allowMC) {
	vector<vector<string>> data;

	for (int n = min; n <= max; n += step) {
		int *arr, c = 0, m = 0;
		vector<string> row;

		if (allowN) row.push_back(to_string(n));
		if (allowMC && mt != nullptr && ct != nullptr) row.push_back(to_string((*mt)(n) + (*ct)(n)));

		for (auto sorter : sorters) {
			if (sorter == nullptr) continue;

			for (auto filler : fillers) {
				arr = new int[n];
				filler(arr, n);
				sorter(arr, n, &m, &c);
				row.push_back(to_string(m + c));
				delete[] arr; m = 0, c = 0;
			}
		}

		data.push_back(row);
	}

	return data;
}

vector<vector<string>> GetSearchData(const vector<searchersFType>& searchers, const int min, const int max, const int step, int (*ct)(int), const bool allowN) {
	vector<vector<string>> data;

	for (int n = min; n <= max; n += step) {
		int* arr, c = 0, sc = 0, sm = 0;
		vector<string> row;

		if (allowN) row.push_back(to_string(n));
		if (*ct != nullptr) row.push_back(to_string(ct(n)));

		arr = new int[n];
		FillRand(arr, n);
		ShellSortKnut(arr, n, &sc, &sm);

		for (auto search : searchers) {
			search(arr, n, GetRandomInt(0, n * 2), &c);
			row.push_back(to_string(c));
			c = 0;
		}

		delete[] arr;
		data.push_back(row);
	}

	return data;
}

vector<Point> CreatePoints(const vector<vector<string>>& data, const int startRow, const int colX, const int colY) {
	vector<Point> vp;

	for (size_t i = startRow; i < data.size(); i++) vp.push_back({ stoi(data[i][colX]), stoi(data[i][colY]) });

	return vp;
}

vector<vector<string>> VerticalVectorVectorConcatenate(const vector<vector<string>>& vec1, const vector<vector<string>>& vec2, const int vec1Start, const int vec2Start) {
	vector<vector<string>> result;
	size_t maxSize = max(vec1.size(), vec2.size());

	for (size_t i = 0; i < maxSize; ++i) {
		vector<string> row;

		if (i < vec1.size()) row.insert(row.end(), vec1[i].begin() + vec1Start, vec1[i].end());

		if (i < vec2.size()) row.insert(row.end(), vec2[i].begin() + vec2Start, vec2[i].end());

		result.push_back(row);
	}

	return result;
}