#ifndef CPP_MY_STRING_MYSTRING_H
#define CPP_MY_STRING_MYSTRING_H


#include <memory>

#define MAX_CHARS_FROM_ISTREAM (1 * 1024 * 1014)

class MyString
{
public:
    MyString();
    explicit MyString(const char* str);

    MyString(const MyString& str);
    MyString(MyString&& str) noexcept;

    MyString& operator=(const MyString& str);
    MyString& operator=(MyString&& str) noexcept;

    size_t length() const noexcept;
    const char* c_str() const noexcept;

    friend bool operator>(const MyString& lhs, const MyString& rhs);
    friend MyString operator+(const MyString& lhs, const MyString& rhs);

    friend std::istream& operator>>(std::istream& is, MyString& str);
    friend std::ostream& operator<<(std::ostream& os, const MyString& str);

private:
    size_t _length;
    std::unique_ptr<char[]> _chars;
};


#endif //CPP_MY_STRING_MYSTRING_H
