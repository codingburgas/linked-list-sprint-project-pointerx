#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "structs.h"

std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return result;
}

void searchEvents(const Node* head) {
    std::cin.ignore();
    system("cls");

    std::cout << "Your choice: 2\n\n";
    std::cout << "🔍 Search by date or topic\n\n";

    std::string query;
    std::cout << "🔍 Enter keyword to search (date or topic): ";
    std::getline(std::cin, query);
    std::string loweredQuery = toLower(query);

    bool found = false;
    const Node* current = head;

    while (current) {
        std::string date = toLower(current->data.date);
        std::string topic = toLower(current->data.topic);

        if (date.find(loweredQuery) != std::string::npos ||
            topic.find(loweredQuery) != std::string::npos) {
            found = true;
            const Event& e = current->data;
            std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
            std::cout << "🗓️ Date: " << e.date << "\n";
            std::cout << "📚 Topic: " << e.topic << "\n";
            std::cout << "📝 Title: " << e.title << "\n";
            std::cout << "📍 Location: " << e.location << "\n";
            std::cout << "👤 Leader: " << e.leader << "\n";
            std::cout << "🤝 Participants: " << e.participants << "\n";
            std::cout << "🏁 Outcome: " << e.outcome << "\n";
        }

        current = current->next;
    }

    if (!found) {
        std::cout << "\n⚠️ No events found matching the keyword.\n";
    }

    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
}
