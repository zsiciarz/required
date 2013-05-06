cmake_minimum_required(VERSION 2.8.8)
project(Required)

set(Required_VERSION_MAJOR 1)
set(Required_VERSION_MINOR 0)
set(Required_VERSION_PATCH 0)
set(Required_VERSION_SUFFIX "-dev")

################################################################################
#
# Build options
#
################################################################################

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

################################################################################
#
# Dependencies
#
################################################################################

find_package(Qt5Widgets REQUIRED)

################################################################################
#
# Compiler-specific options
#
################################################################################

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    if(APPLE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif()

################################################################################
#
# Build targets
#
################################################################################

add_subdirectory(Required)

add_custom_target(examples)
add_subdirectory(Examples)

################################################################################
#
# Installing
#
################################################################################

# install the binaries and include files
install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_PREFIX})
# the libraries define their installation themselves
