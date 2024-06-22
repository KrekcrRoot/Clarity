cmake_minimum_required(VERSION 3.28)
project(clarity)

include_directories(include)

file(GLOB SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

set(CMAKE_CXX_STANDARD 17)

add_library(clarity STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} -static)
