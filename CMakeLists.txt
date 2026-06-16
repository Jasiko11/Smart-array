cmake_minimum_required(VERSION 3.20)
project(SmartArrayApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG main # Important: Specify a version or a commit hash here.
)
FetchContent_MakeAvailable(ftxui)

add_library(SmartArray
        src/smartArray/SmartArray.h)

target_link_libraries(SmartArray
        ftxui::screen
        ftxui::component
        ftxui::dom
        ftxui::component)
# Dodaj plik nagłówkowy jeśli potrzebujesz, ale nie jest wymagane w CMakeLists.txt

add_executable(SmartArrayApp
        src/app/Manager.cpp
        src/app/TuiInterface.cpp
        src/app/main.cpp)

# Podłącz bibliotekę FTXUI (komponent i dom są wymagane dla GUI)
target_link_libraries(SmartArrayApp
        ftxui::screen
        ftxui::component
        ftxui::dom
        ftxui::component)
target_include_directories(SmartArrayApp PRIVATE include model
        src/app
        src/smartArray)

add_subdirectory(tests)
