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
# Example 1 setup
#====================
set (FILES_DIR "${CMAKE_SOURCE_DIR}/examples/1_basic_class_exposure")

set (HEADER_FILES "${FILES_DIR}/entity.hpp")
set (SOURCE_FILES "${FILES_DIR}/entity.cpp"
                  "${FILES_DIR}/main.cpp")

# Set the name of the test executable and its source files. 
add_executable(example_1 ${HEADER_FILES} ${SOURCE_FILES})
# Set linker language to C++.
set_target_properties(example_1 PROPERTIES LINKER_LANGUAGE CXX)