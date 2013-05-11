#include "ProjectWidgetDemoWindow.h"
#include "Required/Project/FileCategory.h"
#include <QRegExp>

ProjectWidgetDemoWindow::ProjectWidgetDemoWindow(QWidget *parent) :
    QMainWindow(parent)
{
    Required::FileCategory::registerCategory("txt", "Text files", QRegExp("*.txt", Qt::CaseSensitive, QRegExp::Wildcard));
    Required::FileCategory::registerCategory("json", "JSON data", QRegExp("*.json", Qt::CaseSensitive, QRegExp::Wildcard));

    m_project = new Required::Project();
    m_project->setName("My Awesome Project");
    m_projectWidget = new Required::ProjectWidget(this);
    m_projectWidget->setProject(m_project);
    setCentralWidget(m_projectWidget);
}
