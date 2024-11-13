#pragma once

#ifndef ENCODING_UTILS_H
#define ENCODING_UTILS_H

#include <cmath>
#include <stdexcept>

static const size_t _maxTextLen = 1024, _maxSymbols = 256, _maxCodeLen = 32;

struct Code {
    int data[_maxCodeLen];
    size_t length;
};

struct SymbolInfo {
    char symbol;
    double probability;
    Code code;

    bool operator<(const SymbolInfo& other) const {
        return this->probability > other.probability;
    }
};

class ShannonCoding {
private:
    char _text[_maxTextLen];
    size_t _symbolCount = 0;
    SymbolInfo _symbols[_maxSymbols];
    double _entropy = 0.0;

    void QuickSortSymbols(SymbolInfo symbols[], size_t size);
    void CalculateFrequencies();
    void CalculateEntropy();
    void Build();

public:
    ShannonCoding(const char* inputText);

    const char* GetText() const;
    size_t GetTextLength() const;
    const SymbolInfo* GetSymbols() const;
    const SymbolInfo& GetSymbol(size_t index) const;
    size_t GetSymbolCount() const;
    double GetKraftInequality();
    double GetEntropy();
    double GetAverageCodeLength();
    double GetRedundancy();
};

#endif // !ENCODING_UTILS_H