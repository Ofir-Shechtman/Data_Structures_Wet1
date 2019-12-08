#include "DataServer.h"

DataServer::DataServer() :
        cmp_linux(new CompareDataCenterByLinux<DataCenter*>()),
        cmp_win(new CompareDataCenterByWindows<DataCenter*>()),
        data_center_by_linux(Set<DataCenter*>(cmp_linux)),
        data_center_by_windows(Set<DataCenter*>(cmp_win)
                ){}

void DataServer::AddDataCenter(DataCenterID dc_id, int numOfServers) {
    auto* dc= new DataCenter(dc_id, numOfServers);
    data_centers.insert(dc_id, dc);
    data_center_by_windows.insert(dc);
    data_center_by_linux.insert(dc);
}

void DataServer::RemoveDataCenter(DataCenterID dc_id) {
    DataCenter* dc = data_centers.at(dc_id);
    data_center_by_windows.erase(dc);
    data_center_by_linux.erase(dc);
    data_centers.erase(dc_id);
    delete dc;
}

ServerID DataServer::RequestServer(DataCenterID dc_id, ServerID server_id, OS os) {
    DataCenter* dc = data_centers.at(dc_id);
    data_center_by_windows.erase(dc);
    data_center_by_linux.erase(dc);
    ServerID s;
    try {
        s = dc->AllocateServer(server_id, os);
    }
    catch (std::bad_alloc& e){
        data_center_by_windows.insert(dc);
        data_center_by_linux.insert(dc);
        throw e;
    }
    catch (std::exception& e){
        data_center_by_windows.insert(dc);
        data_center_by_linux.insert(dc);
        throw e;
    }
    data_center_by_windows.insert(dc);
    data_center_by_linux.insert(dc);
    return s;
}

void DataServer::FreeServer(DataCenterID dc_id, ServerID server_id) {
    DataCenter* dc = data_centers.at(dc_id);
    data_center_by_windows.erase(dc);
    data_center_by_linux.erase(dc);
    try {
        dc->ReturnServer(server_id);
    }
    catch (std::bad_alloc& e){
        data_center_by_windows.insert(dc);
        data_center_by_linux.insert(dc);
        throw e;
    }
    catch (std::exception& e){
        data_center_by_windows.insert(dc);
        data_center_by_linux.insert(dc);
        throw e;
    }
    data_center_by_windows.insert(dc);
    data_center_by_linux.insert(dc);
}

ServerID* DataServer::GetDataCentersByOS(OS os, int* numOfServers) {
    auto& set = os==Linux ? data_center_by_linux : data_center_by_windows;
    if(set.size()==0)
        throw std::exception();
    *numOfServers = (int) set.size();
    auto array = new ServerID[*numOfServers];
    int i=0;
    for(auto &dc : set)
        array[i++] = dc->get_ID();
    return array;
}


unsigned int DataServer::get_num_of_servers(DataCenterID dc_id) const {
    const DataCenter* dc = data_centers.at(dc_id);
    return dc->get_linux()+dc->get_windows();
}

DataServer::~DataServer() {
    for(auto &i : data_centers)
        delete i;
    delete cmp_linux;
    delete cmp_win;
}

template<class DC>
bool CompareDataCenterByLinux<DC>::operator()(const DC& a, const DC& b) const {
    if(a->get_linux() == b->get_linux())
        return a->get_ID()<b->get_ID();
    return a->get_linux() > b->get_linux();
}

template<class DC>
bool CompareDataCenterByWindows<DC>::operator()(const DC& a, const DC& b) const {
    if(a->get_windows() == b->get_windows())
        return a->get_ID()<b->get_ID();
    return a->get_windows() > b->get_windows();
}

