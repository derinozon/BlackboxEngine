#vcpkc install glfw3 assimp entt

cmake_minimum_required(VERSION 3.21)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE Debug)
# set(CMAKE_TOOLCHAIN_FILE "/usr/local/Cellar/vcpkg/2021.05.12/libexec/scripts/buildsystems/vcpkg.cmake")
project(main)




# FIND PACKAGES #
find_package(glfw3 CONFIG REQUIRED)
find_package(ASSIMP CONFIG REQUIRED)

if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif()

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
add_library(main SHARED engine.cpp ${src})
target_include_directories(main PUBLIC ./include ./src)
target_link_libraries(main PRIVATE glfw ${ASSIMP_LIBRARIES})

# BUILD DEMO EXECUTABLE #
link_directories("./build")
add_executable(app main.cpp)
target_include_directories(app PUBLIC ./ ./include ./src)
target_link_libraries(app PRIVATE main glfw ${ASSIMP_LIBRARIES})