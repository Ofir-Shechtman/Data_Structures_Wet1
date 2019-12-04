#include <iostream>
#include "Stack.h"

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
    struct Node;
    Node *root;
    Compare<K> cmp;
    Node *find_req(const K &key, Node *n);
    Node *insert_req(const K &key, const T &data, Node* n, Stack<Node*>* s);
    void print_inorder_req(Node *n);
public:
    explicit AVLTree(Compare<K> cmp=Compare<K>()): root(nullptr), cmp(cmp){}
    AVLTree(const AVLTree &tree);
    AVLTree<K, T>& operator=(const AVLTree & tree);
    ~AVLTree();

    Node *find(const K &key);
    Node *insert(const K &key,const T &data);
    void erase(const K &key);
    void clear();
    bool empty() const;
    class KeyNotExists : public exception{};

    class Iterator;
    Iterator begin() const;
    Iterator end() const;

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
typename AVLTree<K,T>::Node *AVLTree<K,T>::find_req(const K &key, AVLTree::Node *n) {
    if(n == nullptr){
        return nullptr;
    }
    else if(cmp(key, n->key)){
        return find_req(key, n->left);
    }
    else if(cmp(n->key, key)){
        return find_req(key, n->right);
    }
    return n;
}

template <class K, class T>
typename AVLTree<K,T>::Node *AVLTree<K,T>::find(const K &key) {
    return find_req(key, root);
}

template <class K, class T>
typename AVLTree<K,T>::Node *AVLTree<K,T>::insert(const K &key, const T &data) {
    if(root == nullptr){
        root = new Node(key,data);
        return root;
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
    return new_node;
}

template <class K, class T>
typename AVLTree<K,T>::Node *AVLTree<K,T>::insert_req(const K &key, const T &data, AVLTree::Node* n,
                                                      Stack<AVLTree::Node*>* s) {
    s->push(n);
    if(cmp(key, n->key)){
        if(n->left == nullptr){
            n->left = new Node(key, data);
            return n->left;
        }
        else{
            insert_req(key, data, n->left, s);
        }
    }
    else if(cmp(n->key, key)){
        if(n->right == nullptr){
            n->right = new Node(key, data);
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
bool AVLTree<K, T>::empty() {
    if(root == nullptr){
        return true;
    }
    return false;
}

template<class K, class T>
AVLTree<K, T>::AVLTree(const AVLTree &tree) {
    root = tree.root;
    cmp = tree.cmp;
}

template<class K, class T>
AVLTree<K, T>& AVLTree<K, T>::operator=(const AVLTree &tree) {
    root = tree.root;
    cmp = tree.cmp;
    return *this;
}

int main() {
    AVLTree<int,int> tree;
    tree.insert(10,999);
    tree.insert(30,999);
    tree.insert(5,999);
    tree.insert(35,999);
    tree.insert(20,999);
    tree.insert(15,999);
    tree.print_inorder();
    return 0;
}
