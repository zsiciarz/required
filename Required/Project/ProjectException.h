/**
 * @file ProjectException.h
 *
 * The base Project-related exception class.
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

#ifndef PROJECTEXCEPTION_H
#define PROJECTEXCEPTION_H

#include "../global.h"
#include <stdexcept>
#include <QString>

namespace Required
{
    /**
     * The base Project-related exception class.
     */
    class REQUIRED_EXPORT ProjectException : public std::runtime_error
    {
    public:
        ProjectException(QString message):
            std::runtime_error(message.toStdString())
        {
        }
    };
}

#endif // PROJECTEXCEPTION_H
