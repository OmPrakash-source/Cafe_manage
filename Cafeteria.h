#pragma once
#include <vector>
#include <queue>
#include <stack>
#include "FoodItem.h"
#include "OrderItem.h"
#include "User.h"
using namespace std;

class Cafeteria {
    vector<FoodItem> menu;
    vector<OrderItem> orders;
    queue<OrderItem> orderQueue;
    stack<pair<int, string>> tableStack;
    User admin;

    int generateTableNumber();
    void loadMenuFromFile();
    void saveMenuToFile();

public:
    Cafeteria();
    float getPriceByName(const string &name);
    void displayMenu();
    void Additional();
    void addFoodItem();
    void editFoodItem();
    void deleteFoodItem();
    void placeOrder();
    void displayOrderSummary();
    void displayOrderQueue();
    void displayStack();
    void processOrder();
    void showTotal();
    void clearStack();
    void adminMenu();
    void mainMenu();
};
