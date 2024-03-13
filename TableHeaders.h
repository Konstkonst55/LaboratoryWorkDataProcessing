#include <vector>
#include <string>

using namespace std;

#pragma once

#ifndef TABLE_HEADERS_H
#define TABLE_HEADERS_H

const vector<vector<string>> DefaultHeader = {
    { "N", "M+C theor.", "Src M+C", "Src M+C", "Src M+C", "Imp M+C", "Imp M+C", "Imp M+C" },
    { " ", " ", "Dec", "Rand", "Inc", "Dec", "Rand", "Inc" },
    { "-", "----------", "-------", "-------", "-------", "-------", "-------", "-------"}
};

const vector<vector<string>> DefaultMiniHeader = {
    { "N", "M+C theor.", "Src M+C", "Src M+C", "Src M+C" },
    { " ", " ", "Dec", "Rand", "Inc"},
    { "-", "----------", "-------", "-------", "-------"}
};

const vector<vector<string>> BubbleSortWithImpHeader = {
    { "N", "M+C theor.", "Src M+C", "Src M+C", "Src M+C", "Imp M+C", "Imp M+C", "Imp M+C" },
    { " ", " ", "Dec", "Rand", "Inc", "Dec", "Rand", "Inc" },
    { "-", "----------", "-------", "-------", "-------", "-------", "-------", "-------"}
};

const vector<vector<string>> BubbleAndShakerHeader = {
    { "N", "SH M+C theor.", "BB M+C", "BB M+C", "BB M+C", "SH M+C", "SH M+C", "SH M+C" },
    { " ", " ", "Dec", "Rand", "Inc", "Dec", "Rand", "Inc" },
    { "-", "----------", "-------", "-------", "-------", "-------", "-------", "-------"}
};

const vector<vector<string>> AllSortersHeader = {
    { "N", "Select", "Bubble", "Shaker", "Insert" },
    { "-", "------", "------", "------", "------" }
};

const vector<vector<string>> ShellInsertSortHeader = {
    { "N", "Insert", "Knut Shell", "Knut h1...hm", "Imp Shell", "Imp h1...hm"},
    { "-", "-------", "---------", "------------", "---------", "-----------"}
};

const vector<vector<string>> SearchesHeader = {
    { "N", "C Theor", "Search 1", "Search 2", "SearchAll 1", "SearchAll 2"},
    { "-", "-------", "--------", "--------", "-----------", "-----------"}
};
#endif // !TABLE_HEADERS_H