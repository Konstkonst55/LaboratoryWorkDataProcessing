
#include "ArrayUtils.h"
#include "AxisType.h"
#include "Chart.h"
#include "graphics.h"
#include "MathUtils.h"
#include "PhoneBook.h"
#include "Point.h"
#include "Queue.h"
#include "Stack.h"
#include "ListUtils.h"
#include "Table.h"
#include "TableHeaders.h"
#include "WindowSize.h"
#include "TreeUtils.h"
#include "TreeView.h"
#include "EncodingUtils.h"

#include <iostream>
#include <fstream>
#include <random>
#include <stdio.h>
#include <windows.h>
#include <cmath>
#include <format>
#include <locale>
#include <codecvt>
#include <unordered_map>

using namespace std;

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

int ConsoleInit();
void HandleTreeView(Vertex* root, std::string name = "BT View", bool isBinary = true);
void HandleTreeViewDeleting(BinaryTree& tree, std::string name = "BT View", int deleteCount = 10);
void HandleTreeViewAdding(BinaryTree& tree, std::string name = "BT View");
std::vector<std::string> GetTableLineTree(BinaryTree& tree, const string& name);
std::vector<std::string> GetTableLineOST(OST& tree, const string& name);
template <typename T> void PrintMatrix(const std::vector<std::vector<T>>& matrix);
template <typename T = int> std::vector<std::vector<std::string>> ConvertMatrixToString(const std::vector<std::vector<T>>& matrix);
std::string EscapeSpecialChar(char symbol);
std::string GenerateRandomString(size_t length);

void ShowSorts();           // ✔
void ShowSearches();        // ✔
void ShowStructSorting();   // ✔
void ShowIndexes();         // ✔
void ShowHeapShell();       // ✔
void ShowQuickHeapShell();  // ✔
void ShowStackQueueList();  // ✔
void ShowMerge();           // ✔
void ShowDigital();         // ✔

void ShowBinaryTree();      // ✔
void BuildPBST();           // ✔
void BuildRST();            // ✔
void DeleteVertexRST();     // ✔
void BuildAVL();            // ✔
void DeleteVertexAVL();     // ✔
void BuildBBT();            // ✔
void BuildOST();            // ✔
void BuildA1A2();           // ✔

void GenerateShannonCode();

int main() {
    ConsoleInit();

    GenerateShannonCode();
}

int ConsoleInit() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return 0;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return 0;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return 0;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void HandleTreeView(Vertex* root, std::string name, bool isBinary) {
    initwindow(1200, 800, name.c_str());

    const double scaleStep = 0.5;
    const int offsetStep = 100;
    double scale = 1;
    int offsetX = 0, offsetY = 0;

    if (isBinary) {
        DrawTree(root, scale, offsetX, offsetY);
    }
    else {
        DrawCodeTree(root, scale, offsetX, offsetY);
    }

    while (true) {
        if (kbhit()) {
            int key = getch();

            switch (key) {
                case 75: offsetX += offsetStep; break;
                case 77: offsetX -= offsetStep; break;
                case 72: offsetY += offsetStep; break;
                case 80: offsetY -= offsetStep; break;
                case 43:
                case 61: scale += scaleStep; break;
                case 45: scale = (scale > scaleStep) ? scale - scaleStep : scaleStep; break;
                case VK_ESCAPE: closegraph(); return;
            }

            if (isBinary) {
                DrawTree(root, scale, offsetX, offsetY);
            }
            else {
                DrawCodeTree(root, scale, offsetX, offsetY);
            }
        }
    }
}

void HandleTreeViewDeleting(BinaryTree& tree, std::string name, int deleteCount) {
    initwindow(1200, 800, name.c_str());

    const double scaleStep = 0.5;
    const int offsetStep = 100;
    double scale = 1;
    int offsetX = 0, offsetY = 0;

    DrawTree(tree.root, scale, offsetX, offsetY);

    for (int i = 0; i < deleteCount; i++) {
        std::cout << std::endl << "Enter the key to delete (" << (deleteCount - i) << " left): ";
        int key;
        std::cin >> key;

        if (tree.DeleteVertex(key)) {
            DrawTree(tree.root, scale, offsetX, offsetY);
        }
        else {
            i--;
        }
    }

    while (true) {
        if (kbhit()) {
            if (getch() == VK_ESCAPE) {
                closegraph();
                return;
            }
        }
    }
}

