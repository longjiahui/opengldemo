cmake_minimum_required(VERSION 3.29)
project(demo)

find_package(glfw3 REQUIRED)
# lib_cef_dll_wrapper
# set(CEF_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/cef")
# list(APPEND CMAKE_MODULE_PATH "${CEF_ROOT}/cmake")
# find_package(CEF REQUIRED)
# add_subdirectory(./lib/cef/libcef_dll)

add_executable(demo)
target_sources(demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/window.cpp
)

# set(CEF_TARGET libcef_dll_wrapper)
target_link_libraries(demo PUBLIC
    glfw
)

target_include_directories(demo PUBLIC
    # ${CEF_ROOT}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    glfw
)