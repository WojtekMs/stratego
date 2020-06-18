cmake_minimum_required(VERSION 3.1)

project(stratego)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_COMPILER /usr/bin/clang++)

file(GLOB main_SRC
        "src/*.cpp"
        )

set(SOURCE_FILES ${main_SRC})

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR})

add_executable(main ${SOURCE_FILES})
include_directories(include)


set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})
find_package(SFML 2.4 COMPONENTS graphics window system REQUIRED)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(main ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${SFML_WINDOW_LIBRARY_DEBUG} ${SFML_GRAPHICS_LIBRARY_DEBUG} ${SFML_SYSTEM_LIBRARY_DEBUG})
endif ()
