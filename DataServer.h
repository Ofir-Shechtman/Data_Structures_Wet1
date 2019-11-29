#ifndef DATASERVER_H
#define DATASERVER_H

#include "Array.h"
#include "List.h"

enum OS {Linux, Windows};
enum State {Available, Occupied};

typedef unsigned int ServerID;
typedef unsigned int DataServerID;

/*!
 * Struct that contains the Server info,
 * the iterator filed is iterator of the server in the relevant stack.
 */
struct Server{
    ServerID id;
    OS os;
    State state;
    List<ServerID>::Iterator iterator;
    explicit Server(ServerID=0, List<ServerID>::Iterator=List<ServerID>::Iterator());
};

/*!
 * DataServer class contains Array of all servers and 2 List that act like
 * queues of ServerID to manage the server queue for linux and windows.
 * the missing linux_count is just num_of_servers-windows_count
 */
class DataServer {
    Array<Server> servers;
    List<ServerID> windows_queue;
    List<ServerID> linux_queue;
    DataServerID ds_id;
    unsigned int num_of_servers;
    unsigned int windows_count;
public:
    DataServer(DataServerID ds_id, unsigned int num_of_servers);
    ~DataServer()= default;
    void AllocateServer(ServerID id, OS os);
    void ReceivedServer(ServerID);
    class NoFreeServers : public std::exception{};
};


#endif //DATASERVER_H
