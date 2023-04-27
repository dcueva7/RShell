
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
src/main.cpp
header/Command.hpp
header/and.hpp
header/or.hpp
header/semi.hpp
header/Node.hpp
header/paren.hpp
header/test.hpp
header/outrd.hpp
header/pipe.hpp
header/inrd.hpp
header/twooutrd.hpp
)
ADD_EXECUTABLE(test 
   unit_tests/unit_tests.cpp
)




TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)

