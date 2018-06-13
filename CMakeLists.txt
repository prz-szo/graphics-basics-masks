cmake_minimum_required(VERSION 3.8.2)
project(Projekt_GFK_16)
set(EXECUTABLE_NAME "${PROJECT_NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -DWX_PRECOMP")

find_package(wxWidgets COMPONENTS core base REQUIRED)

include(${wxWidgets_USE_FILE})
include_directories(include/ ${wxWidgets_INCLUDE_DIRS})

file(GLOB SOURCE_FILES
        "./*.h"
        "./*.cpp"
        "sources/*.cpp"
        "headers/*.h"
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
