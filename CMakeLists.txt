cmake_minimum_required(VERSION 3.10)
#################################
# Настройки проекта
project(System LANGUAGES C CXX)
#################################
# Установка имени выходного файла
set(EXECUTABLE_NAME "system.out")
#################################
# Проверка режима сборки
if(NOT CMAKE_BUILD_TYPE)
	message(STATUS "No default build type specified: setting CMAKE_BUILD_TYPE=Release")
	set(CMAKE_BUILD_TYPE Release CACHE STRING
		"Choose the build type: options are: Debug Release RelWithDebInfo MinSizeRel"
		FORCE)
else(NOT CMAKE_BUILD_TYPE)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		message(STATUS "Build type is set to Debug: Performance will be negatively impacted")
		message(STATUS "Add -DCMAKE_BUILD_TYPE=Release to the CMake command line to get an optimized build")
	endif(CMAKE_BUILD_TYPE STREQUAL "Debug")
endif(NOT CMAKE_BUILD_TYPE)

#################################
# Установка имени для пакета
set(project_library_target_name ${PROJECT_NAME})
set(PACKAGE_NAME TestSystem)

#################################
# Установка опций компилятора
# Установка стандарта С++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++17 support has been enabled by default")
# Установка флагов для warning'ов
set(EXTRA_C_FLAGS "${EXTRA_C_FLAGS}")# -Wall -Wno-narrowing -Wno-deprecated")
# Установка специфичных флагов компилияции с необходимыми оптимизациями
set(EXTRA_CXX_FLAGS "-O2 -fno-tree-vectorize")

#################################
# Сбор флагов в одном месте
set(EXTRA_CXX_FLAGS         "${EXTRA_CXX_FLAGS} ${EXTRA_C_FLAGS}")
set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} ${EXTRA_C_FLAGS}")
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} ${EXTRA_CXX_FLAGS}")

#################################
# Сборка директорий для компиляции
include_directories(system formats gbenchmark/include gtest/googletest/include tests bfp/lib Eigen/Eigen)
add_subdirectory(gbenchmark)
add_subdirectory(gtest)
add_subdirectory(system)
set(SOURCE_FILES
        main.cpp)
add_executable(${EXECUTABLE_NAME} ${TEST_FILES} ${SOURCE_FILES})
target_link_libraries(${EXECUTABLE_NAME} system_lib benchmark gtest)