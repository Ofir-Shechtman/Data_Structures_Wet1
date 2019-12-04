#include "Test_utility.h"
#include "DataCenter.h"
using namespace std;



string print_queue(const List<ServerID>& list){
    string result= "{";
    for(ServerID id : list){
        result+= to_string(id);
        result+= ", ";
    }
    if(!list.empty()) {
        result.pop_back();
        result.pop_back();
    }
    result+= "}";
    return result;
}


class TestDataServer : public DataCenter{
public:
    TestDataServer(DataCenterID dc_id, unsigned int num_of_servers):DataCenter(dc_id, num_of_servers){};
    string print_servers() const;//{return print_array(servers);}
    string print_windows_queue() const{return print_queue(windows_queue);};
    string print_linux_queue() const{return print_queue(linux_queue);};
    string print() const{
        string result= "ID:"+to_string(dc_id)+", Servers:"+to_string(servers.size)+", WinCount:"+to_string(windows_counter);
        result += ", "+print_servers();
        result += ", Win"+print_windows_queue();
        result += ", Lin"+print_linux_queue();
        return result;

    }
};

string TestDataServer::print_servers() const {
    string result= "Servers[";
    for(int i=0;i<servers.size;++i){
        const Server& s= servers[i];
        string state = s.state==Occupied ? "Oc" : "Av";
        string os = s.os==Linux ? "Lin" : "Win";
        result+= "("+to_string(s.id)+", "+os+", "+state+")";
        result+= ", ";
    }
    if(servers.size>0) {
        result.pop_back();
        result.pop_back();
    }
    result+= "]";
    return result;
}





//template <class T>
ostream& operator<<(ostream& os, const TestDataServer& data){
    return os << data.print() << endl;
}


void DataServer_Test(){
    TestDataServer dc(123, 5);
    cout<<dc<<endl;
    dc.AllocateServer(1, Windows);
    cout<<dc<<endl;
    dc.AllocateServer(1, Linux);
    cout<<dc<<endl;
    dc.AllocateServer(0, Windows);
    cout<<dc<<endl;
    dc.ReturnServer(2);
    cout<<dc<<endl;
    dc.ReturnServer(1);
    cout<<dc<<endl;
    dc.ReturnServer(0);
    cout<<dc<<endl;
    total();
}

