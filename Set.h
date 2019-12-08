#ifndef SET_H
#define SET_H

#include "AVLTree.h"

template <class K>
class Set {
    AVLTree<K, int> tree;
public:
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    explicit Set(Compare<K>* cmp);
    bool empty() const;
    unsigned int size();
    void clear();
    Iterator find(const K& key);
    Iterator insert(const K& key);
    void erase(const K& key);
    //void erase(const Iterator&);
    class KeyNotExists : public AVLTree<K,int>::KeyNotExists{};
    class KeyAlreadyExists : public AVLTree<K,int>::KeyAlreadyExists{};
    void Test_Balance() { //TODO: remove after test
        tree.Test_Balance();
    }
};

template <class K>
class Set<K>::Iterator{
    typename AVLTree<K, int>::Iterator iterator;
public:
    explicit Iterator(typename AVLTree<K, int>::Iterator iterator= AVLTree<K, int>::Iterator());
    const K& operator*() const;
    Iterator operator++();
    bool operator!=(const Iterator& it) const;
    class InvalidIterator : public exception{};
};

template<class K>
const K& Set<K>::Iterator::operator*() const {
    return iterator.key();
}

template<class K>
typename Set<K>::Iterator Set<K>::Iterator::operator++() {
    return Iterator(++iterator);
}

template<class K>
bool Set<K>::Iterator::operator!=(const Set<K>::Iterator &it) const {
    return iterator!=it.iterator;
}

template<class K>
Set<K>::Iterator::Iterator(typename AVLTree<K, int>::Iterator iterator):
    iterator(iterator){}

template<class K>
Set<K>::Set(Compare<K>* cmp) : tree(AVLTree<K, int>(cmp)){}

template<class K>
bool Set<K>::empty() const{
    return tree.empty();
}

template<class K>
void Set<K>::clear() {
    tree.clear();

}

template<class K>
typename Set<K>::Iterator Set<K>::find(const K &key) {
    return Set::Iterator(tree.find(key));
}

template<class K>
typename Set<K>::Iterator Set<K>::insert(const K &key){
    return Set::Iterator(tree.insert(key));
}

template<class K>
void Set<K>::erase(const K &key) {
    tree.erase(key);

}

template<class K>
typename Set<K>::Iterator Set<K>::begin() const {
    return Set::Iterator(tree.begin());
}

template<class K>
typename Set<K>::Iterator Set<K>::end() const {
    return Set::Iterator(tree.end());
}

template<class K>
unsigned int Set<K>::size() {
    return tree.size();
}


#endif //SET_H
