cmake_minimum_required(VERSION 3.24)
project(demo)

find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)
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
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gl/context.cpp
)

# set(CEF_TARGET libcef_dll_wrapper)
target_link_libraries(demo PUBLIC
    glfw
    GLEW::GLEW
)

target_include_directories(demo PUBLIC
    # ${CEF_ROOT}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    glfw
    GLEW::GLEW
)