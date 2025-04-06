
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include "structs.h"
#include "event.h"

std::string toLowerDelete(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

void deleteEvent(Node*& head) {
    std::cin.ignore();
    system("cls");
    std::cout << "Your choice: 4\n\n🗑️ Delete event\n\n";

    std::string keyword;
    std::cout << "Enter keyword to search for an event (topic or date): ";
    std::getline(std::cin, keyword);
    std::string lowered = toLowerDelete(keyword);

    std::vector<Node*> matches;
    std::vector<Node**> nodePointers;

    Node** currentPtr = &head;

    while (*currentPtr) {
        std::string topic = toLowerDelete((*currentPtr)->data.topic);
        std::string date = toLowerDelete((*currentPtr)->data.date);

        if (topic.find(lowered) != std::string::npos || date.find(lowered) != std::string::npos) {
            matches.push_back(*currentPtr);
            nodePointers.push_back(currentPtr);
            std::cout << "\n[" << matches.size() << "] ";
            std::cout << (*currentPtr)->data.date << " - " << (*currentPtr)->data.title << std::endl;
        }
        currentPtr = &((*currentPtr)->next);
    }

    if (matches.empty()) {
        std::cout << "\nNo matching events found.\n";
        std::cout << "\nPress Enter to return to menu...";
        std::cin.get();
        return;
    }

    int choice;
    std::cout << "\nSelect which event to delete (1-" << matches.size() << "): ";
    std::cin >> choice;
    std::cin.ignore();

    if (std::cin.fail() || choice < 1 || choice > matches.size()) {
        std::cout << "Invalid choice. Returning to menu...\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    std::cout << "\nAre you sure you want to delete this event? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    if (confirm != 'y' && confirm != 'Y') {
        std::cout << "Deletion cancelled.\n";
        std::cout << "\nPress Enter to return to the main menu...";
        std::cin.get();
        return;
    }

    Node** toDelete = nodePointers[choice - 1];
    Node* temp = *toDelete;
    *toDelete = (*toDelete)->next;
    delete temp;

    overwriteFile(head);

    std::cout << "\n✅ Event deleted successfully.\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
}
