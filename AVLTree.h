#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include "Stack.h"

using namespace std;

template <class K>
class Compare{
public:
    Compare()= default;
    virtual ~Compare()= default;
    virtual bool operator()(K key1, K key2)=0;
};

template <class K>
class Less : public Compare<K>{
    bool operator()(K key1, K key2){return key1<key2;};
};

template <class K, class T>
class AVLTree{
    struct Node;
    Node * root;
    const Compare<T>* cmp;
public:
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    explicit AVLTree(const Compare<K>& cmp =Less<K>());
    AVLTree(const AVLTree&);
    AVLTree& operator=(const AVLTree&);
    ~AVLTree();
    Iterator find(K key);// TODO: what to return if not found
    Iterator insert(K key, T data);
    void erase(K key);
    bool empty();
    void clear();
    class KeyNotExists : public exception{};
};

template <class K, class T>
struct AVLTree<K,T>::Node{
    K key;
    T data;
    Node* right;
    Node* left;
    unsigned int h;
    explicit Node(T data, Node* right= nullptr, Node* left= nullptr);
};


template <class K, class T>
class AVLTree<K,T>::Iterator{
    Node* node;
    Stack<Node*> stack;
    void Left();
    void Right();
    void Father();
public:
    explicit Iterator(Node* root);
    //const T& operator*() const;
    const K& key() const;
    const T& data() const;
    Iterator& operator++();
    bool operator!=(const Iterator& it) const;
    class InvalidIterator : public exception{};
};

template<class K, class T>
typename AVLTree<K,T>::Iterator AVLTree<K, T>::begin() const {
    return AVLTree::Iterator();
}

template<class K, class T>
typename AVLTree<K,T>::Iterator AVLTree<K, T>::end() const {
    return AVLTree::Iterator(nullptr);
}

template <class K, class T>
void AVLTree<K,T>::Iterator::Left() {
    stack.push(node);
    node=node->left;
}

template <class K, class T>
void AVLTree<K,T>::Iterator::Right() {
    stack.push(node);
    node=node->right;
}

template <class K, class T>
void AVLTree<K,T>::Iterator::Father() {
    node= stack.top();
    stack.pop();
}

template <class K, class T>
AVLTree<K,T>::Iterator::Iterator(Node* root):node(root), stack(Stack<Node*>()){
    if(!node)
        return;
    while(node->left)
        Left();
}

template <class K, class T>
typename AVLTree<K,T>::Iterator &AVLTree<K,T>::Iterator::operator++() {
    if(node== nullptr)
        throw InvalidIterator();
    if(node->right){
        Right();
        while(node->left)
            Left();
        return *this;
    }
    while(true) {
        if (stack.empty()) {
            node = nullptr;
            return *this;
        }
        if(stack.top()->left==node){
            Father();
            return *this;
        }
        Father();
    }
}

template<class K, class T>
const K &AVLTree<K, T>::Iterator::key() const {
    if(node== nullptr)
        throw InvalidIterator();
    return node->key;
}

template<class K, class T>
const T &AVLTree<K, T>::Iterator::data() const {
    if(node== nullptr)
        throw InvalidIterator();
    return node->data;
}


template <class K, class T>
bool AVLTree<K,T>::Iterator::operator!=(const AVLTree<K, T>::Iterator& it) const {
    return node!=it.node;
}


#endif //AVLTREE_H
