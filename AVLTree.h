#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include "Stack.h"
#include "Pair.h"

using namespace std;

template <class K>
class Compare{
public:
    Compare()= default;
    virtual ~Compare()= default;
    virtual bool operator()(K key1, K key2){return key1<key2;};
};

template <class K, class T>
class AVLTree{
protected:    //TODO: remove after test
    struct Node;
    Node *root;
    Compare<K> cmp;
    unsigned int size;
    Node *find_req(const K &key, Node *n, Stack<Node*>* s= nullptr);
    Node *insert_req(const K &key, const T &data, Node* n, Stack<Node*>* s);
    void print_inorder_req(Node *n);
public:
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    explicit AVLTree(Compare<K> cmp=Compare<K>()): root(nullptr), cmp(cmp), size(0){}
    //AVLTree(const AVLTree &tree);
    //AVLTree<K, T>& operator=(const AVLTree & tree);
    ~AVLTree() = default;
    Iterator find(const K& key) const;// TODO: what to return if not found
    Iterator insert(const K& key, const T& data=T());
    void erase(const K& key);
    bool empty() const;
    int get_size() const;
    //void clear();
    class KeyNotExists : public exception{};
    void print_inorder();
};

template <class K, class T>
struct AVLTree<K,T>::Node{
    K key;
    T data;
    unsigned int height;
    Node* right;
    Node* left;
    explicit Node(K key, T data, unsigned int height = 0,
                  Node *right = nullptr, Node *left = nullptr):
            key(key), data(data),height(height), right(right), left(left){}
    int BF();
    void balance();
    void LL();
    void LR();
    void RR();
    void RL();
};


template <class K, class T>
class AVLTree<K,T>::Iterator{
protected:   //TODO: remove after test
    Node* node;
    Stack<Node*> stack;
    void Left();
    void Right();
    void Father();
public:
    friend AVLTree;
    explicit Iterator(Node* root= nullptr);
    Pair<K,T> operator*() const;   //TODO: remove after test
    Iterator& operator++();
    bool operator!=(const Iterator& it) const;
    class InvalidIterator : public exception{};
};

template <class K, class T>
typename AVLTree<K,T>::Node* AVLTree<K,T>::find_req(const K &key, AVLTree::Node *n, Stack<Node*> *s) {
    if(n == nullptr)
        return nullptr;
    if(s)
        s->push(n);

    if(cmp(key, n->key)){
        return find_req(key, n->left, s);
    }
    else if(cmp(n->key, key)){
        return find_req(key, n->right, s);
    }
    return n;
}


template <class K, class T>
typename AVLTree<K,T>::Iterator AVLTree<K,T>::find(const K &key) const {
    Node *n = find_req(key, root);
    if(!n){
        throw KeyNotExists();
    }
    return Iterator(n);
}

