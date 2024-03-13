#include "graphics.h"
#include <stdio.h>
#include "ArrayUtils.h"
#include "MathUtils.h"
#include "TableHeaders.h"
#include "Point.h"
#include "WindowSize.h"
#include <windows.h>
#include "Table.h"
#include "Chart.h"
#include "AxisType.h"

void ShowSorts();
void ShowSearches();

int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return 0;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return 0;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return 0;

    ShowSearches();
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
        knutStepsCol.push_back(getKnutSteps(n));
        impStepsCol.push_back(getImpSteps(n));
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
        STEP = 10,
        LABEL_DENSITY = 10,
        LEGEND_STEP = 20,
        LEGEND_START = 50,
        DATA_STEP = 10;
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

    for (size_t s = 0, y = 2; s < searchersDataTable[0].size() - 2; s++, y++) {
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