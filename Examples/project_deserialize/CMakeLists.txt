add_executable(project_deserialize EXCLUDE_FROM_ALL project_deserialize.cpp)
add_dependencies(examples project_deserialize)
target_link_libraries(project_deserialize Required_Project ${QT_LIBRARIES})
