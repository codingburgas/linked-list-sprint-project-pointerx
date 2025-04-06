
#ifndef EVENT_H
#define EVENT_H

#include "structs.h"

Event createEventFromInput();
void addEventSorted(Node*& head);
void addEventSorted(Node*& head, Node* newNode);
void printAllEvents(const Node* head);
void clearList(Node*& head);
void saveEventToFile(const Event& e);
void loadEventsFromFile(Node*& head);
void overwriteFile(const Node* head); // добавена декларация

#endif
