#ifndef ARRAY_H
#define ARRAY_H


//#include "SparseMatrix.h"

template<class T>
class Array {
private:
    T* data;
public:
    const unsigned int size;
    explicit Array(unsigned int size);
    ~Array();
    Array(const Array<T>&);
    Array<T>& operator=(const Array&);
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;
    const T& operator*() const;

};

template<class T>
Array<T>::Array(unsigned int size): size(size), data(new T[size]){}

template<class T>
Array<T>::Array(const Array<T>& array): size(size), data(new T[size]) {
    for(int i=0; i<size; ++i){
        data[i]= array[i];
    }
}

template<class T>
Array<T>::~Array() {
    delete[] data;
}

template<class T>
Array<T> &Array<T>::operator=(const Array& array) {
    if (array==*this)
        return *this;
    delete data;
    size=array.size;
    data(new T[size]);
    for(int i=0; i<size; ++i){
        data[i]= array[i];
    }
    return *this;
}

template<class T>
T &Array<T>::operator[](unsigned int index) {
    return data[index];
}

template<class T>
const T &Array<T>::operator[](unsigned int index) const {
    return data[index];
}

template<class T>
const T &Array<T>::operator*() const {
    T* array= new T[size];
    for(int i=0; i<size; ++i){
        array[i]= data[i];
    }
    return array;
}

#endif //ARRAY_H
