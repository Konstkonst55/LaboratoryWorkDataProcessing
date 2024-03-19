
#include "Table.h"

void CreateTable(const vector<vector<string>>& table)
{
    vector<size_t> columnWidths;

    for (size_t col = 0; col < table[0].size(); ++col) {
        size_t maxWidth = 0;

        for (size_t row = 0; row < table.size(); ++row) maxWidth = max(maxWidth, table[row][col].length());

        columnWidths.push_back(maxWidth);
    }

    printf("\n");

    for (const auto& row : table) {
        printf("| ");

        for (size_t col = 0; col < row.size(); ++col) {
            printf(row[col].c_str());

            for (size_t i = row[col].length(); i < columnWidths[col]; ++i) printf(" ");
            
            printf(" | ");
        }

        printf("\n");
    }

    printf("\n\n");
}

void FillTable(vector<vector<string>>& table, vector<vector<string>>& data, const int start, const int step) {
    int rowCounter = start;

    for (auto it = data.begin(); it != data.end(); it++) {
        if (++rowCounter == step) {
            table.insert(table.end(), *it);
            rowCounter = 0;
        }
    }
}
