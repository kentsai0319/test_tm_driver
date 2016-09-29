project(tm_socket_test)

#include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
#CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
#if(COMPILER_SUPPORTS_CXX11)
#    set(CMAKE_CXX_FLAGS "-std=c++11")
#elseif(COMPILER_SUPPORTS_CXX0X)
#    set(CMAKE_CXX_FLAGS "-std=c++0x")
#else()
#    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler. Suggested solution: update the pkg build-essential ")
#endif()
set(CMAKE_CXX_FLAGS "-std=c++11 -pthread")

add_executable(tm_socket_test src/tm_print.cpp src/tm_robot_state_rt.cpp src/tm_communication.cpp src/tm_driver.cpp test_tm_driver.cpp)

install(TARGETS tm_socket_test RUNTIME DESTINATION bin)
