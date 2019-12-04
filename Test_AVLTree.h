#include "Test_utility.h"
#include "AVLTree.h"
#include <map>
#include <list>
#include <vector>
using namespace std;

class AVLTree_test : public AVLTree<int, int>{
public:
    ~AVLTree_test(){
        delete root;
    }
    friend string print(AVLTree_test::Node* tree);
    Node* get_root() const{
        return  root;
    }
    bool is_sorted(){
        list<int> l;
        for(auto i : *this)
            l.push_back(i.first);
        auto sort=l;
        sort.sort();
        return l==sort;
    }
    void printBT(const std::string& prefix, const Node* node, bool isLeft)
    {
        if( node != nullptr )
        {
            std::cout << prefix;

            std::cout << (isLeft ? "├──" : "└──" );

            // print the value of the node
            std::cout << node->key << std::endl;

            // enter the next tree level - left and right branch
            printBT( prefix + (isLeft ? "│   " : "    "), node->left, true);
            printBT( prefix + (isLeft ? "│   " : "    "), node->right, false);
        }
    }

    void printBT(const Node* node)
    {
        printBT("", node, false);
    }



};

string print(AVLTree_test::Node* n) {
    string result= "(";
    result += to_string(n->key) + ",";
    result+= (n->left ? print(n->left) : "") + ",";
    result+= n->right ? print(n->right) : "";
    result+= ")";
    return result;
}

string print(const AVLTree_test& tree){
    string result= "{";
    result+= print(tree.get_root());
    result+= "}";
    return result;
}


//template <class T>
ostream& operator<<(ostream& os, const AVLTree_test& data){
    return os << print(data) << endl;
}


void AVLTree_Test(){
    AVLTree_test t;
    t.insert(30);
    test(t, "{(30,,)}");
    t.insert(20);
    test(t, "{(30,(20,,),)}");
    t.insert(35);
    test(t, "{(30,(20,,),(35,,))}");
    t.insert(10);
    test(t, "{(30,(20,(10,,),),(35,,))}",__LINE__);
    t.insert(25);
    test(t, "{(30,(20,(10,,),(25,,)),(35,,))}");
    t.insert(15);//LL needed
    test(t, "{(20,(10,,(15,,)),(30,(25,,),(35,,)))}");
    test(t.is_sorted(), "True");

    t.~AVLTree_test();

    t.insert(10);
    test(t, "{(10,,)}");
    t.insert(5);
    test(t, "{(10,(5,,),)}");
    t.insert(30);
    test(t, "{(10,(5,,),(30,,))}");
    t.insert(20);
    test(t, "{(10,(5,,),(30,(20,,),))}");
    t.insert(35);
    test(t, "{(10,(5,,),(30,(20,,),(35,,)))}");
    t.insert(15);//RL needed
    test(t, "{(20,(10,(5,,),(15,,)),(30,,(35,,)))}");
    test(t.is_sorted(), "True");



    total();
}

