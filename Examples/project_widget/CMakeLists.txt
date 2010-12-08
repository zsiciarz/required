add_executable(project_widget WIN32 EXCLUDE_FROM_ALL project_widget.cpp)
add_dependencies(examples project_widget)
target_link_libraries(project_widget Required_Project ${QT_LIBRARIES})
