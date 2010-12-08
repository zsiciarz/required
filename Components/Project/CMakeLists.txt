# library headers
set(Required_Project_HEADERS
    src/FileCategory.h
    src/ProjectException.h
    src/Project.h
    src/ProjectSerializer.h
    src/ProjectWidget.h
)

# library sources
set(Required_Project_SOURCES
    src/FileCategory.cpp
    src/Project.cpp
    src/ProjectSerializer.cpp
    src/ProjectWidget.cpp
)

# headers that need Qt meta-object compiler
set(Required_Project_MOC_HEADERS
    src/Project.h
    src/ProjectWidget.h
)

qt4_wrap_cpp(Required_Project_MOC_SOURCES ${Required_Project_MOC_HEADERS})

# main Project library
add_library(Required_Project ${Required_Project_HEADERS}
            ${Required_Project_SOURCES} ${Required_Project_MOC_SOURCES})
target_link_libraries(Required_Project ${QT_LIBRARIES})

# where to install the library
install(TARGETS Required_Project
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib)
install(DIRECTORY src/
        DESTINATION "${Required_COMPONENTS_INCLUDE_DIR}/Project"
        FILES_MATCHING PATTERN "*.h")
