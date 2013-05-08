/**
 * @file global.h
 *
 * Global library typedefs and constants.
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

#ifndef GLOBAL_H
#define GLOBAL_H

#if defined (_WIN32) && defined(BUILD_SHARED_LIBS)
#  if defined(Required_EXPORTS)
#    define REQUIRED_EXPORT  __declspec(dllexport)
#  else
#    define REQUIRED_EXPORT  __declspec(dllimport)
#  endif
#else
#    define REQUIRED_EXPORT
#endif

#endif // GLOBAL_H
