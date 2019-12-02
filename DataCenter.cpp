#include "DataCenter.h"

DataCenter::Server::Server(ServerID id, List<ServerID>::Iterator it):
    id(id), os(Linux), state(Available), iterator(it) {}

/*!
 * DataCenter Constructor
 * @param dc_id
 * @param num_of_servers
 * by default all servers are linux type
 * the server array values set with ids of 0 to num_of_servers-1,
 * and iterator by the iterator returns from the stack-push
 */
DataCenter::DataCenter(DataCenterID dc_id, unsigned int num_of_servers):
        dc_id(dc_id),
        servers(Array<Server>(num_of_servers)), windows_count(0){
    for(ServerID id=0; id<num_of_servers; ++id){
        auto server_it=linux_queue.push_back(id);
        servers[id]=Server(id, server_it);
    }
}

/*!
 * Allocating server by request
 * @param id - requested ServerID (if Available)
 * @param os - requested os
 * Allocate the requested ServerID if Available, if not allocate another by
 * the requested os queue. able to change os of the server.
 */
ServerID DataCenter::AllocateServer(ServerID id, OS os) {
    Server* server = &servers[id];
    auto* queue = os==Linux ? &linux_queue : &windows_queue;
    if(server->state==Occupied) {
        if(queue->empty()) {
            queue = os == Linux ? &windows_queue : &linux_queue;
            if (queue->empty())
                throw NoFreeServers();
        }
        server=&servers[queue->front()];
    }
    queue->erase(server->iterator);
    server->state=Occupied;
    server->iterator=List<ServerID>::Iterator();
    if(server->os!=os) {
        server->os = os;
        os == Linux ? --windows_count : ++windows_count;
    }
    return server->id;
}

/*!
 * Received server from client and set him to available to use again in the
 * data server. returns the server the the end of the queue.
 * @param id
 */
void DataCenter::ReceivedServer(ServerID id) {
    Server& server = servers[id];
    if(server.state!=Occupied)
        throw ServersNotOccupied();
    auto& queue = server.os==Linux ? linux_queue : windows_queue;
    server.iterator=queue.push_back(id);
    server.state=Available;
}
