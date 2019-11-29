#ifndef ARRAY_H
#define ARRAY_H


#include "SparseMatrix.h"

template<class T>
class Array {
private:
    unsigned int size;
    T* data;
public:
    explicit Array(unsigned int size);
    ~Array();
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;
    const T& operator*() const;
};

template<class T>
Array<T>::Array(unsigned int size) : size(size), data(new T[size]){}

template<class T>
Array<T>::~Array() {
    delete[] data;
}

template<class T>
T &Array<T>::operator[](unsigned int index) {
    return data[index];
}

template<class T>
const T &Array<T>::operator[](unsigned int index) const {
    return data[index];
}


#endif //ARRAY_H
