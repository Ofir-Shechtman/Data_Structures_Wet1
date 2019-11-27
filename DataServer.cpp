#include "DataServer.h"

DataServer::DataServer(DataServerID ds_id, int num_of_servers):
        ds_id(ds_id), num_of_servers(num_of_servers),
        servers(Array<DSTriple>(num_of_servers)){
    DSTriple default_triple = DSTriple(Linux, Free);
    for(int i=0; i<num_of_servers; ++i){
        auto server=linux_queue.push_back(i);
        servers[i]=DSTriple(Linux, Free, server);
    }
}

void DataServer::AllocateServer(ServerID id, OS os) {
    DSTriple requested_server = servers[id];


}
