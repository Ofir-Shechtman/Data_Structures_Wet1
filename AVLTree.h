#include <utility>

#include <utility>

#include <utility>

//
// Created by Ben Lugasi on 27/11/2019.
//

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include "Stack.h"

using namespace std;
typedef int T;


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
    void append_req(int key,T data, BSTNode* n);
    void remove_req(int key, BSTNode* n);
    void print_inorder_req(BSTNode *n);
public:
    class Iterator;
    AVLTree(): root(nullptr){}
    ~AVLTree() = default;
    BSTNode *search(int key);
    void append(int key,T data);
    void remove(int key);
    void print_inorder();
    T get(int key);
};

class AVLTree::Iterator{
    BSTNode* node;
    Stack<BSTNode*> stack;
    bool left, right;
    void Left();
    void Right();
    void Father();
public:
    friend class List<T>;
    explicit Iterator(BSTNode* node= nullptr, Stack<BSTNode*> stack=Stack<BSTNode*>());
    const T& operator*() const;
    Iterator& operator++();
    bool operator!=(const Iterator& it) const;
};

void AVLTree::Iterator::Left() {
    stack.push(node);
    node=node->left;
}

void AVLTree::Iterator::Right() {
    stack.push(node);
    node=node->right;
    left=false;
}

void AVLTree::Iterator::Father() {
    auto father = stack.top();
    //left= father->left==node;
    right= father->right==node;
    node= father;
    stack.pop();
}

const T &AVLTree::Iterator::operator*() const {
    return node->data;
}
AVLTree::Iterator::Iterator(BSTNode *node, Stack<BSTNode*> stack):
node(node), stack(std::move(stack)), left(false), right(false){}

AVLTree::Iterator &AVLTree::Iterator::operator++() {
    if(!left) {
        if (node->left){
            Left();
            if (node->left)
                ++*this;
        }
        else
            Father();
    }
    else if(!right){
        if (node->right){
            Right();
            if (node->left)
                ++*this;
    }
        else
            Father();
    }
    else
        Father();
    return *this;
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
    if(n != nullptr){
        return n->data;
    }
    return -1;
}

#endif //AVLTREE_H
