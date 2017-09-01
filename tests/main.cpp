#define CATCH_CONFIG_MAIN

#include <sstream>
#include <string>

#include "catch.hpp"
#include "../src/MyString.h"

TEST_CASE("MyString") {
    SECTION("Should construct object using default constructor") {
        MyString str;

        REQUIRE(str.length() == 0);
        REQUIRE(str.c_str() == nullptr);
    }

    SECTION("Should construct object using constructor") {
        MyString str("Hello!");

        REQUIRE(str.length() == 6);
        REQUIRE(std::strncmp(str.c_str(), "Hello!", 6) == 0);
    }

    SECTION("Should copy object using copy constructor") {
        MyString str("Hello!");
        MyString copy(str); // NOLINT

        REQUIRE(copy.length() == 6);
        REQUIRE(std::strncmp(copy.c_str(), "Hello!", 6) == 0);

        REQUIRE(std::strncmp(str.c_str(), "Hello!", 6) == 0);

        REQUIRE(copy.c_str() != str.c_str());
    }

    SECTION("Should move object using move constructor") {
        MyString str("Hello!");
        MyString move(std::move(str));

        REQUIRE(move.length() == 6);
        REQUIRE(std::strncmp(move.c_str(), "Hello!", 6) == 0);

        REQUIRE(str.length() == 0); // NOLINT
        REQUIRE(str.c_str() == nullptr);
    }

    SECTION("Should copy object using copy assignment operator") {
        MyString str("Hello!");
        MyString copy("World!!!");

        copy = str;

        REQUIRE(copy.length() == 6);
        REQUIRE(std::strncmp(copy.c_str(), "Hello!", 6) == 0);

        REQUIRE(std::strncmp(str.c_str(), "Hello!", 6) == 0);

        REQUIRE(copy.c_str() != str.c_str());
    }

    SECTION("Should copy object without reallocating chars buffer "
            "using copy assignment operator if length are the same") {
        MyString str("Hello!");
        MyString copy("World!");

        const char* orig = copy.c_str();

        copy = str;

        REQUIRE(copy.length() == 6);
        REQUIRE(std::strncmp(copy.c_str(), "Hello!", 6) == 0);

        REQUIRE(std::strncmp(str.c_str(), "Hello!", 6) == 0);

        REQUIRE(copy.c_str() != str.c_str());
        REQUIRE(copy.c_str() == orig);
    }

    SECTION("Should move object using move assignment operator") {
        MyString str("Hello!");
        MyString move("World!");

        move = std::move(str);

        REQUIRE(move.length() == 6);
        REQUIRE(std::strncmp(move.c_str(), "Hello!", 6) == 0);

        REQUIRE(str.length() == 0); // NOLINT
        REQUIRE(str.c_str() == nullptr);
    }

    SECTION("Should return new object as concatenation of two object using plus operator") {
        MyString a("Hello, ");
        MyString b("World!");

        MyString str = a + b;

        REQUIRE(str.length() == 13);
        REQUIRE(std::strncmp(str.c_str(), "Hello, World!", 13) == 0);

        REQUIRE(std::strncmp(a.c_str(), "Hello, ", 7) == 0);
        REQUIRE(std::strncmp(b.c_str(), "World!", 6) == 0);

        REQUIRE(str.c_str() != a.c_str());
        REQUIRE(str.c_str() != b.c_str());
    }

    SECTION("Should compare two object using greater operator") {
        REQUIRE(MyString("b") > MyString("a"));
        REQUIRE(MyString("aab") > MyString("aaa"));
        REQUIRE(MyString("aaaaab") > MyString("aa"));
        REQUIRE(MyString("b") > MyString("aaaaaab"));
    }

    SECTION("Should read object from istream using extraction operator") {
        MyString str;
        std::istringstream is(std::string("Hello!"));

        is >> str;

        REQUIRE(str.length() == 6);
        REQUIRE(std::strncmp(str.c_str(), "Hello!", 6) == 0);
    }

    SECTION("Should write object to ostream using insertion operator") {
        MyString str("Hello!");
        std::ostringstream os;

        os << str;

        REQUIRE(os.str().length() == 6);
        REQUIRE(os.str() == "Hello!");
    }
}
