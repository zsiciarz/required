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
#include <QString>

namespace Required
{
    /**
     * Managing categories of files in the project.
     */
    class FileCategory
    {
    public:
        explicit FileCategory(QString shortName, QString displayedName = "");
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

        static void registerCategory(QString shortName, QString displayedName = "");
        static FileCategory getCategory(QString shortName);

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
