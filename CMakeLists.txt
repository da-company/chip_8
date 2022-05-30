CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

project(chip_emu)

SET(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*/*.cpp ${PROJECT_SOURCE_DIR}/*/*.hpp)

add_executable(chip_emu ${SRC_FILES})

find_library(SDL2 SDL2 ${PROJECT_SOURCE_DIR}/frameworks)
target_link_libraries(chip_emu ${SDL2})