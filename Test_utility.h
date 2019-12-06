#ifndef TEST_UTILITY_H
#define TEST_UTILITY_H

#include <iostream>
#include <string>
using namespace std;


static int test_number=0;
static int total_passed=0;


string print(bool flag){
    return flag ? "True" : "False";
}

string print(int i){
    return to_string(i);
}

template <class T>
void test(const T& data, string output="True", unsigned int line=0){
    string result= "Test " + to_string(++test_number) + ": ";
    bool is_passed= print(data)==output;
    if(is_passed) ++total_passed;
    if(is_passed)
        result += "Passed";
    else {
        result += "Failed - expected to " + output + " got " + print(data);
        if(line)
            result += " at line " + to_string(line);
    }
    cout << result << endl;
}

void total(){
    string result= "Passed " + to_string(total_passed);
    result+="/" + to_string(test_number);
    cout << result << endl;
}


#endif //TEST_UTILITY_H