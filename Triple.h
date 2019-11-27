#ifndef TRIPLE_H
#define TRIPLE_H

template<class  T1, class T2, class T3>
struct Triple {
    T1 first;
    T2 second;
    T3 third;
    explicit Triple(T1 first=T1(), T2 second=T2(), T3 third=T3());
};

template<class T1, class T2, class T3>
Triple<T1, T2, T3>::Triple(T1 first, T2 second, T3 third) :
        first(first), second(second), third(third) {}

#endif //TRIPLE_H
