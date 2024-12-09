#pragma once

#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

#include <string>

struct CustomString {
private:
    char* _data;
    int _size;
    
public:
    CustomString(const char* chars);
    CustomString(const std::string& str);
    ~CustomString();

    int FindSubstringBruteForce(const CustomString& substring, int& c) const;
    int FindSubstringRabinKarp(const CustomString& substring, int& c) const;

    int GetSize() const;
    std::string ToString() const;
};

#endif // !CUSTOM_STRING_H
