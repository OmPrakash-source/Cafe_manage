#pragma once
#include <string>
using namespace std;

class User {
    string username;
    string password;

public:
    User(string user = "", string pass = "");
    bool authenticate();
};
