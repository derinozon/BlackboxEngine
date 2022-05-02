cmake_minimum_required(VERSION 3.21)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_BUILD_TYPE Debug)
# set (CMAKE_BUILD_TYPE Release)
project(blackbox)

include(FetchContent)

if(NOT WIN32)
	string(ASCII 27 Esc)
	set(ColorReset "${Esc}[m")
	set(ColorBold  "${Esc}[1m")
	set(BoldCyan   "${Esc}[1;36m")
endif()
message("${BoldCyan}Building dependencies, this might take a while${ColorReset}")

FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw
)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES FALSE)
	set(GLFW_BUILD_TESTS FALSE)
	set(GLFW_BUILD_DOCS FALSE)

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_Declare(
	assimp
	GIT_REPOSITORY https://github.com/assimp/assimp.git
)
FetchContent_GetProperties(assimp)
if(NOT assimp_POPULATED)
	FetchContent_Populate(assimp)

	set(BUILD_SHARED_LIBS FALSE)
	set(ASSIMP_NO_EXPORT TRUE)
	set(ASSIMP_BUILD_ASSIMP_TOOLS FALSE)
	set(ASSIMP_BUILD_TESTS FALSE)
	set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT FALSE)
	set(ASSIMP_BUILD_GLTF_IMPORTER TRUE)
	set(ASSIMP_BUILD_FBX_IMPORTER TRUE)
	set(ASSIMP_BUILD_OBJ_IMPORTER TRUE)

	add_subdirectory(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
endif()

include_directories(${ASSIMP_INCLUDE_DIR})

# GET SOURCE #
file(GLOB src CONFIGURE_DEPENDS "src/*.cpp" "lib/*.cpp" "lib/ImGUI/*.cpp")

# BUILD ENGINE AS STATIC LIBRARY #
#STATIC
add_library(blackbox STATIC engine.cpp ${src})
target_include_directories(blackbox PUBLIC ./include ./src ${assimp_SOURCE_DIR} ./build/_deps/assimp-src/include ./build/_deps/assimp-build/include) #
target_link_libraries(blackbox PUBLIC glfw assimp ${ASSIMP_LIBRARIES})
message("ASDF ${assimp_SOURCE_DIR}")
# BUILD DEMO EXECUTABLE #
link_directories("./build")
add_executable(app main.cpp)
target_link_libraries(app PUBLIC blackbox)

#if (WIN32)
#target_link_options(app PRIVATE -mwindows)
#endif (WIN32)

if (UNIX)
message("${BoldCyan}Copying resources folder${ColorReset}")
execute_process (
    COMMAND bash -c "cp -fR ../res ."
    OUTPUT_VARIABLE outVar
)
endif (UNIX)