#pragma once
#include <string>
using namespace std;

class OrderItem {
public:
    string name;
    float price;
    int quantity;
    string customerName;

    OrderItem(string n = "", float p = 0, int q = 0, string cname = "");
};
