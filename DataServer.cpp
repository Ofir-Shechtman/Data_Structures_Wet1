#include "DataServer.h"

Server::Server(ServerID id, List<ServerID>::Iterator it):
    id(id), os(Linux), state(Free), iterator(it) {}

DataServer::DataServer(DataServerID ds_id, unsigned int num_of_servers):
        ds_id(ds_id), num_of_servers(num_of_servers),
        servers(Array<Server>(num_of_servers)), windows_count(0){
    for(ServerID id=0; id<num_of_servers; ++id){
        auto server_it=linux_queue.push_back(id);
        servers[id]=Server(id, server_it);
    }
}

void DataServer::AllocateServer(ServerID id, OS os) {
    Server& server = servers[id];
    auto& queue = os==Linux ? linux_queue : windows_queue;
    if(server.state==Occupied) {
        if(queue.empty()) {
            queue = os == Linux ? windows_queue : linux_queue;
            if (queue.empty())
                throw NoFreeServers();
        }
        server=servers[queue.front()];
    }
    queue.erase(server.iterator);
    server.state=Occupied;
    server.iterator=List<ServerID>::Iterator();
    if(server.os!=os) {
        server.os = os;
        os == Linux ? --windows_count : ++windows_count;
    }
}

void DataServer::ReceivedServer(ServerID id) {
    Server& server = servers[id];
    auto& queue = server.os==Linux ? linux_queue : windows_queue;
    server.iterator=queue.push_back(id);
    server.state=Free;
}


