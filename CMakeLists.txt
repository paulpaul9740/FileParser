cmake_minimum_required (VERSION 3.0.2)
set(CMAKE_VERBOSE_MAKEFILE ON)
project (TEST)
find_package( Threads )
add_executable(test main.cpp FileReader.cpp ThreadWorker.cpp Writer.cpp)
set_property(TARGET test PROPERTY CXX_STANDARD 17)
target_link_libraries( test ${CMAKE_THREAD_LIBS_INIT} )

