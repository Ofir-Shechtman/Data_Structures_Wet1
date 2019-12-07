#include "library.h"
#include "DataServer.h"

void* Init(){
    try {
        DataServer *DS = new DataServer();
        return (void*)DS;
    }
    catch(std::exception&){
        return NULL;
    }
}

StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers) {
    if(numOfServers<=0 || DS==NULL || dataCenterID<=0)
        return INVALID_INPUT;
    try {
        ((DataServer*)DS)->AddDataCenter(dataCenterID, numOfServers);
        return SUCCESS;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
    catch (std::exception&) {
        return FAILURE;
    }
}

StatusType RemoveDataCenter(void *DS, int dataCenterID){
    if(DS==NULL || dataCenterID<=0)
        return INVALID_INPUT;
    try {
        ((DataServer*)DS)->RemoveDataCenter(dataCenterID);
        return SUCCESS;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
    catch (std::exception&) {
        return FAILURE;
    }
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID){
    if(DS==NULL || serverID<0 || assignedID==NULL || os>1 || dataCenterID<=0 || os<0)
        return INVALID_INPUT;
    try {
        unsigned int numOfServers= ((DataServer*)DS)->get_num_of_servers(dataCenterID);
        if(serverID>= (int)numOfServers)
            return INVALID_INPUT;
        OS requested_os= os==0 ? Linux : Windows;
        *assignedID=((DataServer*)DS)->RequestServer(dataCenterID, serverID, requested_os);
        return SUCCESS;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
    catch (std::exception&) {
        return FAILURE;
    }
}


StatusType FreeServer(void *DS, int dataCenterID, int serverID){
    if(DS==NULL || serverID<0 || dataCenterID<=0)
        return INVALID_INPUT;
    try {
        unsigned int numOfServers= ((DataServer*)DS)->get_num_of_servers(dataCenterID);
        if(serverID>= (int)numOfServers)
            return INVALID_INPUT;
        ((DataServer*)DS)->FreeServer(dataCenterID, serverID);
        return SUCCESS;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
    catch (std::exception&) {
        return FAILURE;
    }
}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters){
    if(DS==NULL || dataCenters==NULL || numOfDataCenters==NULL || os>1 || os<0)
        return INVALID_INPUT;
    try {
        OS requested_os= os==0 ? Linux : Windows;
        *dataCenters = (int*)((DataServer*)DS)->GetDataCentersByOS(requested_os, numOfDataCenters);
        return SUCCESS;
    }
    catch (std::bad_alloc&) {
        return ALLOCATION_ERROR;
    }
    catch (std::exception&) {
        return FAILURE;
    }
}

void Quit(void** DS){
    delete (DataServer*)*DS;
    *DS=NULL;
}