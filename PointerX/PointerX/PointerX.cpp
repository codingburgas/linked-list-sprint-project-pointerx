#include <windows.h>       
#include <iostream>       
#include "headers/event.h"         
#include "headers/mainMenu.h"      

int main() {
    //Set console to use UTF-8 encoding to support special characters and emojis
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Node* head = nullptr;  // Initialize the head of the linked list to store events

    //Load all events from file before showing the menu
    loadEventsFromFile(head);

    // Start the main menu loop (user interaction begins here)
    showMainMenu(head);

    // Clean up memory before exiting the program
    clearList(head);

    return 0;
}