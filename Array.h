#ifndef ARRAY_H
#define ARRAY_H


#include "SparseMatrix.h"

template<class T>
class Array {
private:
    int size;
    T* data;
public:
    explicit Array(int size);
    ~Array();
    T& operator[](int index);
    const T& operator[](int index) const;
};

template<class T>
Array<T>::Array(int size) : size(size), data(new T[size]){}

template<class T>
Array<T>::~Array() {
    delete[] data;
}

template<class T>
T &Array<T>::operator[](int index) {
    return data[index];
}

template<class T>
const T &Array<T>::operator[](int index) const {
    return data[index];
}


#endif //ARRAY_H
