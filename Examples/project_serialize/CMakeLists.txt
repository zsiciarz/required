add_executable(project_serialize EXCLUDE_FROM_ALL project_serialize.cpp)
add_dependencies(examples project_serialize)
target_link_libraries(project_serialize Required_Project ${QT_LIBRARIES})
