/**
 * @file ProjectSerializer.cpp
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

#include "ProjectSerializer.h"
#include "FileCategory.h"
#include "ProjectException.h"
#include <QDebug>
#include <QRegExp>
#include <QStringList>
#include <QXmlStreamAttributes>

namespace Required
{
    /**
     * Creates the serializer.
     *
     * @param device the device which will receive project data
     */
    ProjectSerializer::ProjectSerializer(QIODevice *device):
        m_device(device)
    {
    }

    /**
     * Destroys the serializer.
     */
    ProjectSerializer::~ProjectSerializer()
    {
    }

    /**
     * Handles the serialization.
     *
     * @param project the project to serialize
     */
    void ProjectSerializer::serialize(const Project &project)
    {
        QXmlStreamWriter writer(m_device);
        writer.setAutoFormatting(true);
        writer.writeStartDocument();
        writer.writeStartElement("project");
        writer.writeAttribute("name", project.getName());

        serializeMetadata(project, writer);
        serializeFiles(project, writer);

        writer.writeEndElement();
        writer.writeEndDocument();
    }

    /**
     * Deserializes project from XML.
     *
     * This method only checks for some general assumptions about the XML.
     * The real work is done by readXXX methods.
     *
     * @return a properly set up project instance
     */
    Project* ProjectSerializer::deserialize()
    {
        Project* project = 0;

        QXmlStreamReader reader(m_device);
        reader.readNext();
        while(!reader.atEnd())
        {
            if (reader.isStartElement())
            {
                if (reader.name() == "project")
                {
                    project = new Project();
                    readProjectElement(*project, reader);
                }
                else
                {
                    reader.raiseError(QObject::tr("Not a project file!"));
                }
            }
            else
            {
                reader.readNext();
            }
        }
        if (reader.hasError())
        {
            QString msg = QObject::tr("Parse error at line %1, column %2: %3")
                          .arg(reader.lineNumber())
                          .arg(reader.columnNumber())
                          .arg(reader.errorString());
            throw ProjectException(msg);
        }

        return project;
    }

    /**
     * Serializes only the project metadata.
     *
     * @param project the project to serialize
     * @param writer XML stream writer
     */
    void ProjectSerializer::serializeMetadata(const Project &project,
                                              QXmlStreamWriter &writer)
    {
        writer.writeStartElement("metadata");

        writer.writeStartElement("categories");
        FileCategoryList categories = project.categories();
        foreach (FileCategory category, categories)
        {
            writer.writeStartElement("category");
            writer.writeAttribute("short-name", category.getShortName());
            QString regexp = category.getFilenameRegexp().pattern();
            writer.writeAttribute("filename-regexp", regexp);
            writer.writeCharacters(category.getDisplayedName());
            writer.writeEndElement();
        }
        writer.writeEndElement();

        writer.writeEndElement();
    }

    /**
     * Serializes only project files to the writer.
     *
     * @param project the project to serialize
     * @param writer XML stream writer
     */
    void ProjectSerializer::serializeFiles(const Project &project,
                                           QXmlStreamWriter &writer)
    {
        writer.writeStartElement("files");

        QStringList categoryShortNames = project.categoryShortNames();
        foreach (QString categoryShortName, categoryShortNames)
        {
            QStringList files = project.filesInCategory(categoryShortName);
            foreach (QString filename, files)
            {
                writer.writeStartElement("file");
                writer.writeAttribute("category", categoryShortName);
                writer.writeAttribute("path", filename);
                writer.writeEndElement();
            }
        }

        writer.writeEndElement();
    }

    /**
     * Reads the contents of <project> tag.
     *
     * @param project the project to deserialize
     * @param reader XML stream reader
     */
    void ProjectSerializer::readProjectElement(Project &project,
                                               QXmlStreamReader &reader)
    {
        if (!hasRequiredAttribute(reader, "name"))
            return;

        project.setName(reader.attributes().value("name").toString());

        reader.readNext();
        while (!reader.atEnd())
        {
            if (reader.isEndElement())
            {
                reader.readNext();
                break;
            }
            if (reader.isStartElement())
            {
                if (reader.name() == "metadata")
                {
                    readMetadataElement(project, reader);
                }
                else if (reader.name() == "files")
                {
                    readFilesElement(project, reader);
                }
                else
                {
                    skipUnknownElement(reader);
                }
            }
            else
            {
                reader.readNext();
            }
        }
    }

    /**
     * Reads the contents of <metadata> tag.
     *
     * @param project the project to deserialize
     * @param reader XML stream reader
     */
    void ProjectSerializer::readMetadataElement(Project &project,
                                                QXmlStreamReader &reader)
    {
        reader.readNext();
        while (!reader.atEnd())
        {
            if (reader.isEndElement())
            {
                reader.readNext();
                break;
            }
            if (reader.isStartElement())
            {
                if (reader.name() == "categories")
                {
                    readCategoriesElement(project, reader);
                }
                else
                {
                    skipUnknownElement(reader);
                }
            }
            else
            {
                reader.readNext();
            }
        }
    }

    /**
     * Reads the contents of <categories> tag.
     *
     * @param project the project to deserialize
     * @param reader XML stream reader
     */
    void ProjectSerializer::readCategoriesElement(Project &project,
                                                  QXmlStreamReader &reader)
    {
        reader.readNext();
        while (!reader.atEnd())
        {
            if (reader.isEndElement())
            {
                reader.readNext();
                break;
            }
            if (reader.isStartElement())
            {
                if (reader.name() == "category")
                {
                    readCategoryElement(project, reader);
                }
                else
                {
                    skipUnknownElement(reader);
                }
            }
            else
            {
                reader.readNext();
            }
        }
    }

    /**
     * Reads the contents of <category> tag.
     *
     * @param project the project to deserialize
     * @param reader XML stream reader
     */
    void ProjectSerializer::readCategoryElement(Project &project,
                                                QXmlStreamReader &reader)
    {
        if (!hasRequiredAttribute(reader, "short-name"))
            return;

        QString shortName = reader.attributes().value("short-name").toString();
        QString regexpPattern = reader.attributes().value("filename-regexp").toString();
        QString displayedName = reader.readElementText();
        FileCategory::registerCategory(
            shortName,
            displayedName,
            QRegExp(regexpPattern)
        );

        if (reader.isEndElement())
        {
            reader.readNext();
        }
    }

    /**
     * Reads the contents of <files> tag.
     *
     * @param project the project to deserialize
     * @param reader XML stream reader
     */
    void ProjectSerializer::readFilesElement(Project &project,
                                             QXmlStreamReader &reader)
    {
        reader.readNext();
        while (!reader.atEnd())
        {
            if (reader.isEndElement())
            {
                reader.readNext();
                break;
            }
            if (reader.isStartElement())
            {
                if (reader.name() == "file")
                {
                    readFileElement(project, reader);
                }
                else
                {
                    skipUnknownElement(reader);
                }
            }
            else
            {
                reader.readNext();
            }
        }
    }

    /**
     * Reads the contents of <file> tag.
     *
     * @param project the project to deserialize
     * @param reader XML stream reader
     */
    void ProjectSerializer::readFileElement(Project &project,
                                            QXmlStreamReader &reader)
    {
        if (!hasRequiredAttribute(reader, "path"))
            return;

        QString path = reader.attributes().value("path").toString();
        QString categoryShortName = reader.attributes().value("category").toString();
        project.addFile(path, categoryShortName);

        reader.readNext();

        if (reader.isEndElement())
        {
            reader.readNext();
        }
    }

    /**
     * Skips any XML element unrecognized by readXXX methods.
     */
    void ProjectSerializer::skipUnknownElement(QXmlStreamReader &reader)
    {
        reader.readNext();
        while (!reader.atEnd())
        {
            if (reader.isEndElement())
            {
                reader.readNext();
                break;
            }
            if (reader.isStartElement())
            {
                skipUnknownElement(reader);
            }
            else
            {
                reader.readNext();
            }
        }
    }

    /**
     * Checks whether the current XML tag has a specific attribute.
     *
     * @param reader XML stream reader
     * @param attributeName the name of the attribute
     */
    bool ProjectSerializer::hasRequiredAttribute(QXmlStreamReader &reader,
                                                 QString attributeName)
    {
        QXmlStreamAttributes attributes = reader.attributes();
        if (!attributes.hasAttribute(attributeName))
        {
            reader.raiseError(
                QObject::tr("<%1> element doesn't have a '%2' attribute")
                    .arg(reader.name().toString()).arg(attributeName)
            );
            return false;
        }

        return true;
    }
}
