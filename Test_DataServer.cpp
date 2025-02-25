#ifndef TEST_DATASERVER_H
#define TEST_DATASERVER_H
#include "Test_utility.h"
#include "DataServer.h"
using namespace std;

class TestDataServer : public DataServer{
public:
    bool linuxContains(DataCenterID dc_id){
        DataCenter* dc = data_centers.at(dc_id);
        return (data_center_by_linux.find(dc)!=data_center_by_linux.end());
    }
    bool windowsContains(DataCenterID dc_id){
        DataCenter* dc = data_centers.at(dc_id);
        return (data_center_by_windows.find(dc)!=data_center_by_linux.end());
    }
    string print_set(const Set<DataCenter*>& set){
        string result= "{";
        for(auto i : set){
            result+= to_string(i->get_linux());
            result+= ", ";
        }
        if(!set.empty()) {
            result.pop_back();
            result.pop_back();
        }
        result+= "}";
        return result;
    }
    void Test_linux_Balance(){
        data_center_by_linux.Test_Balance();
    }
};


void DataServer_Test(){
    TestDataServer ds;
    ds.AddDataCenter(123,5);
    ds.RequestServer(123, 3, Windows);
    ds.RequestServer(123, 3, Linux);
    ds.RequestServer(123, 0, Windows);
    ds.FreeServer(123, 1);
    ds.FreeServer(123,3);
    //ds.FreeServer(123, 3);
    ds.AddDataCenter(456, 2);
    ds.RequestServer(456, 0, Windows);
    int numOfServers=5;
    int* array= (int*)ds.GetDataCentersByOS(Windows, &numOfServers);
    for(int i=0; i<numOfServers;++i)
        cout << array[i] << endl;
    delete[] array;

    ds.AddDataCenter(789,10);
    array= (int*) ds.GetDataCentersByOS(Linux, &numOfServers);
    for(int i=0; i<numOfServers;++i)
        cout << array[i] << endl;
    delete[] array;
    ds.RemoveDataCenter(123);
    //ds.RequestServer(123, 3, Windows);
    //ds.AddDataCenter(123, -5);

}

