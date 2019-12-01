#ifndef LIST_H
#define LIST_H


template<class T>
struct Node{
    T data;
    Node<T>* next;
    Node<T>* previous;
    Node(T data, Node* next, Node* previous);
    ~Node()= default;
};

template<class T>
class List{
    Node<T> *head, *tail;
    int list_size;
public:
    List();
    List(const List<T>&);
    ~List();
    List<T>& operator=(const List&);
    class Iterator;
    void erase(Iterator);
    void pop_back();
    void pop_front();
    Iterator insert(const List<T>::Iterator& pos, const T &value);
    Iterator push_back(const T &value);
    Iterator push_front(const T &value);
    const T& front() const;
    const T& back() const;
    const int& size() const;
    void clear();
    Iterator begin() const;
    Iterator end() const;
    bool empty() const;
    class EmptyList : public std::exception{};
};

template<class T>
class List<T>::Iterator{
    Node<T>* node;
public:
    friend class List<T>;
    explicit Iterator(Node<T>* node= nullptr);
    const T& operator*() const;
    Iterator& operator++();
    Iterator& operator--();
    bool operator!=(const Iterator& it) const;
    class InvalidIterator : public std::exception{};
};


template<class T>
Node<T>::Node(T data, Node *next, Node *previous):data(data), next(next),previous(previous){}

template<class T>
void List<T>::erase(List::Iterator it) {
    if(!it.node)
        throw typename List<T>::Iterator::InvalidIterator();
    Node<T>* n=it.node;
    if(n->next)
        n->next->previous=n->previous;
    else
        tail=n->previous;
    if(n->previous)
        n->previous->next=n->next;
    else
        head=n->next;
    delete n;
    --list_size;
}

template<class T>
List<T>::List():head(nullptr), tail(nullptr), list_size(0){}


template<class T>
List<T>::~List() {
    clear();
}

template<class T>
typename List<T>::Iterator List<T>::insert(const List<T>::Iterator &pos, const T &value) {
    if(!pos.node)
        throw typename List<T>::Iterator::InvalidIterator();
    Node<T>* node= new Node<T>(value, pos.node->next, pos.node);
    pos.node->next=node;
    if(node->next)
        node->next->previous=node;
    else
        tail=node;
    ++list_size;
    return Iterator(node);
}

template<class T>
typename List<T>::Iterator List<T>::push_back(const T &value) {
    if(empty())
        return push_front(value);
    return insert(Iterator(tail), value);
}

template<class T>
typename List<T>::Iterator List<T>::push_front(const T &value) {
    auto* node= new Node<T>(value, head, nullptr);
    if(!empty())
        head->previous=node;
    else
        tail=node;
    head=node;
    ++list_size;
    return Iterator(head);
}

template<class T>
void List<T>::pop_back() {
    if(empty())
        throw EmptyList();
    erase(Iterator(tail));
}

template<class T>
void List<T>::pop_front() {
    if(empty())
        throw EmptyList();
    erase(Iterator(head));
}

template<class T>
bool List<T>::empty() const{
    return tail==nullptr;

}
template<class T>
const int & List<T>::size() const {
    return list_size;
}

template<class T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(head);
}

template<class T>
typename List<T>::Iterator List<T>::end() const{
    return Iterator(nullptr);
}

template<class T>
const T& List<T>::front() const{
    if(empty())
        throw EmptyList();
    return head->data;
}

template<class T>
const T& List<T>::back() const{
    if(empty())
        throw EmptyList();
    return tail->data;
}

template<class T>
List<T>::List(const List& list) : head(nullptr), tail(nullptr), list_size(list.list_size){
    *this=list;
}

template<class T>
List<T> &List<T>::operator=(const List& list) {
    if(this==&list)
        return *this;
    clear();
    auto i=list.begin();
    auto n= push_back(*i);
    head=n.node;
    for (++i;i!=list.end(); ++i){
        n=push_back(*i);
    }
    tail=n.node;
}

template<class T>
void List<T>::clear() {
    Node<T>* n= head, *temp;
    while(n){
        temp=n;
        n=n->next;
        delete temp;
    }
    head= nullptr;
    tail= nullptr;
}


template<class T>
List<T>::Iterator::Iterator(Node<T> *node) : node(node) {}

template<class T>
const T& List<T>::Iterator::operator*() const {
    return node->data;
}

template<class T>
typename List<T>::Iterator &List<T>::Iterator::operator++() {
    if(!node)
        throw typename List<T>::Iterator::InvalidIterator();
    node=node->next;
    return *this;
}

template<class T>
typename List<T>::Iterator &List<T>::Iterator::operator--() {
    if(!node)
        throw typename List<T>::Iterator::InvalidIterator();
    node=node->previous;
    return *this;
}


template<class T>
bool List<T>::Iterator::operator!=(const List<T>::Iterator& it) const {
    return node!=it.node;
}

#endif //LIST_H
