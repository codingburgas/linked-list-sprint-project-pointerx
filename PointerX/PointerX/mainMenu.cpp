#include <iostream>            
#include <fstream>                
#include <string>               
#include <limits>                
#include "event.h"              
#include "search.h"             
#include "edit.h"                
#include "delete.h"              

// Displays the main menu and handles user interaction
void showMainMenu(Node*& head) {
    system("cls"); // Clear console (Windows-specific)

    // Load and display the main menu from an external text file
    std::ifstream file("../../interface/mainMenu.txt");
    if (!file.is_open()) {
        std::cerr << "Cannot open mainMenu.txt!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl; // Print each line from the menu
    }
    file.close();

    int choice;
    std::cout << "\nYour choice: ";
    std::cin >> choice;

    // Input validation: ensure the user entered a number
    if (std::cin.fail()) {
        std::cin.clear(); // Clear error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Flush bad input
        std::cout << "\nInvalid input. Please enter a number between 1 and 6.\n";
        return;
    }

    // Handle menu options
    switch (choice) {
    case 1:
        std::cout << "\n📌 Add new event\n";
        std::cin.ignore(); // Clear leftover newline from previous input
        system("cls");     // Clear screen before showing input form
        std::cout << "Your choice: 1\n\n📌 Add new event\n";
        addEventSorted(head); // Collect and store new event
        break;

    case 2:
        std::cout << "\n🔍 Search by date or topic\n";
        searchEvents(head); // Search function (likely prompts for input internally)
        break;

    case 3:
        std::cout << "\n✏️ Edit event (coming soon)\n";
        editEvent(head); // Allow user to find and modify an event
        break;

    case 4:
        std::cout << "\n🗑️ Delete event (coming soon)\n";
        deleteEvent(head); // Allow user to remove an event
        break;

    case 5:
        std::cout << "\n📋 List of all events:\n";
        printAllEvents(head); // Display all saved events
        break;

    case 6:
        std::cout << "\n👋 Exiting the program. Freeing memory...\n";
        clearList(head); // Deallocate memory
        return;          // Exit the program
        break;

    default:
        std::cout << "\nPlease enter a valid number between 1 and 6.\n";
    }

    // Prompt user to return to the menu after an action
    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.ignore(); // Clear newline
    std::cin.get();    // Wait for Enter key

    // Recursively call to display menu again
    showMainMenu(head);
}