#ifndef CHILLINCLIENT_GLOBAL_H
#define CHILLINCLIENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CHILLINCLIENT_LIBRARY)
#  define CHILLINCLIENTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CHILLINCLIENTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CHILLINCLIENT_GLOBAL_H