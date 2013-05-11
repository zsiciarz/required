#include "ProjectWidgetDemoWindow.h"
#include "Required/Project/ProjectSerializer.h"
#include "Required/Project/ProjectException.h"
#include "Required/Project/FileCategory.h"
#include <QFile>
#include <QRegExp>

ProjectWidgetDemoWindow::ProjectWidgetDemoWindow(QWidget *parent) :
    QMainWindow(parent)
{
    Required::FileCategory::registerCategory("txt", "Text files", QRegExp("*.txt", Qt::CaseSensitive, QRegExp::Wildcard));
    Required::FileCategory::registerCategory("json", "JSON data", QRegExp("*.json", Qt::CaseSensitive, QRegExp::Wildcard));

    // load project data from file
    QFile file("project.xml");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Required::ProjectSerializer serializer(&file);
        try
        {
            m_project = serializer.deserialize();
        }
        catch (Required::ProjectException& e)
        {
            m_project = new Required::Project(this);
            m_project->setName("My Awesome Project");
        }
        file.close();
    }
    else
    {
        m_project = new Required::Project(this);
        m_project->setName("My Awesome Project");
    }

    m_project->setParent(this);
    m_projectWidget = new Required::ProjectWidget(this);
    m_projectWidget->setProject(m_project);
    setCentralWidget(m_projectWidget);
}
