#pragma once

#ifndef ENCODING_UTILS_H
#define ENCODING_UTILS_H

#include <cmath>
#include <stdexcept>
#include <vector>

static const size_t _maxTextLen = 1024, _maxSymbols = 256, _maxCodeLen = 32;

struct Code {
public:
    int data[_maxCodeLen];
    size_t length;
};

struct SymbolInfo {
public:
    char symbol;
    double probability;
    Code code;

    bool operator<(const SymbolInfo& other) const {
        return this->probability > other.probability;
    }
};

class CodeBuilder {
protected:
    char _text[_maxTextLen];
    size_t _symbolCount = 0;
    SymbolInfo _symbols[_maxSymbols];
    double _entropy = 0.0;

    virtual void Initialize();
    void QuickSortSymbols(SymbolInfo symbols[], size_t size);
    virtual void CalculateFrequencies();
    virtual void CalculateEntropy();
    virtual void Build() = 0;

public:
    CodeBuilder();
    CodeBuilder(const char* inputText);

    const char* GetText() const;
    void SetText(const char* text);
    size_t GetTextLength() const;
    const SymbolInfo* GetSymbols() const;
    const SymbolInfo& GetSymbol(size_t index) const;
    size_t GetSymbolCount() const;
    double GetKraftInequality();
    double GetEntropy();
    double GetAverageCodeLength();
    double GetRedundancy();
};

class ShannonCodeBuilder : public CodeBuilder {
private: 
    void Build() override;

public:
    using CodeBuilder::CodeBuilder;
};

class FanoCodeBuilder : public CodeBuilder {
private:
    size_t GetMiddleProbability(size_t left, size_t right) const;
    void Build() override;

public:
    using CodeBuilder::CodeBuilder;
};

class HuffmanCodeBuilder : public CodeBuilder {
private:
    size_t Up(size_t n, std::vector<double>& probabilities, double probability);
    void Down(size_t n, size_t up);
    void Build() override;

public:
    using CodeBuilder::CodeBuilder;
};

#endif // !ENCODING_UTILS_H