void HandleTreeViewAdding(BinaryTree& tree, std::string name) {
    initwindow(1200, 800, name.c_str());

    const double scaleStep = 0.5;
    const int offsetStep = 100;
    double scale = 1;
    int offsetX = 0, offsetY = 0;

    DrawTree(tree.root, scale, offsetX, offsetY);

    while (true) {
        std::cout << std::endl << "Enter the key to insert: ";
        int key;
        std::cin >> key;

        tree.AddVertex(key);
        DrawTree(tree.root, scale, offsetX, offsetY);
    }

    while (true) {
        if (kbhit()) {
            if (getch() == VK_ESCAPE) {
                closegraph();
                return;
            }
        }
    }
}

std::vector<std::string> GetTableLineTree(BinaryTree& tree, const string& name) {
    return { name, std::to_string(tree.GetSize()), std::to_string(tree.GetSum()), std::to_string(tree.GetHeight()), std::to_string(tree.GetAvgHeight()).substr(0, std::to_string(tree.GetAvgHeight()).find('.') + 3) };
}

std::vector<std::string> GetTableLineOST(OST& tree, const string& name) {
    return { name, std::to_string(tree.GetSize()), std::to_string(tree.GetSum()), std::to_string(tree.GetHeight()), std::to_string(tree.GetWeightedAvgHeight()).substr(0, std::to_string(tree.GetWeightedAvgHeight()).find('.') + 3) };
}

template <typename T = int> void PrintMatrix(const std::vector<std::vector<T>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& value : row) {
            std::cout << value << "  ";
        }

        std::cout << std::endl;
    }
}

template <typename T = int> std::vector<std::vector<std::string>> ConvertMatrixToString(const std::vector<std::vector<T>>& matrix) {
    std::vector<std::vector<std::string>> stringMatrix(matrix.size());

    for (size_t i = 0; i < matrix.size(); ++i) {
        std::transform(matrix[i].begin(), matrix[i].end(), std::back_inserter(stringMatrix[i]), [](T value) { return std::to_string(value); });
    }

    return stringMatrix;
}

std::string EscapeSpecialChar(char symbol) {
    static const std::unordered_map<char, std::string> specialChars = {
        {'\n', "\'n\'"},
        {'\t', "\'t\'"},
        {'\r', "\'r\'"},
        {'\v', "\'v\'"},
        {'\f', "\'f\'"},
        {'\b', "\'b\'"},
        {'\a', "\'a\'"},
        {'\\', "\\"},
        {'\'', "\'"},
        {'\"', "\""},
        {' ', "\' \'"}
    };

    if (specialChars.find(symbol) != specialChars.end()) {
        return specialChars.at(symbol);
    }

    return std::string(1, symbol);
}

