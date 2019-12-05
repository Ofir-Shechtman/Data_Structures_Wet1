#ifndef DATA_STRUCTURES_WET1_DATASERVER_H
#define DATA_STRUCTURES_WET1_DATASERVER_H

#include <iostream>
#include "DataCenter.h"
#include "Map.h"
#include "Set.h"

using namespace std;

template<class K>
class CompareDataCenterByLinux : public Compare<K>{
public:
    bool operator()(K a,K b);
};

template<class K>
class CompareDataCenterByWindows: public Compare<K>{
public:
    bool operator()(K a,K b);
};


class DataServer{
    Map<DataCenterID, DataCenter> DataCenterTree;
    Set<const DataCenter*> DataCenterWindowsTree;
    Set<const DataCenter*> DataCenterLinuxTree;
public:
    DataServer();
    ~DataServer() = default;
    void AddDataCenter(int dataCenterID, int numOfServers);
    void RemoveDataCenter(int dataCenterID);
    ServerID RequestServer(int dataCenterID, int serverID, int os);
    void FreeServer(int dataCenterID, int serverID);
    Array<DataCenterID> GetDataCentersByOS(int os);
};


#endif //DATA_STRUCTURES_WET1_DATASERVER_H
