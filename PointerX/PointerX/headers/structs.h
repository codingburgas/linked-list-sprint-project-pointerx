#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct Event {
    std::string date;
    std::string topic;
    std::string title;
    std::string location;
    std::string leader;
    std::string participants;
    std::string outcome;
};

struct Node {
    Event data;
    Node* next;
};

#endif
