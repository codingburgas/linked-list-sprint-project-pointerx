
#ifndef EVENT_H
#define EVENT_H

#include <string>
using namespace std;

struct Event {
    string date;       // ключово поле (може да бъде само година или месец/година)
    string topic;
    string title;
    string location;
    string leader;
    string participants;
    string outcome;
};

struct Node {
    Event data;
    Node* next;
};

// Основни функции
void addEventSorted(Node*& head);
void printAllEvents(const Node* head); // за тестване
void clearList(Node*& head); // освобождаване на паметта

#endif
