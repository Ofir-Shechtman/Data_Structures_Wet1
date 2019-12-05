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
        root= nullptr;
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

    t.erase(15);
    test(t, "{(30,(20,(10,,),(25,,)),(35,,))}");
    t.insert(15);
    t.erase(10);
    test(t, "{(30,(20,(15,,),(25,,)),(35,,))}");
    t.erase(10);

    /*
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

    t.~AVLTree_test();

    int arr[100]={16, 91, 80, 53, 41, 28, 12, 10, 81, 97, 1, 84, 36, 52, 64, 68, 60, 40, 7, 67, 4, 54, 30, 66, 34, 3, 23, 48, 73, 27, 45, 92, 76, 70, 47, 88, 9, 82, 5, 46, 26, 42, 83, 90, 77, 6, 38, 58, 13, 56, 21, 98, 87, 61, 37, 89, 24, 32, 2, 33, 59, 62, 78, 39, 57, 51, 79, 69, 86, 55, 65, 96, 99, 94, 17, 29, 25, 85, 22, 8, 71, 18, 15, 74, 63, 20, 19, 0, 44, 93, 95, 43, 50, 49, 31, 72, 35, 14, 75, 11};
    for(int i : arr){
        t.insert(i);
    }
    test(t.is_sorted(), "True");
    t.erase(15);
    t.erase(50);
    t.erase(95);
    test(t.is_sorted(), "True");
*/


    total();
}