void DataServer_Test_1(){
    TestDataServer ds;
    ds.Test_linux_Balance();
    ds.AddDataCenter(3, 51);
    ds.Test_linux_Balance();
    ds.AddDataCenter(5, 299);
    ds.AddDataCenter(7, 20);
    ds.RemoveDataCenter(7);
    ds.Test_linux_Balance();
    ds.AddDataCenter(9, 93);
    ds.RemoveDataCenter(5);
    ds.AddDataCenter(1, 277);
    ds.RequestServer(1, 25, Windows);
    ds.AddDataCenter(23, 294);
    ds.AddDataCenter(4, 183);
    ds.RemoveDataCenter(4);
    ds.Test_linux_Balance();
    ds.AddDataCenter(15, 142);
    ds.AddDataCenter(17, 129);
    ds.AddDataCenter(28, 164);
    ds.RequestServer(28, 74, Linux);
    ds.AddDataCenter(4, 73);
    ds.AddDataCenter(26, 131);
    ds.RequestServer(15, 58, Linux);
    ds.AddDataCenter(11, 59);
    ds.RemoveDataCenter(4);
    ds.RemoveDataCenter(9);
    ds.AddDataCenter(16, 290);
    ds.RequestServer(16, 201, Linux);
    ds.RemoveDataCenter(26);
    ds.AddDataCenter(24, 194);
    ds.RemoveDataCenter(15);
    //cout<<ds.print_set(ds.data_center_by_linux)<<endl;
    //cout<<ds.print_set(ds.data_center_by_windows)<<endl;
    ds.RequestServer(23, 69, Linux);
    //cout<<ds.print_set(ds.data_center_by_linux)<<endl;
    //cout<<ds.print_set(ds.data_center_by_windows)<<endl;
    ds.AddDataCenter(26, 185);
    ds.RequestServer(1, 210, Windows);
    ds.RemoveDataCenter(1);
    ds.AddDataCenter(15, 121);
    ds.RemoveDataCenter(11);
    ds.AddDataCenter(11, 4);
    ds.AddDataCenter(19, 48);
    ds.AddDataCenter(22, 313);
    ds.Test_linux_Balance();
    //cout<<ds.linuxContains(24);
    //cout<<ds.windowsContains(24)<<endl;
    ds.RemoveDataCenter(24);
    ds.AddDataCenter(25, 126);
    ds.RemoveDataCenter(19);
    ds.AddDataCenter(24, 10);
    ds.RemoveDataCenter(11);
    ds.AddDataCenter(8, 22);
    ds.AddDataCenter(27, 233);
    ds.AddDataCenter(18, 194);
    ds.RequestServer(22, 271, Windows);
    ds.AddDataCenter(1, 319);
    ds.AddDataCenter(7, 70);
    ds.RemoveDataCenter(1);
    ds.RemoveDataCenter(28);
    ds.AddDataCenter(5, 106);
    ds.RequestServer(25, 96, Linux);
    ds.AddDataCenter(19, 108);
    ds.RemoveDataCenter(7);
    ds.AddDataCenter(20, 84);
    ds.RemoveDataCenter(5);
    ds.AddDataCenter(1, 91);
    ds.RemoveDataCenter(25);
    ds.AddDataCenter(10, 312);
    ds.AddDataCenter(12, 55);
    ds.RequestServer(18, 101, Windows);
    ds.AddDataCenter(30, 304);
    ds.AddDataCenter(13, 231);
    ds.RequestServer(30, 280, Windows);
    ds.RemoveDataCenter(20);
    ds.AddDataCenter(6, 83);
    ds.RemoveDataCenter(18);
    ds.RemoveDataCenter(22);
    ds.AddDataCenter(5, 240);
    ds.RemoveDataCenter(17);
    ds.RemoveDataCenter(8);
    ds.AddDataCenter(20, 48);
    ds.RemoveDataCenter(16);
    ds.RemoveDataCenter(24);
    ds.RemoveDataCenter(10);
    ds.RemoveDataCenter(20);
    ds.RemoveDataCenter(15);
    ds.AddDataCenter(7, 148);
    ds.RequestServer(23, 265, Windows);
    ds.AddDataCenter(15, 35);
    ds.RemoveDataCenter(26);
    ds.AddDataCenter(16, 231);
    ds.AddDataCenter(4, 84);
    ds.RemoveDataCenter(3);
    ds.AddDataCenter(8, 140);
    ds.RequestServer(27, 63, Linux);
    ds.AddDataCenter(14, 35);
    ds.AddDataCenter(28, 190);
    ds.AddDataCenter(2, 50);
    ds.AddDataCenter(3, 22);
    ds.RemoveDataCenter(19);
    ds.RemoveDataCenter(5);
    ds.RequestServer(30, 47, Windows);
    ds.RequestServer(1, 13, Linux);
    ds.RemoveDataCenter(13);
    ds.AddDataCenter(5, 225);
    ds.RemoveDataCenter(4);
    ds.AddDataCenter(10, 29);
    ds.RemoveDataCenter(28);
    ds.AddDataCenter(4, 12);
    ds.AddDataCenter(13, 115);
    ds.RemoveDataCenter(7);
    ds.AddDataCenter(29, 168);
    ds.RequestServer(6, 78, Linux);
    ds.RemoveDataCenter(13);
    ds.RemoveDataCenter(23);
    ds.RemoveDataCenter(27);
    ds.RequestServer(29, 58, Linux);
    ds.AddDataCenter(24, 6);
    ds.AddDataCenter(27, 19);
    ds.RemoveDataCenter(12);
    ds.AddDataCenter(13, 289);
    ds.AddDataCenter(20, 273);
    ds.RemoveDataCenter(16);
    ds.RemoveDataCenter(2);
    ds.RemoveDataCenter(27);
    ds.AddDataCenter(25, 176);
    ds.RequestServer(30, 221, Windows);
    ds.RemoveDataCenter(6);
    ds.RequestServer(1, 32, Windows);
    ds.RemoveDataCenter(8);
    ds.RemoveDataCenter(4);
    ds.AddDataCenter(18, 8);
    ds.AddDataCenter(16, 66);
    ds.AddDataCenter(17, 229);
    ds.AddDataCenter(12, 191);
    ds.RemoveDataCenter(14);
    ds.AddDataCenter(6, 184);
    ds.RemoveDataCenter(18);
    ds.AddDataCenter(7, 71);
    ds.RemoveDataCenter(17);
    ds.RemoveDataCenter(24);
    ds.AddDataCenter(9, 64);
    ds.RemoveDataCenter(10);
    ds.AddDataCenter(22, 69);
    ds.AddDataCenter(17, 253);
    ds.RemoveDataCenter(30);
    ds.RequestServer(7, 63, Linux);
    ds.RemoveDataCenter(22);
    ds.RemoveDataCenter(5);
    ds.RemoveDataCenter(13);
    ds.RequestServer(17, 161, Linux);
    ds.AddDataCenter(21, 13);
    ds.AddDataCenter(22, 297);
    ds.AddDataCenter(27, 113);
    ds.RemoveDataCenter(27);
    ds.AddDataCenter(26, 69);
    ds.RemoveDataCenter(25);
    ds.RemoveDataCenter(7);
    ds.AddDataCenter(25, 250);
    ds.AddDataCenter(2, 304);
    ds.RemoveDataCenter(29);
    ds.RemoveDataCenter(1);
    ds.RequestServer(25, 113, Linux);
    ds.RemoveDataCenter(16);
    ds.RemoveDataCenter(26);
    ds.AddDataCenter(4, 179);
    ds.AddDataCenter(7, 187);
    ds.RequestServer(22, 235, Linux);
    ds.AddDataCenter(14, 255);
    ds.AddDataCenter(30, 39);
    ds.AddDataCenter(8, 61);
    ds.RemoveDataCenter(15);
    ds.RemoveDataCenter(21);
    ds.AddDataCenter(11, 146);
    ds.RemoveDataCenter(12);
    ds.RemoveDataCenter(17);
    ds.AddDataCenter(27, 48);
    ds.AddDataCenter(29, 36);
    ds.AddDataCenter(24, 274);
    ds.RequestServer(2, 228, Linux);
    ds.AddDataCenter(17, 50);
    ds.RequestServer(11, 13, Linux);
    ds.RemoveDataCenter(17);
    ds.RemoveDataCenter(24);
    ds.RequestServer(2, 258, Windows);
    ds.AddDataCenter(21, 216);
    ds.AddDataCenter(24, 280);
    ds.AddDataCenter(13, 303);
    ds.AddDataCenter(5, 312);
    ds.RemoveDataCenter(4);
    ds.RequestServer(13, 103, Windows);
    ds.RemoveDataCenter(6);
    ds.AddDataCenter(28, 128);
    ds.RequestServer(13, 79, Windows);
    ds.AddDataCenter(17, 296);
    ds.RequestServer(5, 97, Linux);
    ds.RemoveDataCenter(9);
    ds.AddDataCenter(23, 97);
    ds.RemoveDataCenter(17);
    ds.RemoveDataCenter(28);
    ds.RequestServer(24, 203, Windows);
    ds.RemoveDataCenter(23);
    ds.RequestServer(7, 13, Linux);
    ds.RequestServer(14, 92, Windows);
    ds.AddDataCenter(10, 50);
    ds.RequestServer(21, 183, Linux);
    ds.AddDataCenter(15, 197);
    ds.RemoveDataCenter(22);
    ds.RemoveDataCenter(15);
    ds.AddDataCenter(18, 194);
    ds.RemoveDataCenter(3);
    ds.RemoveDataCenter(8);
    ds.RemoveDataCenter(10);
    ds.AddDataCenter(28, 193);
    ds.RemoveDataCenter(11);
    ds.RemoveDataCenter(27);
    ds.RemoveDataCenter(30);
    ds.RemoveDataCenter(21);
    ds.RequestServer(18, 35, Windows);
    ds.AddDataCenter(27, 316);
    ds.RemoveDataCenter(27);
    ds.RemoveDataCenter(29);
    ds.AddDataCenter(11, 5);
    ds.RemoveDataCenter(5);
    ds.RemoveDataCenter(7);
    ds.AddDataCenter(30, 30);
    ds.AddDataCenter(16, 302);
    ds.RemoveDataCenter(30);
    ds.AddDataCenter(12, 121);
    ds.RemoveDataCenter(12);
    ds.AddDataCenter(27, 301);
    ds.AddDataCenter(10, 5);
    ds.RemoveDataCenter(13);
    ds.AddDataCenter(9, 67);
    ds.RemoveDataCenter(24);
    ds.AddDataCenter(30, 64);
    ds.RequestServer(27, 19, Linux);
    ds.RequestServer(16, 215, Windows);
    ds.AddDataCenter(8, 80);
    ds.RemoveDataCenter(25);
    ds.AddDataCenter(4, 99);
    ds.RemoveDataCenter(16);
    ds.AddDataCenter(16, 103);
    ds.RequestServer(14, 126, Windows);
    ds.RequestServer(2, 188, Linux);
    ds.RequestServer(4, 94, Linux);
    ds.AddDataCenter(22, 249);
    ds.RemoveDataCenter(11);
    ds.AddDataCenter(11, 7);
    ds.RequestServer(14, 162, Windows);
    ds.RemoveDataCenter(11);
    ds.AddDataCenter(17, 198);
    ds.RemoveDataCenter(10);
}

#endif //TEST_DATASERVER_H