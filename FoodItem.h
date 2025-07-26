#pragma once
#include <string>
using namespace std;

class FoodItem {
public:
    string name;
    float price;
    int quantity;

    FoodItem(string n = "", float p = 0, int q = 0);
};
