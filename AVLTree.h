//
// Created by Ben Lugasi on 27/11/2019.
//

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <utility>
#include "Stack.h"

using namespace std;
typedef int T;

class Compare{
public:
    Compare()= default;
    virtual ~Compare()= default;
    virtual void operator()(T d1, T d2)=0;
};

struct BSTNode{
    int key;
    T data;
    BSTNode* right;
    BSTNode* left;
    BSTNode(int key, T data, BSTNode* right= nullptr, BSTNode* left= nullptr);
};

class AVLTree{
    BSTNode * root;
    BSTNode *search_req(int key, BSTNode *n);
    const Compare* cmp;
    void append_req(int key,T data, BSTNode* n);
    void remove_req(int key, BSTNode* n);
    void print_inorder_req(BSTNode *n);
public:
    explicit AVLTree(const Compare& cmp);
    ~AVLTree() = default;
    BSTNode *search(int key);
    void append(int key,T data);
    void remove(int key);
    void print_inorder();
    T get(int key);
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    class KeyNotExists : public exception{};
};

class AVLTree::Iterator{
    BSTNode* node;
    Stack<BSTNode*> stack;
    void Left();
    void Right();
    void Father();
public:
    //friend class AVLTree<T>;
    explicit Iterator(BSTNode* root);
    const T& operator*() const;
    Iterator& operator++();
    bool operator!=(const Iterator& it) const;
    class InvalidIterator : public exception{};
};

void AVLTree::Iterator::Left() {
    stack.push(node);
    node=node->left;
}

void AVLTree::Iterator::Right() {
    stack.push(node);
    node=node->right;
}

void AVLTree::Iterator::Father() {
    node= stack.top();
    stack.pop();
}

const T &AVLTree::Iterator::operator*() const {
    if(node== nullptr)
        throw InvalidIterator();
    return node->data;
}
AVLTree::Iterator::Iterator(BSTNode* root):node(root), stack(Stack<BSTNode*>()){
    if(!node)
        return;
    while(node->left)
        Left();
}

AVLTree::Iterator &AVLTree::Iterator::operator++() {
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

bool AVLTree::Iterator::operator!=(const AVLTree::Iterator& it) const {
    return node!=it.node;
}


BSTNode::BSTNode(int key, T data, BSTNode *right, BSTNode *left):
    key(key), data(data), right(right), left(left){}

BSTNode *AVLTree::search_req(int key, BSTNode *n) {
    if(n == nullptr){
        return nullptr;
    }
    if(key == n->key){
        return n;
    }
    else if(key < n->key){
        return search_req(key,n->left);
    }
    else if(key > n->key){
        return search_req(key,n->right);
    }
    return nullptr;
}

BSTNode *AVLTree::search(int key) {
    return search_req(key,root);
}

void AVLTree::append(int key, T data) {
    if(root == nullptr){
        root = new BSTNode(key, data);
        return;
    }
    append_req(key,data,root);
}

void AVLTree::append_req(int key, T data, BSTNode *n) {
    if(key < n->key){
        if(n->left == nullptr){
            n->left = new BSTNode(key, data);
        }
        else{
            append_req(key,data,n->left);
        }
    }
    else if(key > n->key){
        if(n->right == nullptr){
            n->right = new BSTNode(key, data);
        }
        else {
            append_req(key, data, n->right);
        }
    }
}

void AVLTree::print_inorder() {
    if(root == nullptr) return;
    print_inorder_req(root);
}

void AVLTree::print_inorder_req(BSTNode *n) {
    if(n == nullptr) return;
    print_inorder_req(n->left);
    cout<<"(key= "<<n->key<<", data= "<<n->data<<")"<<endl;
    print_inorder_req(n->right);
}

T AVLTree::get(int key) {
    BSTNode* n = search(key);
    if(n == nullptr){
        throw KeyNotExists();
    }
    return n->data;
}

AVLTree::Iterator AVLTree::begin() const {
    return AVLTree::Iterator(root);
}

AVLTree::Iterator AVLTree::end() const {
    return AVLTree::Iterator(nullptr);
}

AVLTree::AVLTree(const Compare &cmp) : root(nullptr), cmp(&cmp){}

#endif //AVLTREE_H
