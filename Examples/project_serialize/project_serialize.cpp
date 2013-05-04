#include <iostream>
#include <QFile>
#include <QRegExp>
#include "Required/Project/FileCategory.h"
#include "Required/Project/Project.h"
#include "Required/Project/ProjectException.h"
#include "Required/Project/ProjectSerializer.h"


int main(int argc, char *argv[])
{
    Required::Project project;
    project.setName("My Awesome Project");
    Required::FileCategory::registerCategory("exe", "Executables", QRegExp("\\.exe$"));
    Required::FileCategory::registerCategory("", "Other");

    // adding self to the project - nonsense, but this is only a demonstration
    project.addFile(argv[0], "exe");

    try
    {
        if (argc < 2)
        {
            std::cerr << "No filename given, quitting." << std::endl;
            return 1;
        }
        QFile file(argv[1]);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            Required::ProjectSerializer serializer(&file);
            serializer.serialize(project);
            file.close();
        }
    }
    catch (Required::ProjectException& e)
    {
        std::cerr << e.what();
    }

    return 0;
}
