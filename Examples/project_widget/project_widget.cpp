#include <QApplication>
#include "Required/Components/Project/Project.h"
#include "Required/Components/Project/ProjectWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Required::Project project;
    project.setName("My Awesome Project");

    Required::ProjectWidget w;
    w.setProject(&project);
    w.show();
    return a.exec();
}
