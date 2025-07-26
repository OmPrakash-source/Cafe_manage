#include "Cafeteria.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

Cafeteria::Cafeteria() : admin("om", "123") {
    srand(time(0));
    loadMenuFromFile();
}

int Cafeteria::generateTableNumber() {
    return rand() % 10 + 1;
}

void Cafeteria::loadMenuFromFile() {
    menu.clear();
    ifstream file("menu.txt");
    if (!file) {
        cout << "Menu file not found. Starting with empty menu.\n";
        return;
    }
    string name;
    float price;
    int quantity;
    while (file >> name >> price >> quantity) {
        menu.emplace_back(name, price, quantity);
    }
    file.close();
}

void Cafeteria::saveMenuToFile() {
    ofstream file("menu.txt");
    for (auto &item : menu) {
        file << item.name << " " << item.price << " " << item.quantity << endl;
    }
    file.close();
}

void Cafeteria::displayMenu() {
    if (menu.empty()) {
        cout << "No items in menu.\n";
        return;
    }
    cout << "| No | Name                | Price | Quantity |\n";
    int i = 1;
    for (auto &item : menu) {
        cout << "| " << setw(2) << i++ << " | " << setw(20) << item.name << " | "
             << setw(6) << fixed << setprecision(2) << item.price << " | "
             << setw(8) << item.quantity << " |\n";
    }
}

void Cafeteria::addFoodItem() {
    string name; float price; int quantity;
    cout << "Enter name: "; cin >> name;
    cout << "Enter price: "; cin >> price;
    cout << "Enter quantity: "; cin >> quantity;
    menu.emplace_back(name, price, quantity);
    return;
}

void Cafeteria::editFoodItem() {
    string name;
    cout << "Enter item name to edit: "; cin >> name;
    for (auto &item : menu) {
        if (item.name == name) {
            cout << "New name: "; cin >> item.name;
            cout << "New quantity: "; cin >> item.quantity;
            return;
        }
    }
    cout << "Item not found.\n";
}

void Cafeteria::deleteFoodItem() {
    string name;
    cout << "Enter name to delete: "; cin >> name;
    auto it = remove_if(menu.begin(), menu.end(), [&](FoodItem &f) { return f.name == name; });
    if (it != menu.end()) {
        menu.erase(it, menu.end());
        cout << "Deleted.\n";
    } else cout << "Not found.\n";
}

float Cafeteria::getPriceByName(const string &name) {
    for (auto &item : menu) {
        if (item.name == name) return item.price;
        
    }
    return 0;
}

void Cafeteria::placeOrder() {
    string cname, iname;
    int qty;
    char again;

    cout << "Enter your name: ";
    cin >> cname;

    do {
        cout << "Enter item name (or 'exit' to cancel): ";
        cin >> iname;
        if (iname == "exit") return;

        cout << "Quantity: ";
        cin >> qty;

        bool found = false;
        for (auto &item : menu) {
            if (item.name == iname && item.quantity >= qty) {
                orders.emplace_back(iname, item.price, qty, cname);
                orderQueue.emplace(iname, item.price, qty, cname);
                tableStack.push({generateTableNumber(), cname});
                item.quantity -= qty;
                cout << "Order placed!\n";
                return;  // Exit after successful order
            }
        }

        // If we reach here, order was invalid
        cout << "Item not found or insufficient stock.\n";

        // Ask only after a failed attempt
        cout << "Do you want to try again? (y/n): ";
        cin >> again;

        if (again != 'y' && again != 'Y') break;

    } while (true);
}


void Cafeteria::displayOrderSummary() {
    for (auto &o : orders) {
        cout << o.customerName << " ordered " << o.name << " x" << o.quantity << " - $" << o.price << endl;
    }
}

void Cafeteria::showTotal() {
    float total = 0;
    for (auto &o : orders) total += o.price * o.quantity;
    cout << "Total Sales: $" << total << endl;
}

void Cafeteria::displayOrderQueue() {
    queue<OrderItem> temp = orderQueue;
    int sn = 1;
    while (!temp.empty()) {
        auto o = temp.front(); temp.pop();
        cout << sn++ << ". " << o.customerName << " - " << o.name << " x" << o.quantity << endl;
    }
}

void Cafeteria::processOrder() {
    if (!orderQueue.empty()) {
        auto o = orderQueue.front();
        orderQueue.pop();
        cout << "Processing: " << o.name << " for " << o.customerName << endl;
    } else cout << "Queue empty.\n";
}

void Cafeteria::displayStack() {
    stack<pair<int, string>> temp = tableStack;
    while (!temp.empty()) {
        auto t = temp.top(); temp.pop();
        cout << "Table " << t.first << ": " << t.second << endl;
    }
}

void Cafeteria::clearStack() {
    while (!tableStack.empty()) tableStack.pop();
    cout << "Stack cleared.\n";
}

void Cafeteria::Additional() {
    int ch;
    do {
        cout << "\n1. clearStack 2. Total 3. Exit\nChoice: ";
        cin >> ch;

        switch (ch) {
            case 1: clearStack(); break;
            case 2: showTotal(); break;
            case 3: saveMenuToFile(); break;
        }
    } while (ch != 3);
}

void Cafeteria::adminMenu() {
    int ch;
    do {
        cout << "\n1.Add 2.Edit 3.Delete 4.Place 5.Menu 6.Summary 7.Stack 8.Queue 9.Process 10.Additional 11.Save & Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: addFoodItem(); break;
            case 2: editFoodItem(); break;
            case 3: deleteFoodItem(); break;
            case 4: placeOrder(); break;
            case 5: displayMenu(); break;
            case 6: displayOrderSummary(); showTotal(); break;
            case 7: displayStack(); break;
            case 8: displayOrderQueue(); break;
            case 9: processOrder(); break;
            case 10: Additional(); break;
            case 11: saveMenuToFile(); break;
        }
    } while (ch != 11);
}

void Cafeteria::mainMenu() {
    int ch;
    do {
        cout << "\n1.Menu 2.Order 3.Queue 4.Get A Price 5.Admin 6.Save & Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: displayMenu(); break;
            case 2: placeOrder(); break;
            case 3: displayOrderQueue(); break;
            case 4: {
                string itemName;
                cout << "Enter item name: ";
                cin >> itemName;
                
    
                float price = getPriceByName(itemName);
                for (auto &item : menu) {
                    if (price > 0 && itemName == item.name)
                        cout << "Price of " << itemName << " is $" << price << endl;
                    else
                        cout << "Item not found.\n";
                    break;
                    }
                }
            case 5: if (admin.authenticate()) adminMenu(); break;
            case 6: saveMenuToFile(); break;
        }
    } while (ch != 6);
}