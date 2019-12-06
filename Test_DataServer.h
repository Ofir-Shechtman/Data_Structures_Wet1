#ifndef TEST_DATASERVER_H
#define TEST_DATASERVER_H
#include "Test_utility.h"
#include "DataServer.h"
using namespace std;


void DataServer_Test(){
    DataServer ds;
    ds.AddDataCenter(123,5);
    ds.RequestServer(123, 3, Windows);
    ds.RequestServer(123, 3, Linux);
    ds.RequestServer(123, 0, Windows);

}

#endif //TEST_DATASERVER_H