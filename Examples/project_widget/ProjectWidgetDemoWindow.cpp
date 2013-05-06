#include "ProjectWidgetDemoWindow.h"

ProjectWidgetDemoWindow::ProjectWidgetDemoWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_project = new Required::Project();
    m_project->setName("My Awesome Project");
    m_projectWidget = new Required::ProjectWidget(this);
    m_projectWidget->setProject(m_project);
    setCentralWidget(m_projectWidget);
}
