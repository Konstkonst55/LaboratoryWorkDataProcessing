#include "CustomString.h"
#include <cstring>

CustomString::CustomString(const char* chars) {
    _size = std::strlen(chars);
    _data = new char[_size];
    std::memcpy(_data, chars, _size); 
}

CustomString::CustomString(const std::string& str) {
    _size = str.size();
    _data = new char[_size];
    std::memcpy(_data, str.c_str(), _size);
}

CustomString::~CustomString() {
    delete[] _data;
}

int CustomString::FindSubstringBruteForce(const CustomString& substring, int& c) const {
    c = 0;
    int n = _size, m = substring._size;

    if (m > n) {
        return -1;
    }

    for (int i = 0; i <= n - m; i++) {
        int j;

        for (j = 0; j < m; j++) {
            c++;
            if (_data[i + j] != substring._data[j]) {
                break;
            }
        }

        if (j == m) {
            return i; 
        }
    }

    return -1;
}

int CustomString::FindSubstringRabinKarp(const CustomString& substring, int& c) const {
    c = 0;
    const int prime = 31, mod = 1e9 + 7;
    int n = _size, m = substring._size;

    if (m > n) {
        return -1;
    }

    unsigned long long targetHash = 0, currentHash = 0, power = 1;

    for (int i = 0; i < m; i++) {
        targetHash = (targetHash * prime + (unsigned char)substring._data[i]) % mod;
        currentHash = (currentHash * prime + (unsigned char)_data[i]) % mod;

        if (i < m - 1) {
            power = (power * prime) % mod;
        }
    }

    for (int i = 0; i <= n - m; i++) {
        if (currentHash == targetHash) {
            bool match = true;

            for (int j = 0; j < m; j++) {
                c++;
                if (_data[i + j] != substring._data[j]) {
                    match = false;
                    break;
                }
            }

            if (match) {
                return i;
            }
        }

        if (i < n - m) {
            currentHash = (currentHash - ((_data[i] % mod) * power % mod) + mod) % mod;
            currentHash = (currentHash * prime + _data[i + m]) % mod;
        }
    }

    return -1;
}

int CustomString::GetSize() const {
    return _size;
}

std::string CustomString::ToString() const {
    return std::string(_data, _size);
}