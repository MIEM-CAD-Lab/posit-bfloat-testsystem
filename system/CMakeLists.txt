cmake_minimum_required(VERSION 3.10)
project(TestSystemLib)

set(SOURCE_FILES
        include/test_manager.h
        include/test_set.h
        include/test.h
        include/test_data.h
        include/data_bank.h
        src/test_manager.cpp
        src/test_set.cpp
        src/test.cpp
        src/test_data.cpp
        )

include_directories(include)

add_library(system_lib STATIC ${SOURCE_FILES})
target_include_directories(system_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
