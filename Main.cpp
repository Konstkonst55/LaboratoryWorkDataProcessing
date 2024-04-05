#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "graphics.h"
#include "ArrayUtils.h"
#include "MathUtils.h"
#include "TableHeaders.h"
#include "Point.h"
#include "WindowSize.h"
#include "Table.h"
#include "Chart.h"
#include "AxisType.h"
#include "PhoneBook.h"

void ShowSorts();
void ShowSearches();
void ShowStructSorting();
void ShowIndexes();
void ShowHeapShell();

PhoneBook phoneBook[] = {
    {"Иванов", "Иван", "9231405856", "ул. Пушкина, 1"},
    {"Петров", "Петр", "9231405828", "ул. Пушкина, 2"},
    {"Сидоров", "Сергей", "9231476822", "ул. Пушкина, 3"},
    {"Кузнецов", "Кузьма", "9231402326", "ул. Пушкина, 4"},
    {"Смирнов", "Олег", "9231405829", "ул. Пушкина, 5"},
    {"Васильев", "Василий", "9231345827", "ул. Пушкина, 6"},
    {"Дмитриев", "Дмитрий", "9231685824", "ул. Пушкина, 7"},
    {"Иванов", "Иван", "9231405858", "ул. Пушкина, 1"},
    {"Дмитриев", "Борис", "9231685824", "ул. Пушкина, 7"},
    {"Новиков", "Дмитрий", "9231405834", "ул. Пушкина, 8"},
    {"Михайлов", "Михаил", "9231695827", "ул. Пушкина, 9"},
    {"Михайлов", "Евгений", "9231401548", "ул. Пушкина, 10"},
    {"Иванов", "Иван", "9231405857", "ул. Пушкина, 1"},
    {"Алексеев", "Алексей", "9231409632", "ул. Пушкина, 11"},
    {"Сергеев", "Сергей", "9231429327", "ул. Пушкина, 12"}
};

int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return 0;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return 0;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return 0;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    ShowHeapShell();
}

void ShowSorts() {
    WindowSize wSize = { 1200, 800 };
    const int
        MIN_N = 100,
        MAX_N = 500,
        STEP = 10,
        LABEL_DENSITY = 10,
        LEGEND_STEP = 20,
        LEGEND_START = 50,
        DATA_STEP = 10;
    const double
        X_SCALE = 2,
        Y_SCALE = 0.002,
        AXIS_STEP = MIN_N;
    const bool ALLOW_LABELS = false;
    const vector<fillersFType> fillers = { FillDec, FillRand, FillInc };
    const vector<sortersFType> sorters = { SelectSort, BubbleSort, ShakerSort, InsertSort };
    const vector<int> colors = { LIGHTBLUE, LIGHTRED, LIGHTGREEN, MAGENTA, WHITE };
    const vector<string> labels = { "BUBBLE", "SHAKER", "SELECT", "INSERT", "SHELL" };

    int legY = 60;

    vector<vector<string>>
        MCTable = ShellInsertSortHeader,
        selectSortData = GetSortData({ SelectSort }, fillers, MIN_N, MAX_N, STEP, GetCTheorSelectSort, GetMTheorSelectSort),
        bubbleSortData = GetSortData({ BubbleSort }, fillers, MIN_N, MAX_N, STEP, GetCTheorBubbleSort, GetMTheorBubbleSort),
        shakerSortData = GetSortData({ ShakerSort }, fillers, MIN_N, MAX_N, STEP, GetCTheorShakerSort, GetMTheorShakerSort),
        insertChartData = GetSortData({ InsertSort }, fillers, MIN_N, MAX_N, STEP, GetCTheorInsertSort, GetMTheorInsertSort),
        insertSortData = GetSortData({ InsertSort }, { FillRand }, MIN_N, MAX_N, STEP, nullptr, nullptr, true, false),
        shellChartData = GetSortData({ ShellSort }, fillers, MIN_N, MAX_N, STEP, GetCTheorInsertSort, GetMTheorInsertSort),
        shellSortImpData = GetSortData({ ShellSort }, { FillRand }, MIN_N, MAX_N, STEP, nullptr, nullptr, false, false),
        shellSortKnutData = GetSortData({ ShellSortKnut }, { FillRand }, MIN_N, MAX_N, STEP, nullptr, nullptr, false, false),
        knutSteps, impSteps;
    const vector<vector<vector<string>>> sortsData = { bubbleSortData, shakerSortData, selectSortData, insertChartData, shellChartData };

    for (int n = MIN_N; n <= MAX_N; n += STEP) {
        vector<string> knutStepsCol, impStepsCol;
        knutStepsCol.push_back(GetKnutSteps(n));
        impStepsCol.push_back(GetImpSteps(n));
        knutSteps.push_back(knutStepsCol);
        impSteps.push_back(impStepsCol);
    }

    auto shellTable = VerticalVectorVectorConcatenate(insertSortData, shellSortKnutData);
    shellTable = VerticalVectorVectorConcatenate(shellTable, knutSteps);
    shellTable = VerticalVectorVectorConcatenate(shellTable, shellSortImpData);
    shellTable = VerticalVectorVectorConcatenate(shellTable, impSteps);

    FillTable(MCTable, shellTable, 9, DATA_STEP);

    CreateTable(MCTable);

    initwindow(wSize.x, wSize.y);

    DrawAxis(BOTTOM_LEFT, "N", "M+C", AXIS_STEP * X_SCALE, AXIS_STEP * Y_SCALE, 3, true, true);

    for (size_t s = 0; s < sortsData.size(); s++) {
        OutChartText(LEGEND_START, legY += LEGEND_STEP, colors[s], (char*)labels[s].c_str());
        DrawChartWithPoints(CreatePoints(sortsData[s], 0, 0, 3), X_SCALE, Y_SCALE, ALLOW_LABELS, LABEL_DENSITY, colors[s]);
    }

    system("PAUSE");
    closegraph();
}

