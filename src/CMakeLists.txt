add_library(MyString MyString.h MyString.cpp)
add_executable(cpp_my_string main.cpp)
target_link_libraries(cpp_my_string MyString)
