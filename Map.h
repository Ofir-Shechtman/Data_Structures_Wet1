#ifndef MAP_H
#define MAP_H

#include "AVLTree.h"

template <class K, class T>
class Map {
    Compare<K>* compare;
    AVLTree<K,T> tree;
public:
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    Map();
    ~Map();
    Map(const Map&);
    Map& operator=(const Map&);
    bool empty() const;
    Iterator find(const K& key);
    void erase(const K& key);
    unsigned int size();
    void clear();
    Iterator insert(const K& key, const T& data);
    const T& at(const K& key) const; //if key not found throw KeyNotExists
    //T& at(const K& key);
    //void erase(const Iterator&);
    class KeyNotExists : public AVLTree<K,T>::KeyNotExists{};
    class KeyAlreadyExists : public AVLTree<K,T>::KeyAlreadyExists{};
};

template<class K, class T>
class Map<K, T>::Iterator{
    typename AVLTree<K, T>::Iterator iterator;
public:
    explicit Iterator(typename AVLTree<K, T>::Iterator iterator = AVLTree<K, T>::Iterator());
    const T& operator*() const;
    T& operator*();
    Iterator operator++();
    bool operator!=(const Iterator& it) const;
    class InvalidIterator : public exception{};
};

template<class K, class T>
Map<K, T>::Iterator::Iterator(
        typename AVLTree<K, T>::Iterator iterator):iterator(iterator){}

template<class K, class T>
const T& Map<K, T>::Iterator::operator*() const {
    return iterator.data();
}

template<class K, class T>
T &Map<K, T>::Iterator::operator*() {
    return iterator.data();
}

template<class K, class T>
typename Map<K, T>::Iterator Map<K, T>::Iterator::operator++() {
    return Iterator(++iterator);
}

template<class K, class T>
bool
Map<K, T>::Iterator::operator!=(const Map<K, T>::Iterator &it) const {
    return iterator!=it.iterator;
}


template<class K, class T>
bool Map<K, T>::empty() const{
    return false;
}

template<class K, class T>
void Map<K, T>::clear() {
    tree.clear();

}

template<class K, class T>
typename Map<K, T>::Iterator Map<K, T>::find(const K &key) {
    return Map::Iterator(tree.find(Element(key)));
}

template<class K, class T>
typename Map<K, T>::Iterator Map<K, T>::insert(const K &key, const T &data) {
    try{
        return Map::Iterator(tree.insert(key, data));
    }
    catch (typename AVLTree<K,int>::KeyAlreadyExists&){
        throw KeyAlreadyExists();
    }
}

template<class K, class T>
const T& Map<K, T>::at(const K &key) const{
    try{
        return *Iterator(tree.find(key));
    }
    catch (typename AVLTree<K,int>::KeyNotExists&){
        throw KeyNotExists();
    }
}
/*
template<class K, class T>
T& Map<K, T>::at(const K &key) {
    try{
        return *Iterator(tree.find(key));
    }
    catch (typename AVLTree<K,int>::KeyNotExists&){
        throw KeyNotExists();
    }
}*/


template<class K, class T>
void Map<K, T>::erase(const K &key) {
    tree.erase(key);

}

template<class K, class T>
typename Map<K, T>::Iterator Map<K, T>::begin() const {
    return Map::Iterator(tree.begin());
}

template<class K, class T>
typename Map<K, T>::Iterator Map<K, T>::end() const {
    return Map::Iterator(tree.end());
}

template<class K, class T>
unsigned int Map<K, T>::size() {
    return tree.size();
}

template<class K, class T>
Map<K, T>::Map() : compare(new Compare<K>()), tree(compare){

}


template<class K, class T>
Map<K, T>::Map(const Map & map): compare(new Compare<K>()), tree(map.tree) {}

template<class K, class T>
Map<K, T>::~Map() {
    delete compare;
}

template<class K, class T>
Map<K, T> &Map<K, T>::operator=(const Map &map) {
    tree=map.tree;
}



#endif //MAP_H
