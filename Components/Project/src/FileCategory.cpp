/**
 * @file FileCategory.cpp
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

#include "FileCategory.h"

namespace Required
{
    QMap<QString, FileCategory> FileCategory::s_nameMap;

    /**
     * Creates the category object.
     *
     * @param shortName category name - used internally for lookup etc.
     * @param displayedName category name to be displayed to the user
     */
    FileCategory::FileCategory(QString shortName, QString displayedName):
        m_shortName(shortName),
        m_displayedName(displayedName.isEmpty() ? m_shortName : displayedName)
    {
    }

    /**
     * Creates the default category (Other).
     *
     * The default constructor should be used only for lookup in the category
     * mapping.
     */
    FileCategory::FileCategory():
        m_shortName("OTHER"), m_displayedName("Other")
    {
    }

    /**
     * Registers new category in the mapping.
     *
     * This method may be called by Project subclasses which need to define
     * their own categories.
     *
     * For example, an ImageProject class may register categories like
     * "JPG Files", "PNG Files", "Brushes" etc.
     *
     * @param shortName category name - used internally for lookup etc.
     * @param displayedName category name to be displayed to the user
     */
    void FileCategory::registerCategory(QString shortName, QString displayedName)
    {
        FileCategory category(shortName, displayedName);
        // copy-by-value here, since QString members can be safely copied
        s_nameMap[shortName] = category;
    }

    /**
     * Looks up a category by it's short name and returns it as an object.
     *
     * If the lookup fails, the default category object is returned (a category
     * labeled "Other").
     *
     * @param shortName the proper short category name
     * @return category object (may be the default one)
     */
    FileCategory FileCategory::getCategory(QString shortName)
    {
        // as Qt docs states about containers: QMap::value() returns a
        // default-constructed value if the specified key isn't in the map.
        return s_nameMap.value(shortName);
    }
}