void ShowSearches() {
    WindowSize wSize = { 1200, 800 };
    const int
        MIN_N = 100,
        MAX_N = 1000,
        STEP = 1,
        LABEL_DENSITY = 10,
        LEGEND_STEP = 20,
        LEGEND_START = 50,
        DATA_STEP = 100;
    const double
        X_SCALE = 1,
        Y_SCALE = 30,
        AXIS_STEP = MIN_N;
    const bool ALLOW_LABELS = false;
    const vector<searchersFType> searchers = { BSearch, BSearchImp, BSearchAll, BSearchAllImp };
    const vector<int> colors = { LIGHTRED, LIGHTGREEN, MAGENTA, WHITE };
    const vector<string> labels = { "SEARCH 1", "SEARCH 2", "SEARCH ALL 1", "SEARCH ALL 2"};
    int legY = 60;

    vector<vector<string>> CTable = SearchesHeader,
        searchersDataTable = GetSearchData(searchers, MIN_N, MAX_N, STEP, GetCTheorBSearch, true);

    FillTable(CTable, searchersDataTable, 9, DATA_STEP);

    CreateTable(CTable);

    initwindow(wSize.x, wSize.y);

    DrawAxis(BOTTOM_LEFT, "N", "C", AXIS_STEP * X_SCALE, AXIS_STEP * Y_SCALE, 3, true, true);

    for (size_t s = 0, y = 2; s < searchersDataTable[0].size() - 4; s++, y++) {
        OutChartText(LEGEND_START, legY += LEGEND_STEP, colors[s], (char*)labels[s].c_str());
        DrawChartWithPoints(CreatePoints(searchersDataTable, 3, 0, y), X_SCALE, Y_SCALE, ALLOW_LABELS, LABEL_DENSITY, colors[s]);
    }

    initwindow(wSize.x, wSize.y);

    DrawAxis(BOTTOM_LEFT, "N", "C", AXIS_STEP * X_SCALE, AXIS_STEP * Y_SCALE, 3, true, true);

    for (size_t s = 2, y = 4; s < searchersDataTable[0].size() - 2; s++, y++) {
        OutChartText(LEGEND_START, legY += LEGEND_STEP, colors[s], (char*)labels[s].c_str());
        DrawChartWithPoints(CreatePoints(searchersDataTable, 3, 0, y), X_SCALE, Y_SCALE, ALLOW_LABELS, LABEL_DENSITY, colors[s]);
    }

    const int testSize = 100, testKey = 5, testMax = 20;
    int* testArr = new int[testSize], c = 0, cImp = 0, cAll = 0, cAllImp = 0, sm = 0, sc = 0;
    srand((unsigned int)time(NULL));
    for (int i = 0; i < testSize; i++) testArr[i] = GetRandomInt(0, testMax);
    ShellSortKnut(testArr, testSize, &sm, &sc);

    int testSearchResult = BSearch(testArr, testSize, testKey, &c);
    int testSearchImpResult = BSearchImp(testArr, testSize, testKey, &cImp);
    vector<int> testSearchAllResult = BSearchAll(testArr, testSize, testKey, &cAll);
    vector<int> testSearchAllImpResult = BSearchAllImp(testArr, testSize, testKey, &cAllImp);
    
    for (int i = 0; i < testSize; i++) printf("\033[38;5;240m%d:\033[0m[%d] ", i, testArr[i]);

    printf("\n\nBSearch");
    if (testSearchResult == -1) printf("\nKey %d was not found!", testKey);
    else printf("\nKey %d was found on index %d!", testKey, testSearchResult);
    printf("\nC_theor: %d\nC: %d", GetCTheorBSearch(testSize), c);

    printf("\n\nBSearchImp");
    if (testSearchImpResult == -1) printf("\nKey %d was not found!", testKey);
    else printf("\nKey %d was found on index %d!", testKey, testSearchImpResult);
    printf("\nC_theor: %d\nC: %d", GetCTheorBSearchImp(testSize), cImp);

    printf("\n\nBSearchAll");
    if (testSearchAllResult.empty()) printf("\nKey %d was not found!", testKey);
    else printf("\nKey %d was found on indexes:\n", testKey);
    for (int index : testSearchAllResult) printf("[%d] ", index);
    printf("\nC: %d", cAll);

    printf("\n\nBSearchAllImp");
    if (testSearchAllImpResult.empty()) printf("\nKey %d was not found!", testKey);
    else printf("\nKey %d was found on indexes:\n", testKey);
    for (int index : testSearchAllImpResult) printf("[%d] ", index);
    printf("\nC: %d\n\n", cAllImp);

    system("PAUSE");
    closegraph();
}

