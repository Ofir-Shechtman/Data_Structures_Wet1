#ifndef TEST_MAP_H
#define TEST_MAP_H

#include "Test_utility.h"
#include "List.h"
using namespace std;


string print(const List<int>& list){
    string result= "[";
    for(int i : list){
        result+= to_string(i);
        result+= ", ";
    }
    if(!list.empty()) {
        result.pop_back();
        result.pop_back();
    }
    result+= "]";
    return result;
}


//template <class T>
ostream& operator<<(ostream& os, const List<int>& data){
    return os << print(data) << endl;
}


void List_Test(){
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_front(4);
    l.push_front(5);
    test(l,"[5, 4, 1, 2, 3]");
    l.pop_front();
    test(l,"[4, 1, 2, 3]");
    l.pop_back();
    test(l,"[4, 1, 2]");
    test(*l.begin(),"4");
    l.erase(++l.begin());
    test(l,"[4, 2]");
    test(l.empty(),"False");
    test(l.size(),"2");
    l.insert(l.begin(), 6);
    test(l,"[4, 6, 2]");
    l.pop_back();
    l.pop_back();
    l.pop_back();
    test(l.empty(),"True");
    bool exceptionThrown = false;
    try{l.pop_front();}
    catch(List<int>::EmptyList&){
        exceptionThrown=true;
        test(exceptionThrown);
    }
    if(!exceptionThrown)
        test(exceptionThrown);
    l.push_front(7);
    test(l.front(),"7");
    exceptionThrown = false;
    try{l.insert(++l.begin(), 8);}
    catch(List<int>::Iterator::InvalidIterator&){
        exceptionThrown=true;
        test(exceptionThrown);
    }
    if(!exceptionThrown)
        test(exceptionThrown);
    l.insert(l.begin(), 8);
    test(l.back(),"8");
    List<int> l2(l);
    test(l2,"[7, 8]");
    l2=l2;
    test(l2,"[7, 8]");
    l2.push_back(9);
    l=l2;
    test(l2,"[7, 8, 9]", __LINE__);
    exceptionThrown = false;
    try{++l.end();}
    catch(List<int>::Iterator::InvalidIterator&){
        exceptionThrown=true;
        test(exceptionThrown);
    }
    if(!exceptionThrown)
        test(exceptionThrown);
    //
    exceptionThrown = false;
    try{--(--l.begin());}
    catch(List<int>::Iterator::InvalidIterator&){
        exceptionThrown=true;
        test(exceptionThrown);
    }
    if(!exceptionThrown)
        test(exceptionThrown);
    exceptionThrown = false;
    //
    try{l.erase(List<int>::Iterator());}
    catch(List<int>::Iterator::InvalidIterator&){
        exceptionThrown=true;
        test(exceptionThrown);
    }
    if(!exceptionThrown)
        test(exceptionThrown);
    l.clear();
    test(l,"[]",__LINE__);
    total();
}

#endif //TEST_MAP_H