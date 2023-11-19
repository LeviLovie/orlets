cmake_minimum_required(VERSION 3.8.0)
project(orlets VERSION 0.0.0 LANGUAGES C CXX)
enable_testing()

configure_file (
  "${PROJECT_SOURCE_DIR}/cfg/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)
include_directories("${PROJECT_BINARY_DIR}")

# file(GLOB BOARD_SRC src/board/*.cpp)
# add_library(board ${BOARD_SRC})

# Orlets
add_executable(orlets src/main.cpp)
# target_link_libraries(orlets board gfx)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
