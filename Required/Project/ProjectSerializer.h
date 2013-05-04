/**
 * @file ProjectSerializer.h
 *
 * A class that allows serializing Project objects to XML.
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

#ifndef PROJECTSERIALIZER_H
#define PROJECTSERIALIZER_H

#include <QIODevice>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Project.h"

namespace Required
{
    /**
     * A class that allows serializing Project objects to XML.
     */
    class ProjectSerializer
    {
    public:
        explicit ProjectSerializer(QIODevice* device);
        virtual ~ProjectSerializer();

        void serialize(const Project& project);
        Project* deserialize();

    private:
        QIODevice* m_device;

        void serializeMetadata(const Project& project, QXmlStreamWriter& writer);
        void serializeFiles(const Project& project, QXmlStreamWriter& writer);

        void readProjectElement(Project& project, QXmlStreamReader& reader);
        void readMetadataElement(Project& project, QXmlStreamReader& reader);
        void readCategoriesElement(Project& project, QXmlStreamReader& reader);
        void readCategoryElement(Project& project, QXmlStreamReader& reader);
        void readFilesElement(Project& project, QXmlStreamReader& reader);
        void readFileElement(Project& project, QXmlStreamReader& reader);
        void skipUnknownElement(QXmlStreamReader &reader);
        bool hasRequiredAttribute(QXmlStreamReader &reader, QString attributeName);
    };
}

#endif // PROJECTSERIALIZER_H
