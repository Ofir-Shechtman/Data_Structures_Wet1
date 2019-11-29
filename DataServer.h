#ifndef DATASERVER_H
#define DATASERVER_H

#include "Array.h"
#include "List.h"
#include "Triple.h"

enum OS {Linux, Windows};
enum State {Free, Occupied};

typedef unsigned int ServerID;
typedef unsigned int DataServerID;

struct Server{
    ServerID id;
    OS os;
    State state;
    List<ServerID>::Iterator iterator;
    explicit Server(ServerID=0, List<ServerID>::Iterator=List<ServerID>::Iterator());
};

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
