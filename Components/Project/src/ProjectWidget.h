/**
 * @file ProjectWidget.h
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

#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QMap>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include "Project.h"

namespace Required
{
    /**
     * A widget which knows how to display contents of a project.
     */
    class ProjectWidget : public QWidget
    {
        Q_OBJECT

    public:
        explicit ProjectWidget(QWidget* parent = 0);
        ~ProjectWidget();

        void setProject(Project* project);

        /**
         * Checks whether the widget is currently presenting a project.
         *
         * @return true if there is a project loaded into the widget
         */
        bool hasProject() const
        {
            return m_project != 0;
        }

        void closeProject();

    public slots:
        void addFile(QString filename, QString categoryShortName = "");
        void removeFile(QString filename, QString categoryShortName = "");

    private:
        /**
         * The actual project instance.
         */
        Project* m_project;

        /**
         * The tree widget.
         */
        QTreeWidget* m_treeWidget;

        /**
         * A register of top-level items corresponding to category identifiers.
         */
        QMap<QString, QTreeWidgetItem*> m_categoryItems;

        /**
         * A register of leaf items corresponding to filenames.
         */
        QMap<QString, QTreeWidgetItem*> m_fileItems;

        QTreeWidgetItem* getCategoryItem(QString categoryShortName);
        QTreeWidgetItem* getFileItem(QString filename);
    };
}

#endif // PROJECTWIDGET_H
