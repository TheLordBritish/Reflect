# CMake generated Testfile for 
# Source directory: C:/Users/Benjamin/Documents/repos/Reflect
# Build directory: C:/Users/Benjamin/Documents/repos/Reflect
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(reflect_tests "C:/Users/Benjamin/Documents/repos/Reflect/Debug/reflect_test.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(reflect_tests "C:/Users/Benjamin/Documents/repos/Reflect/Release/reflect_test.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(reflect_tests "C:/Users/Benjamin/Documents/repos/Reflect/MinSizeRel/reflect_test.exe")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(reflect_tests "C:/Users/Benjamin/Documents/repos/Reflect/RelWithDebInfo/reflect_test.exe")
else()
  add_test(reflect_tests NOT_AVAILABLE)
endif()