void ShowStructSorting() {
    int n = sizeof(phoneBook) / sizeof(phoneBook[0]);

    printf("Исходный справочник: \n\n");

    PrintPhoneBook(phoneBook, n);

    ShellSortKnutPhoneBook(phoneBook, n, ComparePhoneBooksAsc);

    printf("\nОтсортированный справочник: \n\n");

    PrintPhoneBook(phoneBook, n);

    printf("\n");

    while (true) {
        string key;

        printf("\nВведите ключ: ");
        cin >> key;

        vector<int> sRes = BSearchAllPhoneBookSurname(phoneBook, n, key);

        if (sRes.empty()) printf("\nТакого человека нет в справочнике");
        else printf("\nНайдены: ");
        for (auto id : sRes) printf("\n - [%d] %s %s", id, phoneBook[id].surname.c_str(), phoneBook[id].name.c_str());

        char choice;
        printf("\n\nПродолжить поиск? (y/n): ");
        cin >> choice;
        if (tolower(choice) != 'y' && tolower(choice) != 'д') break;
    }

    printf("\n");
    system("PAUSE");
}

void ShowIndexes() {
    int n = sizeof(phoneBook) / sizeof(phoneBook[0]);
    int* idArrSurname = new int[n], *idArrName = new int[n];

    for (int i = 0; i < n; i++) {
        idArrSurname[i] = i;
        idArrName[i] = i;
    }

    printf("Исходный справочник: \n\n");

    PrintPhoneBook(phoneBook, n);

    ShellSortKnutPhoneBookIdx(phoneBook, idArrSurname, n, ComparePhoneBookAscSurname);
    ShellSortKnutPhoneBookIdx(phoneBook, idArrName, n, ComparePhoneBookAscName);

    printf("\nИсходный справочник после сортировки: \n\n");

    PrintPhoneBook(phoneBook, n);

    printf("\nОтсортированный справочник по фамилии: \n\n");

    PrintPhoneBookIdx(phoneBook, idArrSurname, n);
    
    printf("\nОтсортированный справочник по имени: \n\n");

    PrintPhoneBookIdx(phoneBook, idArrName, n);

    printf("\n");

    while (true) {
        string key;

        printf("\nВведите ключ: ");
        cin >> key;

        vector<int> sRes = BSearchAllPhoneBookIdxSurname(phoneBook, idArrSurname, n, key);

        if (sRes.empty()) printf("\nТакого человека нет в справочнике");
        else printf("\nНайдены: \n");
        PrintPhoneBookIdx(phoneBook, sRes.data(), sRes.size());

        char choice;
        printf("\nПродолжить поиск? (y/n): ");
        cin >> choice;
        if (tolower(choice) != 'y' && tolower(choice) != 'д') break;
    }

    printf("\n");
    system("PAUSE");
}

