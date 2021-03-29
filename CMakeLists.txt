cmake_minimum_required (VERSION 3.0.2)
set(CMAKE_VERBOSE_MAKEFILE ON)
project (FileParser)
find_package( Threads )
add_executable(FileParser main.cpp FileReader.cpp ThreadWorker.cpp Writer.cpp)
set_property(TARGET FileParser PROPERTY CXX_STANDARD 17)
target_link_libraries( FileParser ${CMAKE_THREAD_LIBS_INIT} )

