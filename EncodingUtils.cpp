#include "EncodingUtils.h"
#include <functional>
#include <utility>
#include <cstring>
#include <iomanip>

ShannonCoding::ShannonCoding(const char* inputText) {
    strncpy(_text, inputText, _maxTextLen);
    CalculateFrequencies();
    CalculateEntropy();
    Build();
}

void ShannonCoding::QuickSortSymbols(SymbolInfo symbols[], size_t size) {
    std::function<void(int, int)> SortRecursive;

    SortRecursive = [&symbols, &SortRecursive](int left, int right) {
        if (left >= right) return;

        SymbolInfo pivot = symbols[left];
        int i = left, j = right;

        while (i <= j) {
            while (symbols[i] < pivot) {
                i++;
            }

            while (pivot < symbols[j]) {
                j--;
            }

            if (i <= j) {
                std::swap(symbols[i], symbols[j]);
                i++;
                j--;
            }
        }

        if (left < j) SortRecursive(left, j);
        if (i < right) SortRecursive(i, right);
    };

    if (size > 0) {
        SortRecursive(0, (int)size - 1);
    }
}

void ShannonCoding::CalculateFrequencies() {
    int frequencies[_maxSymbols] = { 0 };
    size_t total = strlen(_text);

    for (size_t i = 0; i < total; i++) {
        unsigned char c = _text[i];
        frequencies[c]++;
    }

    for (size_t i = 0; i < _maxSymbols; i++) {
        if (frequencies[i] > 0) {
            _symbols[_symbolCount].symbol = static_cast<char>(i);
            _symbols[_symbolCount].probability = static_cast<double>(frequencies[i]) / total;
            _symbols[_symbolCount].code.length = 0;
            _symbolCount++;
        }
    }
}

void ShannonCoding::CalculateEntropy() {
    for (size_t i = 0; i < _symbolCount; i++) {
        double p = _symbols[i].probability;
        _entropy -= p * log2(p);
    }
}

void ShannonCoding::Build() {
    QuickSortSymbols(_symbols, _symbolCount);

    double cumulativeProbability = 0.0;

    for (size_t i = 0; i < _symbolCount; i++) {
        double probability = _symbols[i].probability;
        size_t codeLength = static_cast<size_t>(ceil(-log2(probability)));
        _symbols[i].code.length = codeLength;
        double value = cumulativeProbability;

        for (size_t j = 0; j < codeLength; j++) {
            value *= 2.0;

            if (value >= 1.0) {
                _symbols[i].code.data[j] = 1;
                value -= 1.0;
            }
            else {
                _symbols[i].code.data[j] = 0;
            }
        }

        for (size_t j = codeLength; j < _maxCodeLen; j++) {
            _symbols[i].code.data[j] = 0;
        }

        cumulativeProbability += probability;
    }
}

const char* ShannonCoding::GetText() const {
    return _text;
}

size_t ShannonCoding::GetTextLength() const {
    return _maxTextLen;
}

const SymbolInfo* ShannonCoding::GetSymbols() const {
    return _symbols;
}

const SymbolInfo& ShannonCoding::GetSymbol(size_t index) const {
    if (index >= _symbolCount) {
        throw std::out_of_range("Index was out of range!");
    }

    return _symbols[index];
}

size_t ShannonCoding::GetSymbolCount() const {
    return _symbolCount;
}

double ShannonCoding::GetKraftInequality() {
    double sum = 0.0;

    for (size_t i = 0; i < _symbolCount; i++) {
        sum = pow(2, -(int)_symbols[i].code.length);
    }

    return sum;
}

double ShannonCoding::GetEntropy() {
    return _entropy;
}

double ShannonCoding::GetAverageCodeLength() {
    double avgLength = 0.0;

    for (size_t i = 0; i < _symbolCount; i++) {
        avgLength += _symbols[i].probability * _symbols[i].code.length;
    }

    return avgLength;
}

double ShannonCoding::GetRedundancy() {
    return GetAverageCodeLength() - _entropy;
}
