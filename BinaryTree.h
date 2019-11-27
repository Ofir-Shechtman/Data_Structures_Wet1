//
// Created by Ben Lugasi on 27/11/2019.
//

#ifndef DATA_STRUCTURES_WET1_BINARYTREE_H
#define DATA_STRUCTURES_WET1_BINARYTREE_H
#include <iostream>

using namespace std;
typedef int T;

struct Node{
    int key;
    T data;
    Node* right;
    Node* left;
};

class BST{
    Node * root;
    Node *search_req(int key, Node *n);
    void append_req(int key,T data, Node* n);
    void remove_req(int key, Node* n);
    void print_inorder_req(Node *n);
public:
    BST(): root(nullptr){}
    ~BST() = default;
    Node *search(int key);
    void append(int key,T data);
    void remove(int key);
    void print_inorder();
    T get(int key);
};

Node *BST::search_req(int key, Node *n) {
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

Node *BST::search(int key) {
    return search_req(key,root);
}

void BST::append(int key, T data) {
    if(root == nullptr){
        root = new Node;
        root->key = key;
        root->data = data;
        root->left = nullptr;
        root->right = nullptr;
        return;
    }
    append_req(key,data,root);
}

void BST::append_req(int key, T data, Node *n) {
    if(key < n->key){
        if(n->left == nullptr){
            n->left = new Node;
            n->left->key = key;
            n->left->data = data;
            n->left->left = nullptr;
            n->left->right = nullptr;
        }
        else{
            append_req(key,data,n->left);
        }
    }
    else if(key > n->key){
        if(n->right == nullptr){
            n->right = new Node;
            n->right->key = key;
            n->right->data = data;
            n->right->left = nullptr;
            n->right->right = nullptr;
        }
        else {
            append_req(key, data, n->right);
        }
    }
}

void BST::print_inorder() {
    if(root == nullptr) return;
    print_inorder_req(root);
}

void BST::print_inorder_req(Node *n) {
    if(n == nullptr) return;
    print_inorder_req(n->left);
    cout<<"(key= "<<n->key<<", data= "<<n->data<<")"<<endl;
    print_inorder_req(n->right);
}

T BST::get(int key) {
    Node* n = search(key);
    if(n != nullptr){
        return n->data;
    }
    return -1;
}

#endif //DATA_STRUCTURES_WET1_BINARYTREE_H
