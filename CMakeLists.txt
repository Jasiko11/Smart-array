cmake_minimum_required(VERSION 3.15)
project(SmartArrayStudentManager CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include(FetchContent)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
        GIT_TAG main
)
FetchContent_MakeAvailable(ftxui)

set(SOURCES
        include/App/main.cpp
        include/App/Manager.cpp
        include/App/TuiInterface.cpp
        include/App/TuiInterface.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/App
)

target_link_libraries(${PROJECT_NAME} PRIVATE ftxui::screen ftxui::dom ftxui::component)