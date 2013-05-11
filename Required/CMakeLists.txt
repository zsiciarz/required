# Project library headers
set(Required_Project_HEADERS
    global.h
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

# UI files
set(Required_Project_UIS
    Project/ProjectWidget.ui
)

qt5_wrap_ui(Required_Project_UIHEADERS ${Required_Project_UIS})

# main Project library
add_library(Required_Project ${Required_Project_HEADERS} ${Required_Project_UIHEADERS} ${Required_Project_SOURCES})
qt5_use_modules(Required_Project Core Widgets)
