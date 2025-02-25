#ifndef TEST_AVLTREE_H
#define TEST_AVLTREE_H

#include "Test_utility.h"
#include "AVLTree.h"
#include <map>
#include <list>
#include <vector>
using namespace std;


template<class K>
class CompareReverse : public Compare<K>{
public:
    bool operator()(const K& a, const K& b) const{
        return a < b;
    }
};


class AVLTree_test : public AVLTree<int, int>{
    //Compare<int>* cmp;
public:
    AVLTree_test(): AVLTree<int, int>(new CompareReverse<int>()){}
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
    test(t, "{(20,(10,,),(30,(25,,),(35,,)))}");
    t.insert(15);
    t.erase(10);
    test(t, "{(20,(15,,),(30,(25,,),(35,,)))}");
    t.erase(20);
    test(t, "{(30,(15,,(25,,)),(35,,))}");


    t.clear();

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

    t.clear();

    int arr[100]={16, 91, 80, 53, 41, 28, 12, 10, 81, 97, 1, 84, 36, 52, 64, 68, 60, 40, 7, 67, 4, 54, 30, 66, 34, 3, 23, 48, 73, 27, 45, 92, 76, 70, 47, 88, 9, 82, 5, 46, 26, 42, 83, 90, 77, 6, 38, 58, 13, 56, 21, 98, 87, 61, 37, 89, 24, 32, 2, 33, 59, 62, 78, 39, 57, 51, 79, 69, 86, 55, 65, 96, 99, 94, 17, 29, 25, 85, 22, 8, 71, 18, 15, 74, 63, 20, 19, 0, 44, 93, 95, 43, 50, 49, 31, 72, 35, 14, 75, 11};
    for(int i : arr){
        t.insert(i);
    }
    test(t.is_sorted(), "True");
    t.erase(15);
    t.erase(50);
    t.erase(95);
    test(t.is_sorted(), "True", __LINE__);

    AVLTree_test t2(t);
    t.erase(80);
    test(t.size() == t2.size(), "False", __LINE__);
    t.insert(400);
    t2.erase(80);
    test(t.size() == t2.size(), "False", __LINE__);
    t2=t;
    test(t.size() == t2.size(), "True", __LINE__);


    t.clear();
    test(t.empty(), "True");

    bool exceptionThrown = false;
    try{t.erase(0);}
    catch(AVLTree<int,int>::KeyNotExists&){
        exceptionThrown=true;
        test(exceptionThrown);
    }
    if(!exceptionThrown)
        test(exceptionThrown);

    try{t.find(10);}
    catch(AVLTree<int,int>::KeyNotExists&){
        exceptionThrown=true;
        test(exceptionThrown);
    }
    if(!exceptionThrown)
        test(exceptionThrown);


