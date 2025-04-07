#include <iostream>    
#include <iomanip>      
#include <fstream>      
#include <sstream>      
#include <direct.h>     
#include "event.h"      

// File paths for saving and loading event data
const char* DATA_FOLDER = "..\\..\\data";
const char* DATA_FILE = "..\\..\\data\\events.txt";

// Prompt user to enter event details and return an Event object
Event createEventFromInput() {
    Event e;

    std::cout << "\n\t🗓️ Enter date (e.g. 1876 or 04.1876): ";
    std::getline(std::cin >> std::ws, e.date); // consume leading whitespace

    std::cout << "\t📚 Enter topic: ";
    std::getline(std::cin, e.topic);

    std::cout << "\t📝 Enter title: ";
    std::getline(std::cin, e.title);

    std::cout << "\t📍 Enter location: ";
    std::getline(std::cin, e.location);

    std::cout << "\t👤 Enter leader: ";
    std::getline(std::cin, e.leader);

    std::cout << "\t👥 Enter participants\n";
    std::cout << "\t    👉 Example: Allies: Russia, Bulgaria | Opponents: Ottoman Empire\n";
    std::cout << "\t    Participants: ";
    std::getline(std::cin, e.participants);

    std::cout << "\t🏁 Enter outcome: ";
    std::getline(std::cin, e.outcome);

    return e;
}

// Compare two dates as strings (assumes proper chronological format)
bool isDateBefore(const std::string& d1, const std::string& d2) {
    return d1 < d2; // Simple lexicographical comparison
}

// Save an event to the file by appending to the end
void saveEventToFile(const Event& e) {
    _mkdir(DATA_FOLDER); // Create data folder if it doesn't exist
    std::ofstream out(DATA_FILE, std::ios::app); // Open in append mode

    if (!out) {
        std::cerr << "❌ Failed to write to events.txt!" << std::endl;
        return;
    }

    // Write event fields to file, ending with a separator line
    out << e.date << "\n";
    out << e.topic << "\n";
    out << e.title << "\n";
    out << e.location << "\n";
    out << e.leader << "\n";
    out << e.participants << "\n";
    out << e.outcome << "\n";
    out << "---\n";

    out.close();
}

// Load all events from the file into the linked list
void loadEventsFromFile(Node*& head) {
    std::ifstream in(DATA_FILE);
    if (!in) return; // Return if file doesn't exist

    std::string line;
    Event e;
    int fieldCount = 0; // Tracks which field we're reading

    // Read line-by-line, parsing each event
    while (std::getline(in, line)) {
        if (line == "---") { // End of one event
            Node* newNode = new Node{ e, nullptr };
            addEventSorted(head, newNode); // Insert in sorted order
            fieldCount = 0; // Reset for next event
            continue;
        }

        // Assign fields in order
        switch (fieldCount) {
        case 0: e.date = line; break;
        case 1: e.topic = line; break;
        case 2: e.title = line; break;
        case 3: e.location = line; break;
        case 4: e.leader = line; break;
        case 5: e.participants = line; break;
        case 6: e.outcome = line; break;
        }
        fieldCount++;
    }

    in.close();
}

// Add a new event from user input and save it to both memory and file
void addEventSorted(Node*& head) {
    Event newEvent = createEventFromInput();        // Get user input
    Node* newNode = new Node{ newEvent, nullptr };  // Create new node
    addEventSorted(head, newNode);                  // Insert into linked list
    saveEventToFile(newEvent);                      // Save to file
}

// Insert a new node into the linked list in sorted order by date
void addEventSorted(Node*& head, Node* newNode) {
    // If list is empty or new node should be at the beginning
    if (!head || isDateBefore(newNode->data.date, head->data.date)) {
        newNode->next = head;
        head = newNode;
        return;
    }

    // Traverse the list to find the correct insertion point
    Node* current = head;
    while (current->next && isDateBefore(current->next->data.date, newNode->data.date)) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Display all events in the linked list
void printAllEvents(const Node* head) {
    system("cls");
    std::cout << "Your choice: 5\n\n";
    std::cout << "📋 List of all events:\n";

    const Node* current = head;

    // Traverse and print each event
    while (current) {
        const Event& e = current->data;
        std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        std::cout << "🗓️ Date: " << e.date << "\n";
        std::cout << "📚 Topic: " << e.topic << "\n";
        std::cout << "📝 Title: " << e.title << "\n";
        std::cout << "📍 Location: " << e.location << "\n";
        std::cout << "👤 Leader: " << e.leader << "\n";
        std::cout << "🤝 Participants: " << e.participants << "\n";
        std::cout << "🏁 Outcome: " << e.outcome << "\n";
        current = current->next;
    }

    std::cout << "\nPress Enter to return to the main menu...";
    std::cin.ignore();
    std::cin.get();
}

// Deallocate all memory used by the linked list
void clearList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Overwrite the file with all events from the linked list (used after edits or deletions)
void overwriteFile(const Node* head) {
    _mkdir("..\\..\\data"); // Ensure folder exists
    std::ofstream out("..\\..\\data\\events.txt", std::ios::trunc); // Truncate existing file

    if (!out) {
        std::cerr << "Error overwriting events.txt!" << std::endl;
        return;
    }

    const Node* current = head;

    // Write all events in order
    while (current) {
        const Event& e = current->data;
        out << e.date << "\n";
        out << e.topic << "\n";
        out << e.title << "\n";
        out << e.location << "\n";
        out << e.leader << "\n";
        out << e.participants << "\n";
        out << e.outcome << "\n";
        out << "---\n";
        current = current->next;
    }

    out.close();
}