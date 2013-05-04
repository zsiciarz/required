# Project library headers
set(Required_Project_HEADERS
    Project/FileCategory.h
    Project/ProjectException.h
    Project/Project.h
    Project/ProjectSerializer.h
    Project/ProjectWidget.h
)

# Project library sources
set(Required_Project_SOURCES
    Project/FileCategory.cpp
    Project/Project.cpp
    Project/ProjectSerializer.cpp
    Project/ProjectWidget.cpp
)

# main Project library
add_library(Required_Project ${Required_Project_HEADERS} ${Required_Project_SOURCES})
qt5_use_modules(Required_Project Core Widgets)
