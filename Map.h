#ifndef MAP_H
#define MAP_H

#include "AVLTree.h"
typedef int T;
typedef int K;

//template <class K>
class default_cmp : public Compare{
    bool operator()(K key1, K key2){return key1<key2;};
};

class Map {
    AVLTree tree;
public:
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    Map(const Compare& cmp=default_cmp());
    ~Map();
    Map(const Map&);
    Map& operator=(const Map&);
    bool empty();
    unsigned int size();
    void clear();
    Iterator find(const K& key);
    Iterator insert(K key, T data=T());
    T& operator[](const K& key); //if key not found insert it
    void erase(const K& key);
    void erase(Iterator);
    class KeyNotExists : public exception{};
    class KeyAlreadyExists : public exception{};
};

class Map::Iterator{
    AVLTree::Iterator iterator;
public:
    Iterator()= default;
    const T& operator*() const;
    Iterator& operator++();
    bool operator!=(const Iterator& it) const;
    class InvalidIterator : public exception{};
};


void AVLTree::append(K key, T data) {
    if(root == nullptr){
        root = new BSTNode(key, data);
        return;
    }
    append_req(key,data,root);
}

T AVLTree::get(K key) {
    BSTNode* n = search(key);
    if(n == nullptr){
        throw KeyNotExists();
    }
    return n->data;
}
#endif //MAP_H
