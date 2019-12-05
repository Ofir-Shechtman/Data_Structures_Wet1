#ifndef PAIR_H
#define PAIR_H

template <class T, class S>
struct Pair {
    Pair() = default;
    ~Pair() = default;

    T first;
    S second;
    Pair(T first, S second):first(first), second(second){};
};


#endif //