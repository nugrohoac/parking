#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "library/cJSON/cJSON.c"
#include "library/cJSON/cJSON.h"
#include "library/json.hpp"
#include <time.h>
#include <string>
#include <math.h>

using namespace std;
using json = nlohmann::json;

json available_floor, available_place;

int start(){
    int input_code;
    cout << "----------***-- SMART PARKING --***----------" << endl << endl;
    cout << "Input code :  1 for parkir in" << endl;
    cout << "Input code :  2 for parkir out" << endl;
    cout << "Input code : -1 for out SMART PARKING" << endl;

    cout << "Insert Input code : ";
    cin >> input_code;

    return input_code;
}

long generate_time(){
    time_t time_now = time(nullptr);
    return time_now;
}

double get_hours(long check_out, long check_in){
    double jam = ceil( ((double)check_out - (double)check_in) / 3600);
    return jam;
}

double get_hours_without_ceiling (long check_out, long check_in){
    double jam;
    if((check_out-check_in) < 3600){
        jam = 0;
    }else{
        jam = ((double)check_out - (double)check_in) / 3600;
    }
    return jam;
}

double get_minutes(long check_out, long check_in){
    double minutes = ((check_out - check_in) % 3600) / 60;
    return minutes;
}

bool parkir_in(int floor, int place, string code_parking, string police_no, long check_in_time, string status){
    //update place
    bool save_status = false;
    json save_place = json::object(
                                {
                                    {"code_parking", "f"+to_string(floor)+to_string(place)},
                                    {"police_no", police_no},
                                    {"check_in_time", check_in_time},
                                    {"status", status}

                                }
                            );

    ofstream file("database/floor_"+to_string(floor)+"/floor_"+to_string(floor)+"_"+to_string(place)+".json");
    file << save_place;

    if(file){
        save_status = true;
        cout << endl << "You parking start at : " << ctime (&check_in_time) << endl;
        cout << "Success Parking in SMART PARKING, thank you" << endl << endl;
    }

    return save_status;
}

bool parkir_out(int floor, int place, string code_parking, long check_out_time, string status){
    //read data
    long check_in_time;
    ifstream ifs("database/floor_"+to_string(floor)+"/floor_"+to_string(floor)+"_"+to_string(place)+".json");
    available_place = json::parse(ifs);
    bool save_status = false;

    if(available_place["code_parking"] == code_parking){
        check_in_time = available_place["check_in_time"];

        double hours_without_ceiling = get_hours_without_ceiling(check_out_time, check_in_time);
        double hours = get_hours(check_out_time, check_in_time);
        double minutes = get_minutes(check_out_time, check_in_time);

        cout << "You parking start at : " << ctime (&check_in_time) << endl;
        cout << "You parking end at : " << ctime (&check_out_time) << endl;
        cout << "You parking as long as " << hours_without_ceiling << " hours " << "and " << minutes << " minutes" << endl << endl;
        cout << "You must pay as long as " << hours << " hours" << endl << endl;
        cout << "Total pay is : Rp." << hours * 2000 << endl << endl;

        json save_place = json::object(
                                    {
                                        {"code_parking", code_parking},
                                        {"police_no", nullptr},
                                        {"check_in_time", nullptr},
                                        {"status", status}

                                    }
                                );

        ofstream file("database/floor_"+to_string(floor)+"/floor_"+to_string(floor)+"_"+to_string(place)+".json");
        file << save_place;

        if(file){
            save_status = true;
            cout << "Success Parking out SMART PARKING, thank you" << endl << endl;
        }
    }

    return save_status;
}

bool update_floor(int floor, string status){
    //update floor
    bool update = false;
    json save_floor = json::object(
                        {
                            {"name", "floor_"+to_string(floor)},
                            {"status", status}

                        }
                    );
    ofstream file("database/floor_"+to_string(floor)+".json");
    file << save_floor;

    if(file){
        update = true;
    }

    return update;
}

pair<bool, int> check_floor(){
    bool result = false;
    int floor = 0;
    for(int i = 1; i<=3 ; i++){
        ifstream ifs("database/floor_"+to_string(i)+".json");
        available_floor = json::parse(ifs);
        if(available_floor["status"] == "available"){
            result = true;
            floor = i;
            break;
        }
    }

    return make_pair(result, floor);
}

pair<string, int> check_place(int floor){
    int place = 0;
    int counter = 0;
    string code_parking = "full";
    for(int i=1; i<=3 ; i++){
        ifstream ifs("database/floor_"+to_string(floor)+"/floor_"+to_string(floor)+"_"+to_string(i)+".json");
        available_place = json::parse(ifs);
        if(available_place["status"] == "available"){
            place = i;
            code_parking = available_place["code_parking"];
            break;
        }
    }

    return make_pair(code_parking, place);
}

int main(){
    int start_system = start();
    string police_no;
    long check_in_time;
    long check_out_time;

    try{

        while(start_system != -1){
            if(start_system == 1){
                //int in = parkir_in();
                cout << endl << endl;
                pair<bool, int> result = check_floor();

                if(result.first){
                    int curren_floor = result.second;
                    pair<string, int> curren_place = check_place(curren_floor);
                    string curren_code_parking = curren_place.first;

                    cout << "Parkir available at floor : " << curren_floor << " and at place : " << curren_place.second << endl;
                    cout << "Your code parking is : " << curren_code_parking << endl;

                    cout << "Input Police No : " ;
                    cin >> police_no;
                    check_in_time = generate_time();

                    bool status_parkir_in = parkir_in(curren_floor, curren_place.second, curren_code_parking, police_no, check_in_time, "unAvailable");

                    if(status_parkir_in){
                        pair<string, int> is_full_place = check_place(curren_floor);

                        if(is_full_place.first == "full"){
                            update_floor(curren_floor, "unAvailable");

                            cout << "Floor : " << curren_floor << " is full" << endl << endl;
                        }
                    }

                }else{
                    cout << "------------- SORRY Parking is full on all floor on all floor, Thank You -------------" << endl;
                }

                start_system = start();

            }else if(start_system == 2){
                string code_parking;
                cout << "Plase insert code parking : " ;
                cin >> code_parking;

                int floor = (int)code_parking[1] - '0';// << "  " << code_parking[2];
                int place = (int)code_parking[2] - '0';
                string status = "available";

                long check_out_time_now = generate_time();
                bool status_parkir_out = parkir_out(floor, place, code_parking, check_out_time_now, status);

                if(status_parkir_out){
                    update_floor(floor, status);
                }

                cout << endl << endl;
                start_system = start();

            }else{
                cout << "\033[2J\033[1;1H";
                cout << endl << endl;
                cout << "INPUT CODE IS WROOOOONG, Plese Input Again...!!!" << endl << endl;
                start_system = start();
            }
        }

        cout << endl << endl << "THANK YOU have use SMART PARKING, see you next time" << endl << endl;

    }catch(exception e){
        throw e;
    }

    return 0;
}
