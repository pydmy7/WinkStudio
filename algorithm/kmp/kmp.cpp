#include "kmp.hpp"

#include <vector>

#include <QString>

namespace kmp {

bool match(const QString& text, const QString& pattern) {
    const auto &s = text, &p = pattern;
    const int n = s.size(), m = p.size();

    std::vector<int> kmpnext(m);
    kmpnext[0] = -1;
    for (int i = 1, j = -1; i < m; ++i) {
        while (j >= 0 && p[i] != p[j + 1]) {
            j = kmpnext[j];
        }
        j += p[i] == p[j + 1];
        kmpnext[i] = j;
    }

    for (int i = 0, j = -1; i < n; ++i) {
        while (j != -1 && s[i] != p[j + 1]) {
            j = kmpnext[j];
        }
        j += s[i] == p[j + 1];
        if (j == m - 1) {
            return true;
        }
    }
    return false;
}

}
