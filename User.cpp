#include "User.h"
#include <iostream>
using namespace std;

User::User(string user, string pass) {
    username = user;
    password = pass;
}

bool User::authenticate() {
    string u, p;
    cout << "Enter admin username: ";
    cin >> u;
    cout << "Enter password: ";
    cin >> p;
    return (u == username && p == password);
}
