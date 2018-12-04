#ifndef GAMELIB_GLOBAL_H
#define GAMELIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GAMELIB_LIBRARY)
#  define GAMELIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GAMELIBSHARED_EXPORT Q_DECL_IMPORT
#endif

extern float windowSizeX;
extern float windowSizeY;

#endif // GAMELIB_GLOBAL_H