template<class K, class T>
typename AVLTree<K,T>::Iterator AVLTree<K, T>::begin() const {
    return AVLTree::Iterator(root);
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


template <class K, class T>
bool AVLTree<K,T>::Iterator::operator!=(const AVLTree<K, T>::Iterator& it) const {
    return node!=it.node;
}

template <class K, class T>
typename AVLTree<K,T>::Iterator AVLTree<K,T>::insert(const K &key, const T &data) {
    if(root == nullptr){
        root = new Node(key,data);
        size++;
        return Iterator(root);
    }
    Stack<Node*> s;
    AVLTree::Node *new_node = insert_req(key, data, root, &s);
    AVLTree::Node *n;
    while(!s.empty()){
        n = s.top();
        s.pop();
        n->balance();
        unsigned int left = n->left ? n->left->height : 0;
        unsigned int right = n->right ? n->right->height : 0;
        n->height=max(left, right)+1;
    }
    return Iterator(new_node);
}

template <class K, class T>
typename AVLTree<K,T>::Node *AVLTree<K,T>::insert_req(const K &key, const T &data, AVLTree::Node* n,
                                                      Stack<AVLTree::Node*>* s) {
    s->push(n);
    if(cmp(key, n->key)){
        if(n->left == nullptr){
            n->left = new Node(key, data);
            size++;
            return n->left;
        }
        else{
            insert_req(key, data, n->left, s);
        }
    }
    else if(cmp(n->key, key)){
        if(n->right == nullptr){
            n->right = new Node(key, data);
            size++;
            return n->right;
        }
        else {
            insert_req(key, data, n->right, s);
        }
    }
    return nullptr;
}

template <class K, class T>
void AVLTree<K,T>::print_inorder() {
    if(root == nullptr) return;
    print_inorder_req(root);
}

template <class K, class T>
void AVLTree<K,T>::print_inorder_req(AVLTree::Node *n) {
    if(n == nullptr) return;
    print_inorder_req(n->left);
    cout<<n->key<<" ";
    print_inorder_req(n->right);
}

template <class K, class T>
void AVLTree<K,T>::Node::balance() {
    if (BF() == 2 && left->BF() >= 0) {
        LL();
    }
    else if (BF() == 2 && left->BF() == -1){
        LR();
    }
    else if (BF() == -2 && right->BF() <= 0){
        RR();
    }
    else if (BF() == -2 && right->BF() == 1){
        RL();
    }
}

template <class K, class T>
int AVLTree<K,T>::Node::BF() {
    unsigned int l = left ? left->height : -1;
    unsigned int r = right ? right->height : -1;
    return l - r;
}

template <class K, class T>
void AVLTree<K,T>::Node::LL() {
    cout<<"Performing LL"<<endl;
    AVLTree::Node *left_son, *left_left_son, *left_right_son, *right_son;
    left_son = left;
    left_left_son = left->left;
    left_right_son = left->right;
    right_son = right;

    left = left_left_son;
    right = left_son;
    left_son->left = left_right_son;
    left_son->right = right_son;
    swap(key, left_son->key);
    swap(data, left_son->data);}

template <class K, class T>
void AVLTree<K,T>::Node::RR() {
    cout<<"Performing RR"<<endl;
    AVLTree::Node *right_son, *right_left_son, *right_right_son, *left_son;
    right_son = right;
    right_left_son = right->left;
    right_right_son = right->right;
    left_son = left;

    right = right_right_son;
    left = right_son;
    right_son->left = left_son;
    right_son->right = right_left_son;
    swap(key, right_son->key);
    swap(data, right_son->data);
}

template <class K, class T>
void AVLTree<K,T>::Node::LR() {
    cout<<"Performing LR"<<endl;
    left->RR();
    LL();
}

template <class K, class T>
void AVLTree<K,T>::Node::RL() {
    cout<<"Performing RL"<<endl;
    right->LL();
    RR();
}

template<class K, class T>
bool AVLTree<K, T>::empty() const{
    return root == nullptr;
}

template<class K, class T>
void AVLTree<K, T>::erase(const K &key) {
    Stack<Node*> s;
    Node* n=find_req(key, root, &s);
    if(!n)
        return;
    Node* father=s.top();
    //CASE 1: no children
    if(!n->right && !n->left){
        if(father)
            father->left==n ? father->left= nullptr : father->right= nullptr;
        delete n;
        if(father)
            father->balance();
    }
    //CASE 2: one child
    else if(!n->right || !n->left){
        if(n->right){
            swap(n->key, n->right->key);
            swap(n->data, n->right->data);
            delete n->right;
            n->right= nullptr;
        }
        else{
            swap(n->key, n->left->key);
            swap(n->data, n->left->data);
            delete n->left;
            n->left= nullptr;
        }
        n->balance();
    }
    //CASE 3: has 2 children
    else{
        Iterator it(root);
        it.node=n;
        it.stack=s;
        Node* next= (++it).node;
        swap(n->key, next->key);
        swap(n->data, next->data);
        erase(next->key);
        next->balance();
    }

}

template<class K, class T>
int AVLTree<K, T>::get_size() const {
    return size;
}

template<class K, class T>
Pair<K, T> AVLTree<K, T>::Iterator::operator*() const {
    return Pair<K,T>(node->key, node->data);
}

#endif //AVLTREE_H
