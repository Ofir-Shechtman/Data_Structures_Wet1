#ifndef DATACENTER_H
#define DATACENTER_H

#include "Array.h"
#include "List.h"

enum OS {Linux, Windows};
enum State {Available, Occupied};

typedef unsigned int ServerID;
typedef unsigned int DataCenterID;

/*!
 * DataCenter class contains Array of all servers and 2 List that act like
 * queues of ServerID to manage the server queue for linux and windows.
 * the missing linux_count is just num_of_servers-windows_count
 */
class DataCenter {
protected://just for testing
    DataCenterID dc_id;
    struct Server;
    Array<Server> servers;
    List<ServerID> linux_queue;
    List<ServerID> windows_queue;
    unsigned int windows_counter;
public:
    DataCenter(DataCenterID dc_id, unsigned int num_of_servers);
    DataCenter(const DataCenter&);
    ~DataCenter()= default;
    ServerID AllocateServer(ServerID id, OS os);
    void ReturnServer(ServerID);
    unsigned int get_windows() const;
    unsigned int get_linux() const;
    unsigned int get_ID() const;

    class NoFreeServers : public std::exception{};
    class ServerNotOccupied : public std::exception{};
};

/*!
 * Struct that contains the Server info,
 * the iterator filed is iterator of the server in the relevant stack.
 */
struct DataCenter::Server{
    ServerID id;
    OS os;
    State state;
    List<ServerID>::Iterator iterator;
    explicit Server(ServerID=0, List<ServerID>::Iterator=List<ServerID>::Iterator());
};

#endif //DATACENTER_H
