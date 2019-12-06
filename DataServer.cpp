#include "DataServer.h"

DataServer::DataServer() :
        data_center_by_linux(
        Set<DataCenter*>(CompareDataCenterByLinux<DataCenter*>())),
        data_center_by_windows(
        Set<DataCenter*>(CompareDataCenterByWindows<DataCenter*>())
                ){}

void DataServer::AddDataCenter(DataCenterID dc_id, int numOfServers) {
    DataCenter dc=DataCenter(dc_id, numOfServers);
    auto it = data_centers.insert(dc_id, dc);
    DataCenter& p  = *it;
    data_center_by_windows.insert(&p);
    data_center_by_linux.insert(&p);
}

void DataServer::RemoveDataCenter(DataCenterID dc_id) {
    DataCenter& dc = data_centers.at(dc_id);
    data_center_by_windows.erase(&dc);
    data_center_by_linux.erase(&dc);
    data_centers.erase(dc_id);
}

ServerID DataServer::RequestServer(DataCenterID dc_id, ServerID server_id, OS os) {
    DataCenter& dc = data_centers.at(dc_id);
    data_center_by_windows.erase(&dc);
    data_center_by_linux.erase(&dc);
    ServerID s = dc.AllocateServer(server_id, os);
    data_center_by_windows.insert(&dc);
    data_center_by_linux.insert(&dc);
    return s;
}

void DataServer::FreeServer(DataCenterID dc_id, ServerID server_id) {
    DataCenter& dc = data_centers.at(dc_id);
    data_center_by_windows.erase(&dc);
    data_center_by_linux.erase(&dc);
    dc.ReturnServer(server_id);
    data_center_by_windows.insert(&dc);
    data_center_by_linux.insert(&dc);
}

Array<DataCenterID> DataServer::GetDataCentersByOS(OS os) {
    auto& set = os==Linux ? data_center_by_linux : data_center_by_windows;
    unsigned int size = data_centers.size();
    Array<DataCenterID> array(size);
    int i=0;
    for(auto &dc : set)
        array[i++]=dc->get_ID();
    return array;
}


unsigned int DataServer::get_num_of_servers(DataCenterID dc_id) const {
    const DataCenter& dc = data_centers.at(dc_id);
    return dc.get_linux()+dc.get_windows();
}


template<class DC>
bool CompareDataCenterByLinux<DC>::operator()(const DC& a, const DC& b) const {
    if(a->get_linux() == b->get_linux())
        return a->get_ID()<b->get_ID();
    return a->get_linux() < b->get_linux();
}

template<class DC>
bool CompareDataCenterByWindows<DC>::operator()(const DC& a, const DC& b) const {
    if(a->get_windows() == b->get_windows())
        return a->get_ID()<b->get_ID();
    return a->get_windows() < b->get_windows();
}
