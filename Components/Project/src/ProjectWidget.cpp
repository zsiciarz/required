/**
 * @file ProjectWidget.cpp
 *
 * A widget which knows how to display contents of a project.
 *
 * This file is part of the Required library.
 * Required is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Required
 * @version 1.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2010
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 1.0.0
 */

#include "ProjectWidget.h"
#include "FileCategory.h"
#include <QTreeWidgetItem>
#include <QVBoxLayout>

namespace Required
{
    /**
     * Creates the widget.
     *
     * @param parent parent object
     */
    ProjectWidget::ProjectWidget(QWidget* parent):
        QWidget(parent), m_project(0), m_treeWidget(new QTreeWidget(this))
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(m_treeWidget);
        setLayout(layout);
    }

    /**
     * Destroys the widget.
     *
     * Closes the project if there is one.
     */
    ProjectWidget::~ProjectWidget()
    {
        if (hasProject())
            closeProject();
    }

    /**
     * Loads project contents into the widget.
     *
     * @param project the project to be displayed
     */
    void ProjectWidget::setProject(Project *project)
    {
        if (hasProject())
            closeProject();

        m_project = project;
        // connect() goes here
        // ...

        // the naive implementation of tree widget goes below
        m_treeWidget->setColumnCount(1);
        m_treeWidget->setHeaderHidden(true);
        FileCategoryList categories = m_project->categories();
        foreach (FileCategory category, categories)
        {
            QTreeWidgetItem* categoryItem = new QTreeWidgetItem(QStringList() << category.displayedName());
            m_treeWidget->addTopLevelItem(categoryItem);
            foreach (QString filename, m_project->filesInCategory(category.shortName()))
            {
                QTreeWidgetItem* fileItem = new QTreeWidgetItem(QStringList() << filename);
                categoryItem->addChild(fileItem);
            }
        }

        setWindowTitle(tr("Project: %1").arg(project->name()));
    }

    /**
     * Closes the currently loaded project.
     */
    void ProjectWidget::closeProject()
    {
        // disconnect() goes here
        // ...
        m_project = 0;

        m_treeWidget->clear();
    }
}
