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
