#include "EncodingUtils.h"
#include <functional>
#include <utility>
#include <cstring>
#include <iomanip>

CodeBuilder::CodeBuilder() { }

CodeBuilder::CodeBuilder(const char* inputText) {
    strncpy(_text, inputText, _maxTextLen);
    Initialize();
}

void CodeBuilder::Initialize() {
    CalculateFrequencies();
    CalculateEntropy();
    Build();
}

void CodeBuilder::QuickSortSymbols(SymbolInfo symbols[], size_t size) {
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

void CodeBuilder::CalculateFrequencies() {
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

void CodeBuilder::CalculateEntropy() {
    for (size_t i = 0; i < _symbolCount; i++) {
        double p = _symbols[i].probability;
        _entropy -= p * log2(p);
    }
}

const char* CodeBuilder::GetText() const {
    return _text;
}

void CodeBuilder::SetText(const char* text) {
    strncpy(_text, text, _maxTextLen);
    Initialize();
}

size_t CodeBuilder::GetTextLength() const {
    return _maxTextLen;
}

const SymbolInfo* CodeBuilder::GetSymbols() const {
    return _symbols;
}

const SymbolInfo& CodeBuilder::GetSymbol(size_t index) const {
    if (index >= _symbolCount) {
        throw std::out_of_range("Index was out of range!");
    }

    return _symbols[index];
}

size_t CodeBuilder::GetSymbolCount() const {
    return _symbolCount;
}

double CodeBuilder::GetKraftInequality() {
    double sum = 0.0;

    for (size_t i = 0; i < _symbolCount; i++) {
        sum = pow(2, -(int)_symbols[i].code.length);
    }

    return sum;
}

double CodeBuilder::GetEntropy() {
    return _entropy;
}

double CodeBuilder::GetAverageCodeLength() {
    double avgLength = 0.0;

    for (size_t i = 0; i < _symbolCount; i++) {
        avgLength += _symbols[i].probability * _symbols[i].code.length;
    }

    return avgLength;
}

double CodeBuilder::GetRedundancy() {
    return GetAverageCodeLength() - _entropy;
}

void ShannonCodeBuilder::Build() {
    if (_symbolCount == 0) return;

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

void FanoCodeBuilder::Build() {
    if (_symbolCount == 0) return;

    QuickSortSymbols(_symbols, _symbolCount);

    auto GetMiddleProbability = [&](size_t left, size_t right) -> size_t {
        double leftSum = 0, rightSum = _symbols[right].probability;
        size_t point = right;

        for (int i = left; i <= right - 1; i++) {
            leftSum += _symbols[i].probability;
        }

        if (leftSum == 0) return 0;

        while (leftSum >= rightSum && (double)point > left) {
            point--;
            leftSum -= _symbols[point].probability;
            rightSum += _symbols[point].probability;
        }

        return point;
    };

    std::function<void(size_t, size_t, size_t)> BuildFanoRecursive = [&](size_t left, size_t right, size_t depth) {
        if (left >= right) return;

        size_t middle = GetMiddleProbability(left, right);

        for (size_t i = left; i <= middle; i++) {
            _symbols[i].code.data[depth] = 0;
            _symbols[i].code.length = depth + 1;
        }

        for (size_t i = middle + 1; i <= right; i++) {
            _symbols[i].code.data[depth] = 1;
            _symbols[i].code.length = depth + 1;
        }

        BuildFanoRecursive(left, middle, depth + 1);
        BuildFanoRecursive(middle + 1, right, depth + 1);
    };

    BuildFanoRecursive(0, _symbolCount - 1, 0);
}
