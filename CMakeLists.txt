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

# GET SOURCE #
file(GLOB src CONFIGURE_DEPENDS "src/*.cpp" "lib/*.cpp" "lib/ImGUI/*.cpp")

# BUILD ENGINE AS STATIC LIBRARY #
add_library(blackbox STATIC blackbox.cpp ${src})
target_include_directories(blackbox PUBLIC ./include ./src) #
target_link_libraries(blackbox PUBLIC glfw)

# BUILD DEMO EXECUTABLE #
link_directories("./build")
add_executable(app main.cpp)
target_link_libraries(app PUBLIC blackbox)

target_compile_definitions(app PUBLIC LITE)

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