
#include "ArrayUtils.h"

void FillInc(int arr[], int len) {
	for (int i = 0; i < len; i++) arr[i] = i + 1;
}

void FillDec(int arr[], int len) {
	for (int i = 0; i < len; i++) arr[i] = len - i;
}

void FillRand(int arr[], int len) {
	srand((unsigned int)time(NULL));
	for (int i = 0; i < len; i++) arr[i] = GetRandomInt(0, len * 2);
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

void swap(int* a, int* b) {
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

		swap(&arr[minIndex], &arr[step]); (*m) += 3;
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
			swap(&arr[minIndex], &arr[step]);
			(*m) += 3;
		}
	}
}

void BubbleSort(int arr[], int len, int* m, int* c) {
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len - i - 1; j++) {
			(*c)++;
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
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
				swap(arr[j], arr[j + 1]);
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
				swap(arr[j], arr[j - 1]); (*m) += 3;
				k = j;
			}
		}

		left = k;

		for (int j = left; j < right; j++) {
			(*c)++;
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]); (*m) += 3;
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
}

string getKnutSteps(int len) {
	int h1 = 1, h = h1, i;

	for (h, i = 2; i + 1 < log2(len); h = 2 * h + 1, i++);

	return to_string(h1) + "..." + to_string(h);
}

string getImpSteps(int len) {
	int h1 = 1, h = h1;

	while (h < len / 3) h = h * 3 + 1;

	return to_string(h1) + "..." + to_string(h);
}

bool ComparePhoneBooks(const PhoneBook& pb1, const PhoneBook& pb2) {
	return pb1.surname == pb2.surname ? pb1.name < pb2.name : pb1.surname < pb2.surname;
}

void ShellSortKnutPhoneBook(PhoneBook arr[], int len, bool (*comparator)(const PhoneBook&, const PhoneBook&), bool isAsc) {
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

			while (j >= 0 && (isAsc ? comparator(temp, arr[j]) : !comparator(temp, arr[j]))) {
				arr[j + k] = arr[j];
				j -= k;
			}

			arr[j + k] = temp;
		}
	}
}

void PrintPhoneBook(PhoneBook arr[], int len) {
	for (int i = 0; i < len; i++) {
		printf("[%d] %s %s   %s   %s\n", i, arr[i].surname.c_str(), arr[i].name.c_str(), arr[i].phone.c_str(), arr[i].address.c_str());
	}
}

int BSearchPhoneBook(PhoneBook arr[], int len, string key, string field) {
	int l = 0, r = len - 1;

	for (auto& c : field) {
		c = tolower(c);
	}

	while (l <= r) {
		int m = l + (r - l) / 2;

		if (field == "surname" && arr[m].surname == key) return m;
		if (field == "name" && arr[m].name == key) return m;
		if (field == "phone" && arr[m].phone == key) return m;
		if (field == "address" && arr[m].address == key) return m;

		if (field == "surname" && arr[m].surname < key) l = m + 1;
		else if (field == "name" && arr[m].name < key) l = m + 1;
		else if (field == "phone" && arr[m].phone < key) l = m + 1;
		else if (field == "address" && arr[m].address < key) l = m + 1;
		else r = m - 1;
	}

	return -1;
}

vector<int> BSearchAllPhoneBookSurname(PhoneBook arr[], int len, string key) {
	vector<int> indexes;
	int l = 0, r = len - 1;

	while (l <= r) {
		int m = l + (r - l) / 2;

		if (arr[m].surname == key) {
			indexes.push_back(m);
			int temp = m - 1;

			while (temp >= 0) {
				if (arr[temp].surname != key) break;

				indexes.push_back(temp--);
			}

			temp = m + 1;

			while (temp < len) {
				if (arr[temp].surname != key) break;

				indexes.push_back(temp++);
			}

			break;
		}

		if (arr[m].surname < key) l = m + 1;
		else r = m - 1;
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
	int l = 0, r = len, m = 0;

	while (l < r) {
		m = l + (r - l) / 2;

		(*c)++;
		if (arr[m] < key) l = m + 1;
		else r = m;
	}

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
	}

	return indexes;
}

vector<vector<string>> GetSortData(const vector<sortersFType>& sorters, const vector<fillersFType>& fillers, const int min, const int max, const int step, int (*ct)(int), int (*mt)(int), const bool allowN, const bool allowMC) {
	vector<vector<string>> data;

	for (int n = min; n <= max; n += step) {
		int *arr, c = 0, m = 0;
		vector<string> row;

		if (allowN) row.push_back(to_string(n));
		if (allowMC || *mt != nullptr || *ct != nullptr) row.push_back(to_string(mt(n) + ct(n)));

		for (auto sorter : sorters)
		{
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