    //BIG TEST
    t.insert(94);
    t.erase(94);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(15);
    t.erase(15);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(40);
    t.erase(40);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(51);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(95);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(88);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(49);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(85);
    t.erase(85);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(62);
    t.erase(88);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(26);
    t.erase(62);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(13);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(84);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(72);
    t.erase(51);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(11);
    t.erase(13);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(52);
    t.erase(72);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(30);
    t.erase(11);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(86);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(12);
    t.erase(52);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(69);
    t.erase(12);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(17);
    t.erase(17);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(56);
    t.erase(84);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(58);
    t.erase(69);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(50);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(63);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(40);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(77);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(22);
    t.erase(49);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(93);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(21);
    t.erase(21);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(27);
    t.erase(95);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(17);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(38);
    t.erase(93);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(73);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(81);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(65);
    t.erase(27);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(8);
    t.erase(56);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(54);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(47);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(53);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(62);
    t.erase(86);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(49);
    t.erase(53);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(36);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(11);
    t.erase(73);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(18);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(78);
    t.erase(81);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(2);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(32);
    t.erase(8);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(53);
    t.erase(54);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(89);
    t.erase(36);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(51);
    t.erase(50);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(88);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(67);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(98);
    t.erase(26);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(26);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(85);
    t.erase(49);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(71);
    t.erase(62);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(12);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(28);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(94);
    t.erase(71);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(76);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(54);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(64);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(24);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(9);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(25);
    t.erase(94);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(20);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(56);
    t.erase(32);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(83);
    t.erase(65);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(71);
    t.erase(71);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(86);
    t.erase(51);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(43);
    t.erase(85);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(37);
    t.erase(63);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(16);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(34);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(7);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(1);
    t.erase(24);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(73);
    t.erase(18);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(48);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(59);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(69);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(50);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(55);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(27);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(49);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(36);
    t.erase(55);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(51);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(72);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(75);
    t.erase(56);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(5);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(97);
    t.erase(89);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(90);
    t.erase(69);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(74);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(55);
    t.erase(97);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(14);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(63);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(69);
    t.erase(7);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(21);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(81);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(52);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(80);
    t.erase(16);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(13);
    t.erase(55);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(10);
    t.erase(81);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(62);
    t.erase(59);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(97);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(87);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(7);
    t.erase(48);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(92);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(59);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(65);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(18);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(41);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(48);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(45);
    t.erase(97);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(61);
    t.erase(87);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(57);
    t.erase(78);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(46);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(29);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(33);
    t.erase(1);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(15);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(95);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(99);
    t.erase(57);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(56);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(44);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(39);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(24);
    t.erase(75);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(42);
    t.erase(99);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(19);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(71);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(23);
    t.erase(88);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(70);
    t.erase(5);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(87);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(57);
    t.erase(38);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(89);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(3);
    t.erase(39);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(4);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(99);
    t.erase(58);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(0);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(84);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(5);
    t.erase(33);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(97);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(78);
    t.erase(92);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(94);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(38);
    t.erase(57);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(92);
    t.erase(24);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(33);
    t.erase(64);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(82);
    t.erase(47);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(55);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(8);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(16);
    t.erase(5);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(47);
    t.erase(82);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(93);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(1);
    t.erase(84);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(82);
    t.erase(93);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(93);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(60);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(58);
    t.erase(27);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(32);
    t.erase(93);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(57);
    t.erase(11);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(88);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(84);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(81);
    t.erase(87);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(64);
    t.erase(19);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(87);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(35);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(24);
    t.erase(97);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(6);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(11);
    t.erase(28);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(91);
    t.erase(11);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(85);
    t.erase(58);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(96);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(19);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(68);
    t.erase(73);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(28);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(75);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(93);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(73);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(11);
    t.erase(34);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(31);
    t.erase(30);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(30);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(27);
    t.erase(48);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(39);
    t.erase(53);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(79);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(66);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(58);
    t.erase(14);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(5);
    t.erase(9);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(53);
    t.erase(45);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(34);
    t.erase(76);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(76);
    t.erase(67);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(48);
    t.erase(48);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(14);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(67);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(48);
    t.erase(17);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(45);
    t.erase(77);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(97);
    t.erase(29);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(77);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(9);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(29);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(17);
    t.erase(1);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(1);
    t.erase(46);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(46);
    t.erase(41);
    test(t.is_sorted(), "True", __LINE__);
    t.insert(41);
    test(t.is_sorted(), "True", __LINE__);
    total();
}

void AVLTree_Test_sp(){
    AVLTree_test t;
    t.insert(51);
    t.insert(299);
    t.insert(20);
    t.erase(20);
    t.insert(93);
    t.erase(299);
    t.insert(277);
    t.erase(277);
    t.insert(276);
    t.insert(294);
    t.insert(183);
    t.erase(183);
    t.insert(142);
    t.insert(129);
    t.insert(164);
    t.erase(164);
    t.insert(164);
    t.insert(73);
    t.insert(131);
    t.erase(142);
    t.insert(142);
    t.insert(59);
    t.erase(73);
    t.erase(93);
    t.insert(290);
    t.erase(290);
    t.insert(290);
    t.erase(131);
    t.insert(194);
    t.erase(142);
    /*
    t.insert(5);
    test(t, "{(5,,)}");
    t.insert(1);
    test(t, "{(5,(1,,),)}");
    t.insert(6);
    test(t, "{(5,(1,,),(6,,))}");
    t.insert(3);
    test(t, "{(5,(1,,(3,,)),(6,,))}");
    t.insert(8);
    test(t, "{(5,(1,,(3,,)),(6,,(8,,)))}");
    t.insert(2);
    test(t, "{(5,(1,,(3,(2,,),)),(6,,(8,,)))}", __LINE__);
    t.insert(4);
    test(t, "{(5,(1,,(3,(2,,),(4,,))),(6,,(8,,)))}", __LINE__);
    t.insert(4);
    test(t, "{(5,(1,,(3,(2,,),(4,,))),(6,,(8,(7,,),)))}", __LINE__);
     */
    test(t, "{(5,(1,,(3,(2,,),(4,,))),(6,,(8,(7,,),)))}", __LINE__);
    test(t.is_sorted(), "True", __LINE__);
    test(t.size() == 8, "True", __LINE__);
    //t.erase(80);
    total();
}

#endif //TEST_AVLTREE_H