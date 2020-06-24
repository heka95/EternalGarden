cmake_minimum_required (VERSION 3.17.3)

# Project Configuration
set( CMAKE_VERBOSE_MAKEFILE OFF )
project (Eternal_Garden VERSION 0.1)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Application paths
file(GLOB SOURCES "src/*.cpp")
add_executable (${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Compiling arguments
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CXX_EXTENSIONS OFF)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set(CMAKE_CXX_FLAGS "-m64 -fPIC -Wall -march=corei7")

# SDL2
set(SDL2_PATH ${PROJECT_SOURCE_DIR}/external/SDL2)
set(SDL2_IMAGE_PATH ${PROJECT_SOURCE_DIR}/external/SDL2)
set(SDL2_TTF_PATH ${PROJECT_SOURCE_DIR}/external/SDL2)
set(SDL2CONSOLE ON) # Use console to show LUA/APP outputs
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries (${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries (${PROJECT_NAME} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries (${PROJECT_NAME} ${SDL2_TTF_LIBRARIES})

# LUA
set(LUA_LIBRARIES ${PROJECT_SOURCE_DIR}/external/lua/lib)
set(LUA_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/external/lua/include)
find_package(Lua REQUIRED)
if (LUA_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${LUA_INCLUDE_DIR})
    target_link_libraries (${PROJECT_NAME} ${LUA_LIBRARIES}/liblua53.a)
endif()

# SOL 2 (LUA C++ Binder)
include_directories(${PROJECT_SOURCE_DIR}/external/sol2)

# Json Library
include_directories(${PROJECT_SOURCE_DIR}/external/json)