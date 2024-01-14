#ifndef KMP_HPP
#define KMP_HPP

#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

namespace kmp {

bool match(const QString& text, const QString& pattern);

}

#endif // KMP_HPP
