#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <chrono>
#include <time.h>

using namespace std;

struct Location {
    float lat;
    float lon;

    Location(float lat, float lon) : lat(lat), lon(lon) {}
};

struct Order {
    int orderId;
    Location pickup;
    Location dropoff;

    Order(int orderId, const Location &pickup, const Location &dropoff) : orderId(orderId), pickup(pickup),
                                                                          dropoff(dropoff) {}
};

void help();

vector<std::string> readLines(ifstream &str);

vector<Order> parseOrders(const vector<std::string> &lines);

void printOrders(const vector<Order> &orders);

Order createOrder();

Order generateOrder();

std::vector<std::string> split(const string &line) {
    std::vector<std::string> result;
    std::stringstream lineStream(line);
    std::string cell;
    while (std::getline(lineStream, cell, ',')) {
        result.push_back(cell);
    }
    return result;
}

int main() {
    ifstream str("D:\\orders.txt");
    vector<std::string> lines = readLines(str);
    vector<Order> orders = parseOrders(lines);
    help();
    bool run = true;
    while (run) {
        string command;
        getline(std::cin, command);
        if (command == "list") {
            printOrders(orders);
        } else if (command == "create") {
            Order order = createOrder();
            orders.push_back(order);
        } else if (command == "generate") {
            Order order = generateOrder();
            orders.push_back(order);
        } else if (command == "exit") {
            run = false;
        }
    }
    return 0;
}

Order generateOrder() {
    int orderId = abs(rand() / 5);
    float pickupLat = (float) rand() / RAND_MAX * (180 - (-180)) + (-180);
    float pickupLon = (float) rand() / RAND_MAX * (90 - (-90)) + (-90);
    float dropoffLat = (float) rand() / RAND_MAX * (180 - (-180)) + (-180);
    float dropoffLon = (float) rand() / RAND_MAX * (90 - (-90)) + (-90);
    Order order = Order(orderId, Location(pickupLat, pickupLon), Location(dropoffLat, dropoffLon));
    return order;
}

Order createOrder() {
    int orderId = abs(rand() / 4);
    float pickupLat;
    float pickupLon;
    float dropoffLat;
    float dropoffLon;
    cin >> pickupLat >> pickupLon >> dropoffLat >> dropoffLon;
    Order order = Order(orderId, Location(pickupLat, pickupLon), Location(dropoffLat, dropoffLon));
    return order;
}

void printOrders(const vector<Order> &orders) {
    for (const auto &order : orders) {
        cout << order.orderId << ' ' << order.pickup.lat << ' ' << order.pickup.lon << ' ' << order.dropoff.lat << ' '
             << order.dropoff.lon << endl;
    }
}

vector<Order> parseOrders(const vector<std::string> &lines) {
    vector<Order> orders;
    for (const string &line : lines) {
        vector<string> orderData = split(line);
        int orderId = stoi(orderData[0]);
        float pickupLat = stof(orderData[1]);
        float pickupLon = stof(orderData[2]);
        float dropoffLat = stof(orderData[3]);
        float dropoffLon = stof(orderData[4]);
        Order order = Order(orderId, Location(pickupLat, pickupLon), Location(dropoffLat, dropoffLon));
        orders.push_back(order);
    }
    return orders;
}

vector<std::string> readLines(ifstream &str) {
    vector<string> lines;
    string line;
    while (getline(str, line)) {
        lines.push_back(line);
    }
    return lines;
}

void help() {
    cout << "Help:\n" <<
         "* list - show existing orders\n" <<
         "* create orderId pickup_lat pickup_long dropoff_lat dropoff_long pick_up_time - create new order\n" <<
         "* generate - generate random order\n" <<
         "* exit - write all data to output.csv file and exit\n"
         << endl;
}
