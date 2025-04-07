#include <iostream>   
#include <string>       
#include <vector>       
#include <fstream>      
#include <algorithm>    
#include <limits>      
#include "structs.h"    
#include "event.h"     

// Helper function: Converts a string to lowercase for case-insensitive search
std::string toLowerEdit(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

// Function to edit an existing event in the linked list
void editEvent(Node*& head) {
    std::cin.ignore();      // Clear leftover newline character
    system("cls");          // Clear the console (Windows-specific)
    std::cout << "Your choice: 3\n\n✏️ Edit event\n\n";

    // Prompt user to search for an event by keyword
    std::string keyword;
    std::cout << "Enter keyword to search for an event (topic or date): ";
    std::getline(std::cin, keyword);
    std::string lowered = toLowerEdit(keyword); // Convert keyword to lowercase

    std::vector<Node*> matches;     // Stores matching events
    Node* current = head;           // Start at the head of the linked list

    // Traverse list and collect events that match the keyword
    while (current) {
        std::string topic = toLowerEdit(current->data.topic);
        std::string date = toLowerEdit(current->data.date);

        if (topic.find(lowered) != std::string::npos || date.find(lowered) != std::string::npos) {
            matches.push_back(current);  // Save matching node
            std::cout << "\n[" << matches.size() << "] ";
            std::cout << current->data.date << " - " << current->data.title << std::endl;
        }
        current = current->next;
    }

    // If no matches found, return to menu
    if (matches.empty()) {
        std::cout << "\nNo matching events found.\n";
        std::cout << "\nPress Enter to return to menu...";
        std::cin.get();
        return;
    }

    // Let user choose which matching event to edit
    int choice;
    std::cout << "\nSelect which event to edit (1-" << matches.size() << "): ";
    std::cin >> choice;

    // Validate user input
    if (std::cin.fail() || choice < 1 || choice > matches.size()) {
        std::cout << "Invalid choice. Returning to menu...\n";
        std::cin.clear(); // Clear error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard input
        std::cin.get();
        return;
    }

    Node* selected = matches[choice - 1];  // Get selected node
    Event& e = selected->data;             // Reference to the event data

    // Prompt user for which field they want to edit
    std::cout << "\nWhich field do you want to edit?\n";
    std::cout << "1. Date\n2. Topic\n3. Title\n4. Location\n5. Leader\n6. Participants\n7. Outcome\n";
    std::cout << "Your choice: ";
    int field;
    std::cin >> field;
    std::cin.ignore(); // Clear newline

    // Ask for the new value for the selected field
    std::string newValue;
    std::cout << "Enter new value: ";
    std::getline(std::cin, newValue);

    // Update the appropriate field based on user input
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

    // Save updated event list back to file
    overwriteFile(head);

    std::cout << "\n✅ Event updated successfully.\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
}
