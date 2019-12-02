//
// Created by Ben Lugasi on 27/11/2019.
//

#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <utility>
#include "Stack.h"

using namespace std;
typedef int K;
typedef int T;


//template <class K>
class Compare{
public:
    Compare()= default;
    virtual ~Compare()= default;
    virtual bool operator()(K key1, K key2)=0;
};



class AVLTree{
    struct Node;
    Node * root;
    const Compare* cmp;

public:
    explicit AVLTree(const Compare& cmp);
    ~AVLTree() = default;
    Node *search_req(K key, Node *n);
    void append_req(K key,T data, Node* n);
    void remove_req(K key, Node* n);
    void print_inorder_req(Node *n);
    void print_inorder();
    Node* search(K key);
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    class KeyNotExists : public exception{};
};

//template <class K, class T>
struct AVLTree::Node{
    K key;
    T data;
    Node* right;
    Node* left;
    Node(K key, T data, Node* right= nullptr, Node* left= nullptr);
};

class AVLTree::Iterator{
    Node* node;
    Stack<Node*> stack;
    void Left();
    void Right();
    void Father();
public:
    explicit Iterator(Node* root);
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
AVLTree::Iterator::Iterator(Node* root):node(root), stack(Stack<Node*>()){
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


Node::Node(K key, T data, Node *right, Node *left):
    key(key), data(data), right(right), left(left){}

Node *AVLTree::search_req(K key, Node *n) {
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

Node *AVLTree::search(K key) {
    return search_req(key,root);
}



void AVLTree::append_req(K key, T data, Node *n) {
    if(key < n->key){
        if(n->left == nullptr){
            n->left = new Node(key, data);
        }
        else{
            append_req(key,data,n->left);
        }
    }
    else if(key > n->key){
        if(n->right == nullptr){
            n->right = new Node(key, data);
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

void AVLTree::print_inorder_req(Node *n) {
    if(n == nullptr) return;
    print_inorder_req(n->left);
    cout<<"(key= "<<n->key<<", data= "<<n->data<<")"<<endl;
    print_inorder_req(n->right);
}



AVLTree::Iterator AVLTree::begin() const {
    return AVLTree::Iterator(root);
}

AVLTree::Iterator AVLTree::end() const {
    return AVLTree::Iterator(nullptr);
}

AVLTree::AVLTree(const Compare &cmp) : root(nullptr), cmp(&cmp){}

#endif //AVLTREE_H
