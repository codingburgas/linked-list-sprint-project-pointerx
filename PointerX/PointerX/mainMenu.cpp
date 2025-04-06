
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "event.h"
#include "search.h"

void showMainMenu(Node*& head) {
    system("cls");

    std::ifstream file("../../interface/mainMenu.txt");
    if (!file.is_open()) {
        std::cerr << "Cannot open mainMenu.txt!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();

    int choice;
    std::cout << "\nYour choice: ";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nInvalid input. Please enter a number between 1 and 6.\n";
        return;
    }

    switch (choice) {
        case 1:
            std::cout << "\n📌 Add new event\n";
            std::cin.ignore();
            system("cls");
            std::cout << "Your choice: 1\n\n📌 Add new event\n";
            addEventSorted(head);
            break;
        case 2:
            std::cout << "\n🔍 Search by date or topic\n";
            searchEvents(head);
            break;
        case 3:
            std::cout << "\n✏️ Edit event (coming soon)\n";
            break;
        case 4:
            std::cout << "\n🗑️ Delete event (coming soon)\n";
            break;
        case 5:
            std::cout << "\n📋 List of all events:\n";
            printAllEvents(head);
            break;
        case 6:
            std::cout << "\n👋 Exiting the program. Freeing memory...\n";
            clearList(head);
            return;
        default:
            std::cout << "\nPlease enter a valid number between 1 and 6.\n";
    }

    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.ignore();
    std::cin.get();
    showMainMenu(head);
}
