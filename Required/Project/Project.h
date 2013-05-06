/**
 * @file Project.h
 *
 * A class implementing basic project management functionality.
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

#ifndef PROJECT_H
#define PROJECT_H

#include "FileCategory.h"
#include <QFileInfoList>
#include <QList>
#include <QMap>
#include <QMultiMap>
#include <QObject>
#include <QString>
#include <QStringList>

namespace Required
{
    /**
     * A class implementing basic project management functionality.
     */
    class Project : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QString name READ getName WRITE setName)

    public:
        explicit Project(QObject* parent = 0);

        /**
         * Returns project name.
         *
         * @return project name
         */
        QString getName() const
        {
            return m_name;
        }

        /**
         * Sets project name.
         *
         * @param name project name
         */
        void setName(QString name)
        {
            m_name = name;
        }

        bool hasFile(QString filename) const;
        void addFile(QString filename, QString categoryShortName = "");
        void addFiles(QStringList filenames, QString categoryShortName = "");
        void removeFile(QString filename, bool deleteFromDisk = false);

        QStringList files() const;
        QFileInfoList fileInfos() const;
        QStringList filesInCategory(QString categoryShortName) const;
        FileCategoryList categories() const;
        QStringList categoryShortNames() const;


    signals:
        void fileAdded(QString filename, QString categoryShortName);
        void fileRemoved(QString filename, QString categoryShortName);

    public slots:

    private:
        /**
         * Project name.
         */
        QString m_name;

        /**
         * A mapping of category short names and files in the project.
         */
        QMultiMap<QString, QString> m_categorizedFiles;

        /**
         * A reverse mapping (file => category) - used for fast indexing.
         */
        QMap<QString, QString> m_fileIndex;
    };
}

#endif // PROJECT_H
