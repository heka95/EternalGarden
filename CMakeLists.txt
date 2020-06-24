cmake_minimum_required (VERSION 3.13.0)

project (Eternal_Garden VERSION 0.1)

# Project Configuration
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Application paths
file(GLOB SOURCE_FILES src/*.cpp)
add_executable (${PROJECT_NAME} ${SOURCE_FILES})

file(GLOB_RECURSE HEADER_FILES include/*.hpp external/*.hpp external/*.h)

foreach(HEADER_FILE ${HEADER_FILES})
	get_filename_component(HEADER_DIRECTORY ${HEADER_FILE} DIRECTORY)
	include_directories(${HEADER_DIRECTORY})
endforeach(HEADER_FILE)

#target_include_directories(${PROJECT_NAME} PRIVATE include)

# Compiling arguments
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CXX_EXTENSIONS OFF)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -DDEBUG_ENABLED -DDEBUG_COLOR)
set(CMAKE_CXX_FLAGS "-m64 -fPIC -Wall -march=corei7")

# SDL2
set(SDL2_PATH ${PROJECT_SOURCE_DIR}/external/SDL2)
set(SDL2_IMAGE_PATH ${PROJECT_SOURCE_DIR}/external/SDL2)
set(SDL2_TTF_PATH ${PROJECT_SOURCE_DIR}/external/SDL2)
set(SDL2CONSOLE ON) # Use console to show LUA/APP outputs
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 is needed to build the project. Please install it correctly.")
endif()

include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries (${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries (${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})

# LUA
if (WIN32)
    set(LUA_LIBRARIES ${PROJECT_SOURCE_DIR}/external/lua/lib)
    set(LUA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/lua/include)
endif (WIN32)
find_package(Lua REQUIRED)
if(NOT LUA_FOUND)
    message(FATAL_ERROR "Lua is needed to build the project. Please install it correctly.")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${LUA_INCLUDE_DIR})
target_link_libraries (${PROJECT_NAME} ${LUA_LIBRARIES}/liblua53.a)


# SOL 2 (LUA C++ Binder)
include_directories(${PROJECT_SOURCE_DIR}/external/sol2)

# Json Library
include_directories(${PROJECT_SOURCE_DIR}/external/json)