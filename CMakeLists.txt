cmake_minimum_required(VERSION 2.8.8)
project(Required)

set(Required_VERSION_MAJOR 1)
set(Required_VERSION_MINOR 0)
set(Required_VERSION_PATCH 0)
set(Required_VERSION_SUFFIX "-dev")


################################################################################
#
# Dependencies
#
################################################################################

# Qt
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})


################################################################################
#
# Build targets
#
################################################################################

add_subdirectory(Components)

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
