# Reflect Library
# 2017 - Benjamin Carter (bencarterdev@outlook.com)
#
# This software is provided 'as-is', without any express or implied warranty.
# In no event will the authors be held liable for any damages arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it freely,
# subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented;
#    you must not claim that you wrote the original software.
#    If you use this software in a product, an acknowledgement
#    in the product documentation would be appreciated but is not required.
#
# 2. Altered source versions must be plainly marked as such,
#    and must not be misrepresented as being the original software.
#
# 3. This notice may not be removed or altered from any source distribution.

#====================
# Setup
#====================
# Minimum needed for C++14 flags and standards.
cmake_minimum_required(VERSION 3.1.0)
# The name of the project.
project(Reflect)
# Individual version numbers of the engine.
set(REFLECT_MAJOR_VERSION 1)
set(REFLECT_MINOR_VERSION 0)
set(REFLECT_PATCH_VERSION 0)
# Concatenated application version.
set(REFLECT_VERSION ${REFLECT_MAJOR_VERSION}.${REFLECT_MINOR_VERSION}.${REFLECT_PATCH_VERSION})

# Set compiler flags
# Set C++ version to 14.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#====================
# Include directories
#====================
# Reflect library includes
include_directories("${CMAKE_SOURCE_DIR}/include")

#====================
# Libraries
#====================
########################################
# Catch [Unit-testing framework].
set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib/catch/include)
# Create the library.
add_library(catch INTERFACE)
# Link the catch header files.
target_include_directories(catch INTERFACE ${CATCH_INCLUDE_DIR})

#====================
# Executables
#====================
########################################
# Unit test executable.
set(TEST_HEADER_FILES ${CMAKE_SOURCE_DIR}/tests/test_object.hpp)
set(TEST_SOURCE_FILES ${CMAKE_SOURCE_DIR}/tests/test_main.cpp)
# Set the name of the test executable and its source files. 
add_executable(reflect_test ${TEST_HEADER_FILES} ${TEST_SOURCE_FILES})

# Set linker language to C++.
set_target_properties(reflect_test PROPERTIES LINKER_LANGUAGE CXX)
# Link the libraries to test executable.
target_link_libraries(reflect_test catch)

# Enable testing and link it to CTest framework.
enable_testing(true)
add_test(NAME reflect_tests COMMAND reflect_test)