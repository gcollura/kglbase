project(kglbase)
cmake_minimum_required(VERSION 2.8)

# Define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

find_package(PkgConfig REQUIRED)

find_package(KGLT REQUIRED)
find_package(KAZMATH REQUIRED)
find_package(Lua51 REQUIRED)

pkg_check_modules(SIGC sigc++-2.0 REQUIRED)

add_definitions("-Wall -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include_directories(
    ${KGLT_INCLUDE_DIRS}
    ${KAZMATH_INCLUDE_DIRS}
    ${SIGC_INCLUDE_DIRS}
    ${LUA_INCLUDE_DIR}
)

link_libraries(
    ${KGLT_LIBRARIES}
    ${KAZMATH_LIBRARIES}
    ${SIGC_LIBRARIES}
    ${LUA_LIBRARIES}
)

aux_source_directory(src SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/ DESTINATION ${CMAKE_BINARY_DIR}/data/)
