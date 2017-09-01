#include <iostream>
#include <vector>
#include <algorithm>

#include "MyString.h"

int main() {
    std::vector<MyString> vec;

    MyString input;
    while (std::cin >> input) {
        vec.emplace_back(input);
    }

    std::sort(vec.begin(), vec.end(), std::greater<>());

    for (auto &str : vec) {
        std::cout << str << std::endl;
    }

    return 0;
}
