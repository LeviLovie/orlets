cmake_minimum_required(VERSION 3.8.0)
project(orlets VERSION 0.0.1 LANGUAGES C CXX)
enable_testing()

configure_file (
  "${PROJECT_SOURCE_DIR}/cfg/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

file(GLOB Sources src/*.c src/*.cpp)
add_executable(orlets ${Sources})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
