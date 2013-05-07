#include <iostream>
#include <QFile>
#include <QString>
#include "Required/Project/FileCategory.h"
#include "Required/Project/Project.h"
#include "Required/Project/ProjectException.h"
#include "Required/Project/ProjectSerializer.h"


int main(int argc, char *argv[])
{
    Required::Project* project = 0;
    try
    {
        if (argc < 2)
        {
            std::cerr << "Usage: project_deserialize <FILENAME>" << std::endl;
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

    std::cout << "Project name: " << qPrintable(project->getName()) << std::endl
              << "--------------------------------------------------------\n";

    foreach(Required::FileCategory category, project->getCategories())
    {
        std::cout << qPrintable(category.getDisplayedName()) << "\t\t("
                  << qPrintable(category.getShortName()) << "), matches: "
                  << qPrintable(category.getFilenameRegexp().pattern()) << "\n";
        foreach (QString filename, project->getFilesInCategory(category.getShortName()))
        {
            std::cout << "\t" << qPrintable(filename) << "\n";
        }
    }

    return 0;
}
