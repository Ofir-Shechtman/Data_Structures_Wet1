#ifndef MAP_H
#define MAP_H

#include "AVLTree.h"

template <class K, class T>
class Map {
    AVLTree<K,T> tree;
public:
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    Map()= default;
    bool empty() const;
    Iterator find(const K& key);
    void erase(const K& key);
    unsigned int size();
    void clear();
    Iterator insert(const K& key, const T& data);
    const T& at(const K& key) const; //if key not found throw KeyNotExists
    //void erase(const Iterator&);
    class KeyNotExists : public AVLTree<K,int>::KeyNotExists{};
    class KeyAlreadyExists : public AVLTree<K,int>::KeyAlreadyExists{};
};

template<class K, class T>
class Map<K, T>::Iterator{
    typename AVLTree<K, T>::Iterator iterator;
public:
    explicit Iterator(typename AVLTree<K, T>::Iterator iterator = AVLTree<K, T>::Iterator());
    const T& operator*() const;
    Iterator& operator++();
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
typename Map<K, T>::Iterator &Map<K, T>::Iterator::operator++() {
    return ++iterator;
}

template<class K, class T>
bool
Map<K, T>::Iterator::operator!=(const Map<K, T>::Iterator &it) const {
    return Iterator(iterator)!=it;
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
    return Map::Iterator(tree.insert(key, data));
}

template<class K, class T>
const T& Map<K, T>::at(const K &key) const{
    auto it= Iterator(tree.find(key));
    if(it!=end())
        return *it;
    throw KeyNotExists();

}


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


#endif //MAP_H