std::string GenerateRandomString(size_t length) {
    const std::string chars = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя1234567890";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, chars.size() - 1);
    std::string result;

    for (size_t i = 0; i < length; ++i) {
        result += chars[distribution(generator)];
    }

    return result;
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

void ShowQuickHeapShell() {
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
    const vector<sortersQuickFType> sorters = { QuickSort, QuickSortImp };
    const vector<int> colors = { WHITE, LIGHTBLUE, LIGHTRED };
    const vector<string> labels = { "SHELL", "HEAP", "QUICK" };
    int legY = 60;

    vector<vector<string>> MCTable = DefaultMiniHeader,
        recTable = QuickSortHeader,
        quickSortData,
        quickSortRecData,
        shellSortData = GetSortData({ ShellSort }, fillers, MIN_N, MAX_N, STEP, GetCTheorShellSort, GetMTheorShellSort),
        heapSortData = GetSortData({ HeapSort }, fillers, MIN_N, MAX_N, STEP, GetCTheorHeapSort, GetMTheorHeapSort);
    vector<vector<vector<string>>> sortsData = { shellSortData, heapSortData };

    for (int n = MIN_N; n <= MAX_N; n += STEP) {
        int* arr, c = 0, m = 0, maxRec = 0;
        vector<string> row;

        row.push_back(to_string(n));
        row.push_back(to_string(GetCTheorQuickSort(n) + GetMTheorQuickSort(n)));

        for (auto filler : fillers) {
            arr = new int[n];
            filler(arr, n);
            QuickSort(arr, 0, n - 1, &m, &c, &maxRec);
            row.push_back(to_string(m + c));
            delete[] arr; m = 0; c = 0; _recCounter = 0; maxRec = 0;
        }

        quickSortData.push_back(row);
    }

    for (int n = MIN_N; n <= MAX_N; n += DATA_STEP) {
        int* arr, c = 0, m = 0, maxRec = 0;
        vector<string> row;

        row.push_back(to_string(n));

        for (auto sorter : sorters) {
            for (auto filler : fillers) {
                arr = new int[n];
                filler(arr, n);
                sorter(arr, 0, n - 1, &m, &c, &maxRec);
                row.push_back(to_string(maxRec));
                delete[] arr; m = 0; c = 0; _recCounter = 0; maxRec = 0;
            }
        }

        quickSortRecData.push_back(row);
    }

    FillTable(MCTable, quickSortData, 9, DATA_STEP);
    CreateTable(MCTable);
    sortsData.push_back(quickSortData);

    cout << "Глубина" << endl << endl;

    FillTable(recTable, quickSortRecData, 9, DATA_STEP);
    CreateTable(recTable);

    initwindow(wSize.x, wSize.y);

    DrawAxis(BOTTOM_LEFT, "N", "M+C", AXIS_STEP * X_SCALE, AXIS_STEP * Y_SCALE, 3, true, true);

    for (size_t s = 0; s < sortsData.size(); s++) {
        OutChartText(LEGEND_START, legY += LEGEND_STEP, colors[s], (char*)labels[s].c_str());
        DrawChartWithPoints(CreatePoints(sortsData[s], 0, 0, 3), X_SCALE, Y_SCALE, ALLOW_LABELS, LABEL_DENSITY, colors[s]);
    }

    printf("\n");
    system("PAUSE");
}

void ShowStackQueueList() {
    Stack stack;

    stack.FillInc(1, 9);
    cout << "Возрастающий стэк:" << endl << endl;
    stack.Print();
    stack.Clear();
    cout << endl << endl;

    stack.FillDec(9, 1);
    cout << "Убывающий стэк:" << endl << endl;
    stack.Print();
    stack.Clear();
    cout << endl << endl;

    stack.FillRand(9, 1, 9);
    cout << "Случайный стэк:" << endl << endl;
    stack.Print();
    stack.Clear();
    cout << endl << endl;

    Queue queue;

    queue.FillInc(1, 9);
    cout << "Возрастающая очередь:" << endl << endl;
    queue.Print();
    queue.Clear();
    cout << endl << endl;

    queue.FillDec(9, 1);
    cout << "Убывающая очередь:" << endl << endl;
    queue.Print();
    queue.Clear();
    cout << endl << endl;

    queue.FillRand(9, 1, 9);
    cout << "Случайная очередь:" << endl << endl;
    queue.Print();
    queue.Clear();
    cout << endl << endl;

    stack.FillRand(15, 0, 30);
    cout << endl << "Случайный стэк:" << endl << endl;
    stack.Print();
    cout << endl << endl << "Случайный стэк (обр.):" << endl << endl;
    stack.PrintReverse();
    cout << endl << endl << "Сумма: " << stack.GetSum() << endl;
    cout << "Серии: " << stack.GetSeries() << endl;

    queue.FillRand(15, 0, 30);
    cout << endl << "Случайная очередь:" << endl << endl;
    queue.Print();
    cout << endl << endl << "Случайная очередь (обр.):" << endl << endl;
    queue.PrintReverse();
    cout << endl << endl << "Сумма: " << queue.GetSum() << endl;
    cout << "Серии: " << queue.GetSeries() << endl << endl;

    system("PAUSE");
}

void ShowMerge() {
    //WindowSize wSize = { 1200, 800 };
    //const int
    //    MIN_N = 100,
    //    MAX_N = 1000,
    //    STEP = 10,
    //    LABEL_DENSITY = 10,
    //    LEGEND_STEP = 20,
    //    LEGEND_START = 50,
    //    DATA_STEP = 10;
    //const double
    //    X_SCALE = 1.1,
    //    Y_SCALE = 0.02,
    //    AXIS_STEP = MIN_N;
    //const bool ALLOW_LABELS = false;
    //const vector<fillersFType> fillers = { FillDec, FillRand, FillInc };
    //const vector<sortersQuickFType> sorters = { QuickSort, QuickSortImp };
    //const vector<int> colors = { WHITE, LIGHTBLUE, LIGHTRED };
    //const vector<string> labels = { "HEAP", "QUICK", "MERGE"};

    //int legY = 60; _recCounter = 0;

    //vector<vector<string>> MCTable = DefaultMiniHeader,
    //    quickSortData,
    //    mergeSortData,
    //    heapSortData = GetSortData({ HeapSort }, fillers, MIN_N, MAX_N, STEP, GetCTheorHeapSort, GetMTheorHeapSort);
    //vector<vector<vector<string>>> sortsData = { heapSortData };

    //for (int n = MIN_N; n <= MAX_N; n += STEP) {
    //    int* arr, c = 0, m = 0, maxRec = 0;
    //    vector<string> row;

    //    row.push_back(to_string(n));
    //    row.push_back(to_string(GetCTheorQuickSort(n) + GetMTheorQuickSort(n)));

    //    for (auto filler : fillers) {
    //        arr = new int[n];
    //        filler(arr, n);
    //        QuickSort(arr, 0, n - 1, &m, &c, &maxRec);
    //        row.push_back(to_string(m + c));
    //        delete[] arr; m = 0; c = 0; _recCounter = 0; maxRec = 0;
    //    }

    //    quickSortData.push_back(row);
    //}

    //for (int n = MIN_N; n <= MAX_N; n += STEP) {
    //    int* arr, c = 0, m = 0;
    //    vector<string> row;
    //    Queue queue;

    //    row.push_back(to_string(n));
    //    row.push_back(to_string(GetCTheorMergeSort(n) + GetMTheorMergeSort(n)));

    //    queue.FillDec(0, n);
    //    MergeSort(queue.front, queue.back, &m, &c);
    //    row.push_back(to_string(m + c));
    //    queue.Clear(); m = 0; c = 0;

    //    queue.FillRand(n, 0, n * 2);
    //    MergeSort(queue.front, queue.back, &m, &c);
    //    row.push_back(to_string(m + c));
    //    queue.Clear(); m = 0; c = 0;

    //    queue.FillInc(0, n);
    //    MergeSort(queue.front, queue.back, &m, &c);
    //    row.push_back(to_string(m + c));
    //    queue.Clear(); m = 0; c = 0;

    //    mergeSortData.push_back(row);
    //}

    //FillTable(MCTable, mergeSortData, 9, DATA_STEP);
    //CreateTable(MCTable);

    //sortsData.push_back(quickSortData);
    //sortsData.push_back(mergeSortData);

    //initwindow(wSize.x, wSize.y);

    //DrawAxis(BOTTOM_LEFT, "N", "M+C", AXIS_STEP * X_SCALE, AXIS_STEP * Y_SCALE, 3, true, true);

    //for (size_t s = 0; s < sortsData.size(); s++) {
    //    OutChartText(LEGEND_START, legY += LEGEND_STEP, colors[s], (char*)labels[s].c_str());
    //    DrawChartWithPoints(CreatePoints(sortsData[s], 0, 0, 3), X_SCALE, Y_SCALE, ALLOW_LABELS, LABEL_DENSITY, colors[s]);
    //}
    
    // ---------------------------- //

    //Node* stack;
    //Node* a;
    //Node* b;
    //int c = 0, m = 0;
    //int cmTheory = 0;

    //cout << "Исходный стэк: " << endl;
    //stack = FillRandNode(16, 0, 20);
    //PrintNode(stack);
    //MSplit(stack, &a, &b, m);
    //cout << "Стэк 1:" << endl;
    //PrintNode(a);
    //cout << "Количество элементов в списке: " << GetNodeCount(a) << endl;
    //cout << "Стек 2:" << endl;
    //PrintNode(b);
    //cout << "Количество элементов в списке: " << GetNodeCount(b) << endl;
    //
    //int q = floor(16 / 2);
    //int r = floor(16 / 2);
    //Node* stackA = FillRandNode(16, 0, 20);
    //Node* stackB = FillRandNode(16, 0, 20);
    //cout << "Стек 1:" << endl;
    //PrintNode(stackA);
    //cout << "Стек 2:" << endl;
    //PrintNode(stackB);
    //QueueClean queue;
    //queue.tail = (Node*)&(queue.tail);
    //MMerge(&stackA, q, &stackB, r, &queue, c, m);
    //cout << "\nИтоговая Очередь:" << endl;
    //PrintNode(queue.head);
    //cout << "\nФактическое С+M: " << c + m << " | Теоретическое C+M: " << 2 * (q + r) - 1 << endl;
    //cout << "Количество серий в списке: " << GetSeriesCount(queue.head) << endl;
    //cout << "Сумма элементов списка: " << GetNodeSum(queue.head) << endl;

    //system("PAUSE");
}

void ShowDigital() {
    const int MinN = 100, MaxN = 500, Step = 100, N = 20;
    int m = 0;
    Node16* head16 = NULL, * tail16 = NULL;
    Node32* head32 = NULL, * tail32 = NULL;

    QueueFillRand(N, head32, tail32);
    cout << "Неотсортированный список:" << endl;
    PrintList(head32);
    cout << "Количество серий в списке: " << CountSeries(head32) << endl;
    cout << "Сумма элементов списка: " << SumList(head32) << endl << endl;

    DigitalSort(head32, tail32, m, false);
    cout << "Отсортированный список:" << endl;
    PrintList(head32);
    cout << "Количество серий в списке: " << CountSeries(head32) << endl
    << "Сумма элементов списка: " << SumList(head32) << endl
    << endl << "Фактическое M: " << m << " | Теоретическое M: " << N << endl
    << endl << endl;

    cout << "DigitalSort Двухбайтовый по возрастанию:" << endl;
    QueueFillRand(N, head16, tail16);
    m = 0;
    DigitalSort(head16, tail16, m, false);
    PrintList(head16);
    cout << "DigitalSort Двухбайтовый по убыванию:" << endl;
    DigitalSort(head16, tail16, m, true);
    PrintList(head16);

    cout << "\nDigitalSort Четырёхбайтовый по возрастанию:" << endl;
    QueueFillRand(N, head32, tail32);
    m = 0;
    DigitalSort(head32, tail32, m, false);
    PrintList(head32);
    cout << "DigitalSort Четырёхбайтовый по убыванию:" << endl;
    DigitalSort(head32, tail32, m, true);
    PrintList(head32);
    cout << endl << endl;

    int *arr;
    string* row;
    vector<vector<string>> table = DigitalHeader;

    for (int n = MinN; n <= MaxN; n += Step) {
        Node16* head = nullptr, *tail = nullptr;
        vector<string> row;
        row.push_back(to_string(n));
        row.push_back(to_string(n));

        QueueFillDec(n, head, tail);
        DigitalSort(head, tail, m, false);
        row.push_back(to_string(m));
        DeleteList(head, tail); m = 0;

        QueueFillRand(n, head, tail);
        DigitalSort(head, tail, m, false);
        row.push_back(to_string(m));
        DeleteList(head, tail); m = 0;

        QueueFillInc(n, head, tail);
        DigitalSort(head, tail, m, false);
        row.push_back(to_string(m));
        DeleteList(head, tail); m = 0;

        table.push_back(row);
    }

    CreateTable(table);

    system("PAUSE");
}

void ShowBinaryTree() {
    BinaryTree tree;
    tree.root = CreateVertex(1);

    tree.root->left = CreateVertex(2);
    tree.root->left->right = CreateVertex(3);
    tree.root->left->right->left = CreateVertex(4);
    tree.root->left->right->left->right = CreateVertex(5);
    tree.root->left->right->left->right->right = CreateVertex(6);

    std::cout << "Root-Left-Right: ";
    tree.PrintRootLeftRight();

    std::cout << std::endl << "Left-Root-Right: ";
    tree.PrintLeftRootRight();

    std::cout << std::endl << "Left-Right-Root: ";
    tree.PrintLeftRightRoot();
    std::cout << std::endl << std::endl;

    tree.PrintInfo();

    tree.Delete();

    system("PAUSE");
}

void BuildPBST() {
    PBST pbst;
    int size = 100, * arr = new int[size];
    
    FillInc(arr, size);

    pbst.Create(arr, size);
    pbst.PrintLeftRootRight();
    std::cout << std::endl << std::endl;
    pbst.PrintInfo();
    std::cout << std::endl;

    system("PAUSE");
}

void BuildRST() {
    RST rst, rstdi;
    PBST pbst;
    const int size = 100;
    int arr[size], pbstArr[size];
    
    FillRand(arr, size);
    FillInc(pbstArr, size);

    pbst.Create(pbstArr, size);
    
    for (auto value : arr) {
        rst.AddVertex(value);
        rstdi.AddVertexDoubleIndirection(value);
    }

    std::cout << "RST Rec: ";
    rst.PrintLeftRootRight();
    std::cout << std::endl << std::endl;
    std::cout << "RST DI:  ";
    rstdi.PrintLeftRootRight();
    std::cout << std::endl << std::endl;

    auto header = TreeHeader;
    header.push_back(GetTableLineTree(pbst, "ISDP"));
    header.push_back(GetTableLineTree(rst, "SDP1"));
    header.push_back(GetTableLineTree(rstdi, "SDP2"));

    CreateTable(header);

    HandleTreeView(pbst.root, "ISDP");
    HandleTreeView(rst.root, "SDP1");
    HandleTreeView(rstdi.root, "SDP2");

    system("PAUSE");
}

void DeleteVertexRST() {
    RST rst;
    const int size = 30;
    int arr[size], key;

    FillRand(arr, size);
    
    for (auto value : arr) {
        rst.AddVertex(value);
    }

    rst.PrintLeftRootRight();

    HandleTreeViewDeleting(rst, "SDP", 10);

    system("PAUSE");
}

void BuildAVL() {
    PBST pbst;
    AVL avl;
    const int size = 100;
    int arr[size];

    FillRandUniq(arr, size);

    for (auto value : arr) {
        avl.AddVertex(value);
    }

    int m = 0, c = 0, maxRec = 0;
    QuickSort(arr, 0, size - 1, &m, &c, &maxRec);

    pbst.Create(arr, size);

    std::cout << "ISDP: ";
    pbst.PrintLeftRootRight();
    std::cout << std::endl << std::endl;
    std::cout << "AVL : ";
    avl.PrintLeftRootRight();
    std::cout << std::endl << std::endl;

    auto header = TreeHeader;
    header.push_back(GetTableLineTree(pbst, "ISDP"));
    header.push_back(GetTableLineTree(avl, "AVL"));

    CreateTable(header);

    HandleTreeView(pbst.root, "ISDP");
    HandleTreeView(avl.root, "AVL");
    
    system("PAUSE");
}

void DeleteVertexAVL() {
    AVL avl;
    const int size = 30;
    int arr[size], key;

    FillRandUniq(arr, size);

    for (auto value : arr) {
        avl.AddVertex(value);
    }

    avl.PrintLeftRootRight();

    HandleTreeViewDeleting(avl, "AVL", 10);

    system("PAUSE");
}

void BuildBBT() {
    BBT bbt;
    AVL avl;
    const int size = 100;
    int arr[size];

    FillRandUniq(arr, size);

    for (auto value : arr) {
        avl.AddVertex(value);
    }

    for (auto value : arr) {
        bbt.AddVertex(value);
    }

    std::cout << "Levels: " << bbt.GetLevels() << std::endl;

    auto header = TreeHeader;
    header.push_back(GetTableLineTree(bbt, "DBD"));
    header.push_back(GetTableLineTree(avl, "AVL"));

    CreateTable(header);

    HandleTreeView(bbt.root, "DBD");
    HandleTreeView(avl.root, "AVL");

    system("PAUSE");
}

void BuildOST() {
    OST ost;
    const int size = 10;
    int keysArr[size];
    std::vector<std::pair<int, int>> keyWithWeights;

    FillInc(keysArr, size);

    for (int i = 0; i < size; i++) {
        keyWithWeights.emplace_back(keysArr[i], GetRandomInt(1, 100));
    }

    ost.Create(keyWithWeights);

    std::cout << "AW: " << std::endl;
    CreateTable(ConvertMatrixToString(ost.GetWeights()), "");

    std::cout << "AP: " << std::endl;
    CreateTable(ConvertMatrixToString(ost.GetHeights()), "");

    std::cout << "AR: " << std::endl;
    CreateTable(ConvertMatrixToString(ost.GetRoots()), "");

    std::cout << "Left Root Right:" << std::endl << std::endl;
    ost.PrintLeftRootRight();

    std::cout << std::endl << std::endl << "AP/AW = h: " << ost.GetRatioHeightsWeights() << " = " << ost.GetWeightedAvgHeight() << std::endl << std::endl;

    auto header = TreeHeader;
    header.push_back(GetTableLineOST(ost, "DOP"));
    CreateTable(header);

    HandleTreeView(ost.root, "DOP");

    system("pause");
}

void BuildA1A2() {
    OST ost;
    A1 a1;
    A2 a2;
    const int size = 100;
    int keysArr[size];
    std::vector<std::pair<int, int>> keyWithWeights;

    if (keyWithWeights.empty()) {
        FillInc(keysArr, size);

        for (int i = 0; i < size; i++) {
            keyWithWeights.emplace_back(keysArr[i], GetRandomInt(1, 100));
        }
    }

    ost.Create(keyWithWeights);
    a1.Create(keyWithWeights);
    a2.Create(keyWithWeights);

    auto header = TreeHeader;
    header.push_back(GetTableLineOST(ost, "DOP"));
    header.push_back(GetTableLineOST(a1, "A1"));
    header.push_back(GetTableLineOST(a2, "A2"));
    CreateTable(header);

    HandleTreeView(ost.root, "DOP");
    HandleTreeView(a1.root, "A1");
    HandleTreeView(a2.root, "A2");

    system("pause");
}

void GenerateShannonCode() {
    const std::string path = "encoding.txt";
    const size_t encodeSize = 100;

    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << path << std::endl;
        return;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    // content = GenerateRandomString(100);

    ShannonCoding code(content.c_str());
    std::cout << content << std::endl;
    auto symbols = code.GetSymbols();
    auto encodingHeader = EncodingHeader;
    double totalProbability = 0.0;

    for (size_t i = 0; i < code.GetSymbolCount(); i++) {
        std::string codeData;

        for (size_t j = 0; j < symbols[i].code.length; j++) {
            codeData.append(std::to_string(symbols[i].code.data[j]));
        }

        std::string escapedSymbol = EscapeSpecialChar(symbols[i].symbol);
        encodingHeader.push_back({ escapedSymbol, std::to_string(symbols[i].probability), codeData, std::to_string(symbols[i].code.length) });
        
        totalProbability += symbols[i].probability;
    }

    CreateTable(encodingHeader);

    std::cout << "Total probability: " << totalProbability << std::endl;

    auto codeHeader = CodeInfoHeader;
    codeHeader.push_back({ std::to_string(code.GetKraftInequality()), std::to_string(code.GetEntropy()), std::to_string(code.GetAverageCodeLength()), std::to_string(code.GetRedundancy()) });

    CreateTable(codeHeader);

    std::vector<int> encodedText;

    for (size_t i = 0; i < encodeSize; i++) {
        char c = content[i];

        for (size_t j = 0; j < code.GetSymbolCount(); j++) {
            if (symbols[j].symbol == c) {
                for (size_t bit = 0; bit < symbols[j].code.length; bit++) {
                    encodedText.push_back(symbols[j].code.data[bit]);
                }

                break;
            }
        }
    }

    std::cout << "Encoded text: ";

    for (int bit : encodedText) {
        std::cout << bit;
    }

    std::cout << std::endl << std::endl;

    size_t encodedTextLength = encodedText.size();
    size_t originalTextLength = encodeSize * 8;
    double compressionRatio = (double)encodedTextLength / originalTextLength * 100.0;

    std::cout << "Source text length in bits: " << originalTextLength << std::endl;
    std::cout << "Encoded text length in bits: " << encodedTextLength << std::endl;
    std::cout << "Compression ratio: " << compressionRatio << "%" << std::endl;

    CodeTree ctree;
    
    for (size_t i = 0; i < code.GetSymbolCount(); i++) {
        ctree.AddVertex(symbols[i].symbol, std::vector<int>(symbols[i].code.data, symbols[i].code.data + symbols[i].code.length));
    }

    HandleTreeView(ctree.root, "Code Tree", false);

    system("pause");
}