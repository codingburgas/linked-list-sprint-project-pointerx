#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "../headers/structs.h"

// Helper function to convert a string to lowercase (for case-insensitive comparisons)
std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

// Function to search events in the linked list based on date or topic
void searchEvents(const Node* head) {
    std::cin.ignore();       // Clear any leftover input
    system("cls");           // Clear the console screen (Windows specific)

    std::cout << "Your choice: 2\n\n";
    std::cout << "🔍 Search by date or topic\n\n";

    // Prompt user to enter a keyword to search
    std::string query;
    std::cout << "🔍 Enter keyword to search (date or topic): ";
    std::getline(std::cin, query);
    std::string loweredQuery = toLower(query);  // Normalize for case-insensitive search

    bool found = false;
    const Node* current = head;

    // Traverse the linked list and compare keyword to each event's date and topic
    while (current) {
        std::string date = toLower(current->data.date);
        std::string topic = toLower(current->data.topic);

        if (date.find(loweredQuery) != std::string::npos ||
            topic.find(loweredQuery) != std::string::npos) {
            found = true;
            const Event& e = current->data;

            // Display the matching event
            std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
            std::cout << "🗓️ Date: " << e.date << "\n";
            std::cout << "📚 Topic: " << e.topic << "\n";
            std::cout << "📝 Title: " << e.title << "\n";
            std::cout << "📍 Location: " << e.location << "\n";
            std::cout << "👤 Leader: " << e.leader << "\n";
            std::cout << "🤝 Participants: " << e.participants << "\n";
            std::cout << "🏁 Outcome: " << e.outcome << "\n";
        }

        current = current->next;  // Move to next node
    }

    // If no matches were found, inform the user
    if (!found) {
        std::cout << "\n⚠️ No events found matching the keyword.\n";
    }

    // Wait for user input before returning to the main menu
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
}