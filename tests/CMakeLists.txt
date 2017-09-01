# Prepare "Catch" library for other executables
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE catch.hpp)

include_directories(${TEST_SOURCE_DIR}/src)

# Make test executable
add_executable(tests main.cpp)
target_link_libraries(tests Catch MyString)
