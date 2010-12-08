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
        connect(project, SIGNAL(fileAdded(QString,QString)), SLOT(addFile(QString,QString)));
        connect(project, SIGNAL(fileRemoved(QString,QString)), SLOT(removeFile(QString,QString)));

        // the naive implementation of tree widget goes below
        m_treeWidget->setColumnCount(1);
        m_treeWidget->setHeaderHidden(true);
        QStringList categoryShortNames = m_project->categoryShortNames();
        foreach (QString categoryShortName, categoryShortNames)
        {
            QTreeWidgetItem* categoryItem = getCategoryItem(categoryShortName);
            foreach (QString filename, m_project->filesInCategory(categoryShortName))
            {
                QTreeWidgetItem* fileItem = getFileItem(filename);
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
        m_project->disconnect(this);
        // TODO: not sure about deleting the Project object?
        //m_project->deleteLater();
        m_project = 0;

        m_treeWidget->clear();
        m_categoryItems.clear();
        m_fileItems.clear();
    }

    /**
     * Adds new file to the display.
     *
     * @param filename full path to the file
     * @param categoryShortName category identifier
     */
    void ProjectWidget::addFile(QString filename, QString categoryShortName)
    {
        QTreeWidgetItem* fileItem = getFileItem(filename);
        QTreeWidgetItem* categoryItem = getCategoryItem(categoryShortName);
        categoryItem->addChild(fileItem);
    }

    /**
     * Removes a file from the display.
     *
     * @param filename full path to the file
     * @param categoryShortName category identifier
     */
    void ProjectWidget::removeFile(QString filename, QString categoryShortName)
    {
        QTreeWidgetItem* fileItem = getFileItem(filename);
        QTreeWidgetItem* categoryItem = getCategoryItem(categoryShortName);
        categoryItem->removeChild(fileItem);
    }

    /**
     * Returns a top-level item corresponding to file category.
     *
     * If the category is already displayed as a top-level item, we return that
     * item. Otherwise, a new top-level item is created and inserted into the
     * widget.
     *
     * @param categoryShortName category identifier
     * @return top-level category item
     */
    QTreeWidgetItem* ProjectWidget::getCategoryItem(QString categoryShortName)
    {
        QTreeWidgetItem* item = m_categoryItems[categoryShortName];
        if (item)
        {
            return item;
        }

        // item == 0, that means we have to create one
        FileCategory category = FileCategory::getCategory(categoryShortName);
        item = new QTreeWidgetItem(QStringList() << category.displayedName());
        // store a pointer to the item in the category => item mapping
        m_categoryItems[categoryShortName] = item;
        m_treeWidget->addTopLevelItem(item);

        return item;
    }

    /**
     * Returns an item for a filename.
     *
     * @param filename full path to the file
     * @return item for the file
     */
    QTreeWidgetItem* ProjectWidget::getFileItem(QString filename)
    {
        QTreeWidgetItem* item = m_fileItems[filename];
        if (item)
        {
            return item;
        }

        // no item found in the mapping so we create one
        item = new QTreeWidgetItem(QStringList() << filename);
        m_fileItems[filename] = item;

        return item;
    }
}
