################################################################################
#
# Example programs using Required
#
################################################################################

# all examples use installed headers, not the ones in the source distribution
include_directories("${CMAKE_INSTALL_PREFIX}/include")

add_subdirectory(project_widget)
add_subdirectory(project_serialize)
add_subdirectory(project_deserialize)
