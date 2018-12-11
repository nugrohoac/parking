#include <iostream>
#include <fstream>
#include "library/cJSON/cJSON.c"
#include "library/cJSON/cJSON.h"
#include "library/json.hpp"
#include <time.h>
#include <string>
#include <math.h>

using namespace std;
using json = nlohmann::json;

int main(){

    json jsonfile, j, k, l, zz;

//    string a = "testing1";
//    string b = "testing2";
//    string c = "testing3";

//    j["object"] = { {"currency", "USD"}, {"value", 42.99} };
//    k["object"] = { {"currency", "USD"}, {"value", 42.99} };
//    l["object"] = { {"currency", "USD"}, {"value", 42.99} };

    json j_list_of_pairs = json::object({ {"one", 1}, {"two", 2} });

    jsonfile["json_array"] = {{{"currency", "USD"}, {"value", 42.99}}, j_list_of_pairs};


    ofstream file("file/key.json");
    file << jsonfile;

//    ifstream ifs("park.json");
//    json j = json::parse(ifs);
//    //cout << j["lantai_1"];
//    json array_1 = j["lantai_1"];
//
//    for (auto it = array_1.begin(); it != array_1.end(); ++it)
//    {
//        cout << it.value() << endl;
//    }

//    time_t time_now = time(nullptr);
//    cout << time_now << endl;
//
//    long waktu1 = 1286679600;
//    long waktu2 = 1286686860;
//
//    cout << ctime (&waktu1) << endl;
//    cout << ctime (&waktu2) << endl;
//    cout << ((waktu2 - waktu1) % 3600) / 60 << "menit" << endl;
//    double jam = ceil( ((double)waktu2 - (double)waktu1) / 3600);
//    cout << jam <<"jam" << endl;

//    json json_file;
//
//    json_file


    return 0;

}
