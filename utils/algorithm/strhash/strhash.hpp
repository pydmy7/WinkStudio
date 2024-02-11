#ifndef STRHASH_HPP
#define STRHASH_HPP

#include <array>
#include <vector>

#include <QString>

using i64 = long long;

class StrHash {
private:
    static constexpr std::array<int, 2> p = {223333333, 773333333};
    static constexpr std::array<int, 2> mod = {1000000033, 1000002233};

    int n;
    // const int n;会报错？不清楚，和隐式共享有关系吗？
    std::vector<std::vector<i64>> h, rh, pw;

public:
    explicit StrHash(const QString& str = "");

    i64 getHashValueObverse(int l, int r) const;
    i64 getHashValueReverse(int l, int r) const;
};

#endif // STRHASH_HPP
