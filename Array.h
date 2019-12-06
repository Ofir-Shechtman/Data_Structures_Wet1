#ifndef ARRAY_H
#define ARRAY_H


//#include "SparseMatrix.h"

template<class T>
class Array {
private:
    unsigned int array_size;
    T* data;
public:
    unsigned int size() const;
    explicit Array(unsigned int size);
    ~Array();
    Array(const Array<T>&);
    Array<T>& operator=(const Array&);
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;

};

template<class T>
Array<T>::Array(unsigned int size): array_size(size), data(new T[size]){}

template<class T>
Array<T>::Array(const Array<T>& array): array_size(array.array_size), data(new T[array_size]) {
    for(unsigned int i=0; i < array_size; ++i){
        data[i]= array[i];
    }
}

template<class T>
Array<T>::~Array() {
    delete[] data;
}


template<class T>
Array<T> &Array<T>::operator=(const Array& array) {
    if (&array==this)
        return *this;
    delete data;
    array_size=array.size();
    data= new T[array_size];
    for(int i=0; i<array_size; ++i){
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
unsigned int Array<T>::size() const {
    return array_size;
}

#endif //ARRAY_H
