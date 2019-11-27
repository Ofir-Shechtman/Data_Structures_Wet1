#ifndef DATASERVER_H
#define DATASERVER_H

#include "Array.h"
#include "List.h"
#include "Triple.h"

enum OS {Linux, Windows};
enum State {Free, Occupied};

typedef unsigned int ServerID;
typedef unsigned int DataServerID;
typedef Triple<OS, State, List<ServerID>::Iterator> DSTriple;



class DataServer {
    Array<DSTriple> servers;
    List<ServerID> windows_queue;
    List<ServerID> linux_queue;
    DataServerID ds_id;
    int num_of_servers;
public:
    DataServer(DataServerID ds_id, int num_of_servers);
    ~DataServer()= default;
    void AllocateServer(ServerID id, OS os);
    void ReceivedServer(ServerID);
};


#endif //DATASERVER_H
