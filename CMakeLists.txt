# CMakeList.txt : CMake project for macro_generator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source to this project's executable.
add_executable (macro_generator "macro_generator.cpp" "macro_generator.h")

# TODO: Add tests and install targets if needed.


