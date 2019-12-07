#ifndef DATASERVER_H
#define DATASERVER_H

#include <iostream>
#include "DataCenter.h"
#include "Map.h"
#include "Set.h"

using namespace std;

template<class DC>
class CompareDataCenterByLinux : public Compare<DC>{
public:
    bool operator()(const DC& a, const DC& b) const;
};

template<class DC>
class CompareDataCenterByWindows: public Compare<DC>{
public:
    bool operator()(const DC& a, const DC& b) const;
};


class DataServer{
    Map<DataCenterID, DataCenter*> data_centers;
    CompareDataCenterByLinux<DataCenter*>* cmp_linux;
    CompareDataCenterByWindows<DataCenter*>* cmp_win;
    Set<DataCenter*> data_center_by_linux;
    Set<DataCenter*> data_center_by_windows;

public:
    DataServer();
    ~DataServer();
    DataServer(const DataServer&)=delete;
    DataServer& operator=(const DataServer&)=delete;
    void AddDataCenter(DataCenterID dc_id, int numOfServers);
    void RemoveDataCenter(DataCenterID dc_id);
    ServerID RequestServer(DataCenterID dc_id, ServerID server_id, OS os);
    void FreeServer(DataCenterID dc_id, ServerID server_id);
    ServerID* GetDataCentersByOS(OS os, int* numOfServers);
    unsigned int get_num_of_servers(DataCenterID) const;
};


#endif //DATASERVER_H
