/**
 * @file Project.cpp
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

#include "Project.h"
#include "ProjectException.h"
#include <QFile>

namespace Required
{
    Project::Project(QObject* parent):
        QObject(parent)
    {
    }

    /**
     * Checks whether given file is already included in the project.
     *
     * @return true if the file is in the project
     */
    bool Project::hasFile(QString filename) const
    {
        return m_fileIndex.contains(filename);
    }

    /**
     * Adds a file to the project, possibly associating it with a category.
     *
     * If no category short name is provided, a category lookup (based on
     * filename is issued. If a matching category is found, it is used. Else,
     * the default category will be associated when later accessing the file.
     *
     * After a successful addition, fileAdded() signal is emitted.
     *
     * @param filename path to the file
     * @param categoryShortName an optional category identifier
     */
    void Project::addFile(QString filename, QString categoryShortName)
    {
        if (hasFile(filename))
            return;

        if (!QFile::exists(filename))
        {
            throw ProjectException(tr("File %1 does not exist!").arg(filename));
        }

        if (categoryShortName.isEmpty())
        {
            // find whether a category can be associated with a given filename
            FileCategory category = FileCategory::getCategoryForFilename(filename);
            categoryShortName = category.shortName();
        }

        // insert new file - create a new entry in the multimap
        m_categorizedFiles.insert(categoryShortName, filename);

        // update the file index so hasFile can look it up
        m_fileIndex.insert(filename, categoryShortName);

        emit fileAdded(filename, categoryShortName);
    }

    /**
     * Adds multiple files to the project.
     *
     * The only catch is that all files given as the first argument are
     * supposed to be associated with one category.
     *
     * @param filenames list of file paths
     * @param categoryShortName category identifier for all files to be added
     */
    void Project::addFiles(QStringList filenames, QString categoryShortName)
    {
        foreach(QString filename, filenames)
        {
            addFile(filename, categoryShortName);
        }
    }

    /**
     * Removes the file from project.
     *
     * By default the file is only detached from the logical structure of the
     * project. However it is possible to remove it physically by setting the
     * value of the second parameter to true.
     *
     * @param filename path to the file
     * @param deleteFromDisk whether to physically delete the file from disk
     */
    void Project::removeFile(QString filename, bool deleteFromDisk)
    {
        if (!hasFile(filename))
            return;

        // obtain category identifier from the file index
        // the short name is neccessary for the remove() method of QMultiMap
        QString categoryShortName = m_fileIndex[filename];
        m_fileIndex.remove(filename);
        m_categorizedFiles.remove(categoryShortName, filename);

        if (deleteFromDisk)
        {
            QFile::remove(filename);
        }

        emit fileRemoved(filename, categoryShortName);
    }

    /**
     * Returns a list of all files in the project.
     *
     * @return list of file names
     */
    QStringList Project::files() const
    {
        return m_fileIndex.keys();
    }

    /**
     * Returns a list of all files in the project as QFileInfo objects.
     *
     * @return list of QFileInfo objects for all project files
     */
    QFileInfoList Project::fileInfos() const
    {
        QFileInfoList infos;
        foreach(QString filename, files())
        {
            infos.append(QFileInfo(filename));
        }

        return infos;
    }

    /**
     * Returns a list of all files associated with a specific category.
     *
     * @param categoryShortName internal category identifier
     * @return files in that category
     */
    QStringList Project::filesInCategory(QString categoryShortName) const
    {
        return m_categorizedFiles.values(categoryShortName);
    }

    /**
     * Returns a list of all categories in the project.
     *
     * @return category list
     */
    FileCategoryList Project::categories() const
    {
        QStringList shortNames = categoryShortNames();
        QList<FileCategory> categoryList;
        foreach (QString categoryShortName, shortNames)
        {
            categoryList.append(FileCategory::getCategory(categoryShortName));
        }

        return categoryList;
    }

    /**
     * Returns a list of all category identifiers.
     *
     * @return list of category short names
     */
    QStringList Project::categoryShortNames() const
    {
        return m_categorizedFiles.uniqueKeys();
    }
}
