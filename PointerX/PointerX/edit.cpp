#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include "structs.h"
#include "event.h"

std::string toLowerEdit(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

void editEvent(Node*& head) {
    std::cin.ignore();
    system("cls");
    std::cout << "Your choice: 3\n\n✏️ Edit event\n\n";

    std::string keyword;
    std::cout << "Enter keyword to search for an event (topic or date): ";
    std::getline(std::cin, keyword);
    std::string lowered = toLowerEdit(keyword);

    std::vector<Node*> matches;
    Node* current = head;
    int index = 1;

    while (current) {
        std::string topic = toLowerEdit(current->data.topic);
        std::string date = toLowerEdit(current->data.date);

        if (topic.find(lowered) != std::string::npos || date.find(lowered) != std::string::npos) {
            matches.push_back(current);
            std::cout << "\n[" << matches.size() << "] ";
            std::cout << current->data.date << " - " << current->data.title << std::endl;
        }
        current = current->next;
    }

    if (matches.empty()) {
        std::cout << "\nNo matching events found.\n";
        std::cout << "\nPress Enter to return to menu...";
        std::cin.get();
        return;
    }

    int choice;
    std::cout << "\nSelect which event to edit (1-" << matches.size() << "): ";
    std::cin >> choice;

    if (std::cin.fail() || choice < 1 || choice > matches.size()) {
        std::cout << "Invalid choice. Returning to menu...\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    Node* selected = matches[choice - 1];
    Event& e = selected->data;

    std::cout << "\nWhich field do you want to edit?\n";
    std::cout << "1. Date\n2. Topic\n3. Title\n4. Location\n5. Leader\n6. Participants\n7. Outcome\n";
    std::cout << "Your choice: ";
    int field;
    std::cin >> field;
    std::cin.ignore();

    std::string newValue;
    std::cout << "Enter new value: ";
    std::getline(std::cin, newValue);

    switch (field) {
        case 1: e.date = newValue; break;
        case 2: e.topic = newValue; break;
        case 3: e.title = newValue; break;
        case 4: e.location = newValue; break;
        case 5: e.leader = newValue; break;
        case 6: e.participants = newValue; break;
        case 7: e.outcome = newValue; break;
        default:
            std::cout << "Invalid field.\n";
            return;
    }

    overwriteFile(head);

    std::cout << "\n✅ Event updated successfully.\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
}
