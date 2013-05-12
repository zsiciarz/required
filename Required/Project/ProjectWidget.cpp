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
 * @date 2010-2013
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 1.0.0
 */

#include "ProjectWidget.h"
#include "ui_ProjectWidget.h"
#include "FileCategory.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

namespace Required
{
    /**
     * Creates the widget.
     *
     * @param parent parent object
     */
    ProjectWidget::ProjectWidget(QWidget* parent):
        QWidget(parent), m_project(0), ui(new Ui::ProjectWidget)
    {
        ui->setupUi(this);
    }

    /**
     * Destroys the widget.
     *
     * Closes the project if there is one.
     */
    ProjectWidget::~ProjectWidget()
    {
        if (hasProject())
        {
            closeProject();
        }

        delete ui;
    }

    /**
     * Loads project contents into the widget.
     *
     * @param project the project to be displayed
     */
    void ProjectWidget::setProject(Project *project)
    {
        if (hasProject())
        {
            closeProject();
        }

        m_project = project;
        m_project->setParent(this);
        connect(m_project, &Project::fileAdded, this, &ProjectWidget::addFile);
        connect(m_project, &Project::fileRemoved, this, &ProjectWidget::removeFile);

        QStringList categoryShortNames = m_project->getCategoryShortNames();
        foreach (QString shortName, categoryShortNames)
        {
            QTreeWidgetItem* categoryItem = getCategoryItem(shortName);
            foreach (QString filename, m_project->getFilesInCategory(shortName))
            {
                QTreeWidgetItem* fileItem = getFileItem(filename);
                categoryItem->addChild(fileItem);
            }
        }

        setWindowTitle(tr("Project: %1").arg(m_project->getName()));
    }

    /**
     * Closes the currently loaded project.
     */
    void ProjectWidget::closeProject()
    {
        disconnect(m_project, &Project::fileAdded, this, &ProjectWidget::addFile);
        disconnect(m_project, &Project::fileRemoved, this, &ProjectWidget::removeFile);
        m_project->deleteLater();
        m_project = 0;

        ui->treeWidget->clear();
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
        item = new QTreeWidgetItem(QStringList() << category.getDisplayedName());
        // store a pointer to the item in the category => item mapping
        m_categoryItems[categoryShortName] = item;
        ui->treeWidget->addTopLevelItem(item);

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
        if (!item)
        {
            // no item found in the mapping so we create one
            item = new QTreeWidgetItem(QStringList() << filename);
            m_fileItems[filename] = item;
        }

        return item;
    }

    void ProjectWidget::on_btnAddFile_clicked()
    {
        QString filename = QFileDialog::getOpenFileName(
            this,
            tr("Add file to project"),
            QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
        );
        auto category = FileCategory::getCategoryForFilename(filename);
        m_project->addFile(filename, category.getShortName());
    }

    void ProjectWidget::on_btnAddDirectory_clicked()
    {
        QString dirName = QFileDialog::getExistingDirectory(
            this,
            tr("Add all files in a directory to project"),
            QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
        );
        QDir dir(dirName);
        foreach (auto fileinfo, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
        {
            auto filename = fileinfo.absoluteFilePath();
            auto category = FileCategory::getCategoryForFilename(filename);
            m_project->addFile(filename, category.getShortName());
        }
    }
}
