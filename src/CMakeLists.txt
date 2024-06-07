add_library(application)

find_package(glfw3 REQUIRED)

target_sources(application PRIVATE
    application.cpp
    window.cpp)

target_include_directories(application PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${glfw3_INCLUDE_DIRS}
)
target_link_libraries(application INTERFACE
    ${glfw3_LIBRARIES}
)