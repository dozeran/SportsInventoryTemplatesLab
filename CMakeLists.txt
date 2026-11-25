
cmake_minimum_required(VERSION 3.20)

project(SportsInventoryTemplatesLab VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
include(FetchContent)

# Завантаження GoogleTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

# Основна програма
add_executable(SportsInventoryTemplatesLab
    src/main.cpp
)

target_include_directories(SportsInventoryTemplatesLab PRIVATE
    src
)

# Модульні тести
add_executable(test_templates
    tests/test_templates.cpp
)

target_include_directories(test_templates PRIVATE
    src
)

target_link_libraries(test_templates
    PRIVATE
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_templates)

# Попередження компілятора
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    foreach(target SportsInventoryTemplatesLab test_templates)
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic
        )
    endforeach()
endif()

# Перевірка пам'яті та невизначеної поведінки
option(ENABLE_SANITIZERS "Enable sanitizers" OFF)

if(ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    foreach(target SportsInventoryTemplatesLab test_templates)
        target_compile_options(${target} PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )

        target_link_options(${target} PRIVATE
            -fsanitize=address,undefined
        )
    endforeach()
endif()
