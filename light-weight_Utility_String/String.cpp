#include "String.hpp"
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

namespace NP
{
    String::String(): data(new char[1]), length(0)
    {
        data[0] = '\0';
    }

    String::String(const char* str)
    {
        if (str)
        {
            length = strlen(str);
            data = new char[length + 1];
            strcpy_s(data, length + 1, str);
        }
        else 
        {
            data = new char[1];
            data[0] = '\0';
            length = 0;
        }
    }

    String::String(const String& other): data(new char[other.length + 1]), length(other.length)
    {
        strcpy_s(data, length + 1, other.data);
    }

    String::~String()
    {
        delete[] data;
    }

    String& String::operator=(const String& other)
    {
        if (this != &other) 
        {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy_s(data, length + 1, other.data);
        }
        return *this;
    }

    char String::operator[](size_t index) const
    {
        assert(index < length && "Invalid operator[]");
        return data[index];
    }

    String String::operator+(const String& other) const
    {
        size_t newLength = length + other.length;
        char* newData = new char[newLength + 1];

        strcpy_s(newData, newLength + 1, data);
        strcat_s(newData, newLength + 1, other.data);

        String result(newData);
        delete[] newData;

        return result;
    }

    bool String::operator==(const String& other) const
    {
        return strcmp(data, other.data) == 0;
    }

    bool String::operator!=(const String& other) const
    {
        return !(*this == other);
    }

    bool String::operator<(const String& other) const
    {
        return strcmp(data, other.data) < 0;
    }

    bool String::operator>(const String& other) const
    {
        return strcmp(data, other.data) > 0;
    }

    size_t String::getLength() const
    {
        return length;
    }

    const char* String::getCString() const
    {
        return data;
    }

    char String::charAt(size_t index) const
    {
        assert(index < length && "Invalid charAt");
        return data[index];
    }

    int String::compare(const String& other) const
    {
        return strcmp(data, other.data);
    }

    bool String::equals(const String& other) const
    {
        return *this == other;
    }

    bool String::isEmpty() const
    {
        return length == 0;
    }

    String String::substring(size_t start, size_t end) const
    {
        assert(start <= end && end <= length && "Invalid substring");

        size_t subLength = end - start;
        char* subData = new char[subLength + 1];
        strncpy_s(subData, subLength + 1, data + start, subLength);
        subData[subLength] = '\0';

        String result(subData);
        delete[] subData;

        return result;
    }
}