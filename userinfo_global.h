#ifndef USERINFO_GLOBAL_H
#define USERINFO_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QDir>
#include <QString>

#if defined(USERINFO_LIBRARY)
#  define USERINFOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define USERINFOSHARED_EXPORT Q_DECL_IMPORT
#endif

namespace global
{
    extern QString db_path = QDir::currentPath()+"/../user_info.db";
}


#endif // USERINFO_GLOBAL_H
