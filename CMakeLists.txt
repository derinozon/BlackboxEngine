cmake_minimum_required(VERSION 3.21)
set (CMAKE_CXX_STANDARD 17)

# set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_BUILD_TYPE Release)

project(blackbox)

include(FetchContent)

FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw
	GIT_PROGRESS    TRUE
)
FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES FALSE)
	set(GLFW_BUILD_TESTS FALSE)
	set(GLFW_BUILD_DOCS FALSE)

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

# GET SOURCE #
file(GLOB src CONFIGURE_DEPENDS "src/*.cpp" "lib/*.cpp" "lib/*.c" "lib/ImGUI/*.cpp")

# BUILD ENGINE AS STATIC LIBRARY #
add_library(blackbox STATIC blackbox.cpp ${src})
target_include_directories(blackbox PUBLIC ${glfw_SOURCE_DIR}/include ./include ./src)
target_link_libraries(blackbox PUBLIC glfw)

# BUILD DEMO EXECUTABLE #
link_directories("./build")
add_executable(app demos/main.cpp)
target_link_libraries(app PUBLIC blackbox)

target_compile_definitions(app PUBLIC LITE)

if (MINGW)
	target_link_options(app PRIVATE -static-libgcc -static-libstdc++)
endif (MINGW)

if (WIN32)
	target_link_options(app PRIVATE -mwindows)

	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_link_options(app PRIVATE -mconsole)
	endif (CMAKE_BUILD_TYPE STREQUAL "Debug")
endif (WIN32)

if (UNIX)
message("${BoldCyan}Copying resources folder${ColorReset}")
execute_process (
    COMMAND bash -c "cp -fR ../res ."
    OUTPUT_VARIABLE outVar
)
endif (UNIX)