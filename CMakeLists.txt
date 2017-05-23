cmake_minimum_required(VERSION 3.7)

project(CAL_URGENCIAS)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCE_FILES
        "src/*.h"
        "src/*.cpp"
        )

link_libraries(ws2_32 wsock32)

add_executable(CAL_URGENCIAS ${SOURCE_FILES} src/Matcher.cpp src/Matcher.h)