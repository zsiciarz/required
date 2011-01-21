/**
 * @file FileCategory.h
 *
 * Managing categories of files in the project.
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

#ifndef FILECATEGORY_H
#define FILECATEGORY_H

#include <QList>
#include <QMap>
#include <QObject>
#include <QRegExp>
#include <QString>

namespace Required
{
    /**
     * Managing categories of files in the project.
     */
    class FileCategory
    {
    public:
        explicit FileCategory(QString shortName, QString displayedName = "",
                              QRegExp filenameRegexp = QRegExp());
        FileCategory();

        /**
         * Returns the internal short name.
         *
         * @return short name used for lookup etc.
         */
        QString shortName() const
        {
            return m_shortName;
        }

        /**
         * Returns the displayed name.
         *
         * @return displayed name
         */
        QString displayedName() const
        {
            return m_displayedName;
        }

        /**
         * Returns the regular expression for filename matching.
         *
         * @return filename regexp
         */
        QRegExp filenameRegexp() const
        {
            return m_filenameRegexp;
        }

        /**
         * Checks whether the category can be associated with a given filename.
         */
        bool matchesFilename(QString filename) const
        {
            return m_filenameRegexp.exactMatch(filename);
        }

        static void registerCategory(QString shortName, QString displayedName = "",
                                     QRegExp filenameRegexp = QRegExp());
        static FileCategory getCategory(QString shortName);
        static FileCategory getCategoryForFilename(QString filename);

    private:
        /**
         * Short name - used internally.
         */
        QString m_shortName;

        /**
         * Full category name which is displayed to the user.
         */
        QString m_displayedName;

        /**
         * A pattern for filenames which will be associated with the category.
         */
        QRegExp m_filenameRegexp;

        /**
         * A mapping of category short names to category objects.
         */
        static QMap<QString, FileCategory> s_nameMap;
    };

    /**
     * A typedef to ease typing.
     */
    typedef QList<FileCategory> FileCategoryList;
}

#endif // FILECATEGORY_H
