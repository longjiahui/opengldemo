cmake_minimum_required(VERSION 3.24)

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")
message(STATUS ${CMAKE_TOOLCHAIN_FILE})

project(demo)

find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Stb REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)
# lib_cef_dll_wrapper
# set(CEF_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/lib/cef")
# list(APPEND CMAKE_MODULE_PATH "${CEF_ROOT}/cmake")
# find_package(CEF REQUIRED)
# add_subdirectory(./lib/cef/libcef_dll)
message(STATUS )
add_executable(demo)
target_sources(demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/win/application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/win/window.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/gl/glbase.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gl/mesh.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gl/program.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gl/pipeline.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gl/image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/gl/texture.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/gl/huigl.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/util.cpp
)

# set(CEF_TARGET libcef_dll_wrapper)
target_link_libraries(demo PUBLIC
    glfw
    GLEW::GLEW
    assimp::assimp
)

target_include_directories(demo PUBLIC
    # ${CEF_ROOT}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    glfw
    GLEW::GLEW
    ${Stb_INCLUDE_DIR}
    glm::glm-header-only
    assimp::assimp
)

list(APPEND move_dirs glsl image)
foreach(dir IN LISTS move_dirs)
    file(REMOVE ${CMAKE_BINARY_DIR}/${dir})
    file(COPY ${dir} DESTINATION ${CMAKE_BINARY_DIR})
endforeach()

# configure_file("glsl/vertex.glsl" ${CMAKE_BINARY_DIR}/vertex.glsl COPYONLY)