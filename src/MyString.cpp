#include <iostream>
#include <cstring>
#include <memory>

#include "MyString.h"

MyString::MyString() :
    _length(0),
    _chars(nullptr)
{}

MyString::MyString(const char* str)
{
    _length = std::strlen(str);

    _chars = std::make_unique<char[]>(_length + 1);
    std::strncpy(_chars.get(), str, _length + 1);
}

MyString::MyString(const MyString& str) :
    _length(str._length),
    _chars(new char[str._length + 1])
{
    std::strncpy(_chars.get(), str._chars.get(), _length + 1);
}

MyString::MyString(MyString&& str) noexcept :
    _length(str._length),
    _chars(std::move(str._chars))
{
    str._length = 0;
    str._chars = nullptr;
}

MyString& MyString::operator=(const MyString& str)
{
    if (this != &str) {
        if (_length != str._length) {
            _chars = nullptr;
            _length = str._length;
            _chars = (_length > 0) ? std::make_unique<char[]>(_length + 1) : nullptr;
        }

        std::strncpy(_chars.get(), str._chars.get(), _length + 1);
    }

    return *this;
}

MyString& MyString::operator=(MyString&& str) noexcept
{
    if (this != &str) {
        _chars = nullptr;
        _length = str._length;
        _chars = std::move(str._chars);

        str._chars = nullptr;
        str._length = 0;
    }

    return *this;
}

size_t MyString::length() const noexcept
{
    return _length;
}

const char* MyString::c_str() const noexcept
{
    return _chars.get();
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
    auto max = std::max(lhs.length(), rhs.length());
    return std::strncmp(lhs.c_str(), rhs.c_str(), max) > 0;
}

MyString operator+(const MyString &lhs, const MyString &rhs)
{
    MyString str;

    str._length = lhs._length + rhs._length;
    str._chars = std::make_unique<char[]>(str._length + 1);

    std::strncpy(str._chars.get(), lhs._chars.get(), lhs._length + 1);
    std::strncat(str._chars.get(), rhs._chars.get(), rhs._length + 1);

    return str;
}

std::istream &operator>>(std::istream &is, MyString &str)
{
    char tmp[MAX_CHARS_FROM_ISTREAM];
    is.getline(tmp, MAX_CHARS_FROM_ISTREAM);

    str = MyString(tmp);

    return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
    return os << str.c_str();
}
