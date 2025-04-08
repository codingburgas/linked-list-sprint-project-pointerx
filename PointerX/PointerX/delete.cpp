#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <limits>
#include "structs.h"
#include "event.h"

// Converts a string to lowercase for case-insensitive comparison
std::string toLowerDelete(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

// Function to delete an event from a linked list based on a keyword
void deleteEvent(Node*& head) {
    std::cin.ignore();  // Clear any leftover newline characters
    system("cls");      // Clear the console screen
    std::cout << "Your choice: 4\n\n🗑️ Delete event\n\n";

    // Prompt user for a keyword to search
    std::string keyword;
    std::cout << "Enter keyword to search for an event (topic or date): ";
    std::getline(std::cin, keyword);
    std::string lowered = toLowerDelete(keyword); // Convert keyword to lowercase

    std::vector<Node*> matches;      // Stores matching nodes
    std::vector<Node**> nodePointers; // Stores pointers to the pointers of matching nodes (used for deletion)

    Node** currentPtr = &head; // Pointer to the current node pointer

    // Traverse the linked list to find matches
    while (*currentPtr) {
        std::string topic = toLowerDelete((*currentPtr)->data.topic);
        std::string date = toLowerDelete((*currentPtr)->data.date);

        // Check if topic or date contains the keyword
        if (topic.find(lowered) != std::string::npos || date.find(lowered) != std::string::npos) {
            matches.push_back(*currentPtr);       // Store matching node
            nodePointers.push_back(currentPtr);   // Store pointer to the node
            std::cout << "\n[" << matches.size() << "] ";
            std::cout << (*currentPtr)->data.date << " - " << (*currentPtr)->data.title << std::endl;
        }
        currentPtr = &((*currentPtr)->next); // Move to the next node
    }

    // If no events match, notify user and return
    if (matches.empty()) {
        std::cout << "\nNo matching events found.\n";
        std::cout << "\nPress Enter to return to menu...";
        std::cin.get();
        return;
    }

    // Ask user which matching event they want to delete
    int choice;
    std::cout << "\nSelect which event to delete (1-" << matches.size() << "): ";
    std::cin >> choice;
    std::cin.ignore();

    // Validate input
    if (std::cin.fail() || choice < 1 || choice > matches.size()) {
        std::cout << "Invalid choice. Returning to menu...\n";
        std::cin.clear(); // Clear error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        std::cin.get();
        return;
    }

    // Confirm deletion
    std::cout << "\nAre you sure you want to delete this event? (y/n): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();

    // If user cancels, return
    if (confirm != 'y' && confirm != 'Y') {
        std::cout << "Deletion cancelled.\n";
        std::cout << "\nPress Enter to return to the main menu...";
        std::cin.get();
        return;
    }

    // Perform deletion by adjusting pointers and deleting the node
    Node** toDelete = nodePointers[choice - 1]; // Get pointer to the node to delete
    Node* temp = *toDelete;
    *toDelete = (*toDelete)->next; // Bypass the node
    delete temp; // Free memory

    // Update the event storage (e.g., file or database)
    overwriteFile(head);

    std::cout << "\n✅ Event deleted successfully.\n";
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.get();
}

// Function to overwrite the event data to a file
void overwriteFile(Node* head) {
    std::ofstream file("events.txt");  // Open the file in write mode

    Node* current = head;
    while (current) {
        // Write event data to file (can customize the format)
        file << current->data.date << " - " << current->data.title << " - " << current->data.topic << std::endl;
        current = current->next;
    }

    file.close(); // Close the file
}
