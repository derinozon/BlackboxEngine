#vcpkc install glfw3 entt
#cmake -DCMAKE_BUILD_TYPE=Debug ..

cmake_minimum_required(VERSION 3.21)
set (CMAKE_CXX_STANDARD 17)
project(main)


find_package(glfw3 CONFIG REQUIRED)
find_package(ASSIMP CONFIG REQUIRED)
if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
	message("Found!")
endif()

if (UNIX)
message("Running command")
execute_process (
    COMMAND bash -c "cp -fR ../res ."
    OUTPUT_VARIABLE outVar
)
endif (UNIX)

file(GLOB src CONFIGURE_DEPENDS "src/*.cpp" "lib/*.cpp")


link_directories("/usr/local/Cellar/assimp/5.0.1/lib")
add_library(main SHARED engine.cpp ${src})
#add_executable(main main.cpp engine.cpp ${src})
target_include_directories(main PUBLIC ./include ./src)
target_link_libraries(main PRIVATE glfw ${ASSIMP_LIBRARIES})

link_directories("./build")
add_executable(app main.cpp)
target_include_directories(app PUBLIC ./ ./include ./src)
target_link_libraries(app PRIVATE main glfw ${ASSIMP_LIBRARIES})