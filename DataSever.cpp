#include "DataServer.h"

DataServer::DataServer() :
        DataCenterLinuxTree(
        Set<DataCenter*>(CompareDataCenterByLinux<DataCenter*>())),
        DataCenterWindowsTree(
        Set<DataCenter*>(CompareDataCenterByWindows<DataCenter*>())
                ){}

void DataServer::AddDataCenter(int dataCenterID, int numOfServers) {
    DataCenter dc=DataCenter(dataCenterID, numOfServers);
    auto it = DataCenterTree.insert(dataCenterID, dc);
    DataCenter p  = *it;
    DataCenterWindowsTree.insert(&p);
    DataCenterLinuxTree.insert(&p);
}

void DataServer::RemoveDataCenter(int dataCenterID) {
    DataCenter dc = DataCenterTree.at(dataCenterID);
    DataCenterWindowsTree.erase(&dc);
    DataCenterLinuxTree.erase(&dc);
    DataCenterTree.erase(dataCenterID);
}

ServerID DataServer::RequestServer(int dataCenterID, int serverID, int os) {
    DataCenter dc = DataCenterTree.at(dataCenterID);
    DataCenterWindowsTree.erase(&dc);
    DataCenterLinuxTree.erase(&dc);
    OS requested_os = os==0 ? Linux : Windows;
    ServerID s = dc.AllocateServer(serverID, requested_os);
    DataCenterWindowsTree.insert(&dc);
    DataCenterLinuxTree.insert(&dc);
    return s;
}

void DataServer::FreeServer(int dataCenterID, int serverID) {
    DataCenter dc = DataCenterTree.at(dataCenterID);
    DataCenterWindowsTree.erase(&dc);
    DataCenterLinuxTree.erase(&dc);
    dc.ReturnServer(serverID);
    DataCenterWindowsTree.insert(&dc);
    DataCenterLinuxTree.insert(&dc);
}

Array<DataCenterID> DataServer::GetDataCentersByOS(int os) {
    auto& set = os==0? DataCenterLinuxTree : DataCenterWindowsTree;
    unsigned int size = DataCenterTree.size();
    Array<DataCenterID> array(size);
    int i=0;
    for(auto &dc : set)
        array[i++]=dc->get_ID();
    return array;
}

template<class K>
bool CompareDataCenterByLinux<K>::operator()(const K& a,const K& b) const {
    if(a->get_linux() == b->get_linux())
        return a->get_ID()<b->get_ID();
    return a->get_linux() < b->get_linux();
}

template<class K>
bool CompareDataCenterByWindows<K>::operator()(const K& a,const K& b) const {
    if(a->get_windows() == b->get_windows())
        return a->get_ID()<b->get_ID();
    return a->get_windows() < b->get_windows();
}
