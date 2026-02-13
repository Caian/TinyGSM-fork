cmake_minimum_required(VERSION 3.12)

set(TINY_GSM_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE SOURCES
    ${TINY_GSM_ROOT_DIR}/src/*.tpp
    ${TINY_GSM_ROOT_DIR}/src/ArduinoCompat/*.c
    ${TINY_GSM_ROOT_DIR}/src/ArduinoCompat/*.cpp)

idf_component_register(SRCS ${SOURCES} INCLUDE_DIRS "src" REQUIRES driver)
