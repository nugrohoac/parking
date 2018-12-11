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
    int i = 9;

    cout << to_string(i) << endl;

    return 0;
}
