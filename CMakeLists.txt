#vcpkc install glfw3 assimp entt
#cmake .. -G "MinGW Makefiles"

cmake_minimum_required(VERSION 3.21)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE Debug)
# set (CMAKE_BUILD_TYPE Release)
# set(CMAKE_TOOLCHAIN_FILE "/usr/local/Cellar/vcpkg/2021.05.12/libexec/scripts/buildsystems/vcpkg.cmake")
project(main)


include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp
)

# FetchContent_GetProperties(assimp)
# if(NOT glfw_POPULATED)
#     FetchContent_Populate(assimp)
# 
#     add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
# endif()

# FIND PACKAGES #
# find_package(glfw3 CONFIG REQUIRED)
# find_package(ASSIMP CONFIG REQUIRED)

#if(ASSIMP_FOUND)
include_directories(${ASSIMP_INCLUDE_DIR})
#endif()

if (UNIX)
message("Running command")
execute_process (
    COMMAND bash -c "cp -fR ../res ."
    OUTPUT_VARIABLE outVar
)
endif (UNIX)


# GET SOURCE #
file(GLOB src CONFIGURE_DEPENDS "src/*.cpp" "lib/*.cpp" "lib/ImGUI/*.cpp")

# ASSIMP dependencies fail to build on mac Error: Building package irrlicht:x64-osx failed with: BUILD_FAILED
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	link_directories("/usr/local/Cellar/assimp/5.0.1/lib")
endif()

# BUILD ENGINE AS SHARED LIBRARY #
# add_library(main SHARED engine.cpp ${src})
# target_include_directories(main PUBLIC ./include ./src)
# target_link_libraries(main PRIVATE glfw ${ASSIMP_LIBRARIES})

# BUILD ENGINE AS STATIC LIBRARY #
add_library(main STATIC engine.cpp ${src})
target_include_directories(main PUBLIC ./include ./src)
target_link_libraries(main PRIVATE glfw ${ASSIMP_LIBRARIES})

# BUILD DEMO EXECUTABLE #
link_directories("./build")
add_executable(app main.cpp)
target_include_directories(app PUBLIC ./ ./include ./src)
target_link_libraries(app PRIVATE main glfw ${ASSIMP_LIBRARIES})

#if (WIN32)
#target_link_options(app PRIVATE -mwindows)
#endif (WIN32)