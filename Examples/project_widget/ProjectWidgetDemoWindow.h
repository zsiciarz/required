#ifndef PROJECTWIDGETDEMOWINDOW_H
#define PROJECTWIDGETDEMOWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include "Required/Project/Project.h"
#include "Required/Project/ProjectWidget.h"

class ProjectWidgetDemoWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ProjectWidgetDemoWindow(QWidget *parent = 0);

private:
    Required::Project* m_project;
    Required::ProjectWidget* m_projectWidget;

    void closeEvent(QCloseEvent* event);
};

#endif // PROJECTWIDGETDEMOWINDOW_H
