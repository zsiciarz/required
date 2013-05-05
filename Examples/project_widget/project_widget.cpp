#include <QApplication>
#include <QMainWindow>
#include "ProjectWidgetDemoWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProjectWidgetDemoWindow w;
    w.show();
    return a.exec();
}