void ShowHeapShell() {
    WindowSize wSize = { 1200, 800 };
    const int
        MIN_N = 100,
        MAX_N = 1000,
        STEP = 10,
        LABEL_DENSITY = 10,
        LEGEND_STEP = 20,
        LEGEND_START = 50,
        DATA_STEP = 10;
    const double
        X_SCALE = 1.1,
        Y_SCALE = 0.02,
        AXIS_STEP = MIN_N;
    const bool ALLOW_LABELS = false;
    const vector<fillersFType> fillers = { FillDec, FillRand, FillInc };
    const vector<int> colors = { LIGHTBLUE, LIGHTRED };
    const vector<string> labels = { "HEAP", "SHELL" };

    int legY = 60;

    vector<vector<string>>
        MCTable = DefaultMiniHeader,
        BuildMCTable = NMCHeader,
        heapSortData = GetSortData({ HeapSort }, fillers, MIN_N, MAX_N, STEP, GetCTheorHeapSort, GetMTheorHeapSort),
        shellSortKnutData = GetSortData({ ShellSort }, fillers, MIN_N, MAX_N, STEP, GetCTheorShellSort, GetMTheorShellSort),
        heapBuildData;
    const vector<vector<vector<string>>> sortsData = { heapSortData, shellSortKnutData };

    for (int n = MIN_N; n <= MAX_N; n += DATA_STEP) {
        int* arr, c = 0, m = 0;
        vector<string> row;

        row.push_back(to_string(n));

        for (auto filler : fillers) {
            arr = new int[n];
            filler(arr, n);
            BuildHeap(arr, 0, n, &m, &c);
            row.push_back(to_string(m + c));
            delete[] arr; m = 0, c = 0;
        }

        heapBuildData.push_back(row);
    }

    FillTable(BuildMCTable, heapBuildData, 9, DATA_STEP);
    FillTable(MCTable, heapSortData, 9, DATA_STEP);

    CreateTable(BuildMCTable);
    CreateTable(MCTable);

    initwindow(wSize.x, wSize.y);

    DrawAxis(BOTTOM_LEFT, "N", "M+C", AXIS_STEP * X_SCALE, AXIS_STEP * Y_SCALE, 3, true, true);

    for (size_t s = 0; s < sortsData.size(); s++) {
        OutChartText(LEGEND_START, legY += LEGEND_STEP, colors[s], (char*)labels[s].c_str());
        DrawChartWithPoints(CreatePoints(sortsData[s], 0, 0, 3), X_SCALE, Y_SCALE, ALLOW_LABELS, LABEL_DENSITY, colors[s]);
    }

    printf("\n");
    system("PAUSE");
}