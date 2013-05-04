#include <QApplication>
#include "Required/Project/Project.h"
#include "Required/Project/ProjectWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Required::Project project;
    project.setName("My Awesome Project");

    Required::ProjectWidget w;
    w.setProject(&project);

    project.addFile(argv[0]);
    project.removeFile(argv[0]);

    w.show();
    return a.exec();
}
