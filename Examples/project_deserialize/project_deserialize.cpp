#include <iostream>
#include <QFile>
#include <QString>
#include "Required/Components/Project/FileCategory.h"
#include "Required/Components/Project/Project.h"
#include "Required/Components/Project/ProjectException.h"
#include "Required/Components/Project/ProjectSerializer.h"


int main(int argc, char *argv[])
{
    Required::Project* project = 0;
    try
    {
        if (argc < 2)
        {
            std::cerr << "No filename given, quitting." << std::endl;
            return 1;
        }
        QFile file(argv[1]);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            Required::ProjectSerializer serializer(&file);
            project = serializer.deserialize();
            file.close();
        }
    }
    catch (Required::ProjectException& e)
    {
        std::cerr << e.what();
        return 1;
    }

    std::cout << "Project name: " << qPrintable(project->name()) << std::endl
              << "--------------------------------------------------------\n";


    foreach(Required::FileCategory category, project->categories())
    {
        std::cout << qPrintable(category.displayedName()) << "\t\t("
                  << qPrintable(category.shortName()) << ")\n";
        foreach (QString filename, project->filesInCategory(category.shortName()))
        {
            std::cout << "\t" << qPrintable(filename) << "\n";
        }
    }

    return 0;
}