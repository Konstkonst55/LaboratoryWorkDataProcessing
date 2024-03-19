#pragma once

#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <stdio.h>

using namespace std;

void CreateTable(const vector<vector<string>>& table);
void FillTable(vector<vector<string>>& table, vector<vector<string>>& data, const int start = 0, const int step = 1);

#endif // !TABLE_H