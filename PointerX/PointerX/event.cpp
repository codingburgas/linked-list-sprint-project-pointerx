
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <direct.h> // за _mkdir
#include "event.h"

const char* DATA_FOLDER = "..\\..\\data";
const char* DATA_FILE = "..\\..\\data\\events.txt";

Event createEventFromInput() {
    Event e;
    std::cout << "\n\t🗓️ Въведи дата (напр. 1876 или 04.1876): ";
    std::getline(std::cin >> std::ws, e.date);

    std::cout << "\t📚 Въведи тема: ";
    std::getline(std::cin, e.topic);

    std::cout << "\t📝 Въведи заглавие: ";
    std::getline(std::cin, e.title);

    std::cout << "\t📍 Въведи място: ";
    std::getline(std::cin, e.location);

    std::cout << "\t👤 Въведи лидер: ";
    std::getline(std::cin, e.leader);

    std::cout << "\t👥 Въведи участници\n";
    std::cout << "\t    👉 Пример: Съюзници: Русия, България | Противници: Османска империя\n";
    std::cout << "\t    Участници: ";
    std::getline(std::cin, e.participants);

    std::cout << "\t🏁 Въведи резултат: ";
    std::getline(std::cin, e.outcome);

    return e;
}

bool isDateBefore(const std::string& d1, const std::string& d2) {
    return d1 < d2;
}

void saveEventToFile(const Event& e) {
    _mkdir(DATA_FOLDER); // създава папка ако не съществува

    std::ofstream out(DATA_FILE, std::ios::app);
    if (!out) {
        std::cerr << "❌ Неуспешен запис във файла events.txt!" << std::endl;
        return;
    }

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

void loadEventsFromFile(Node*& head) {
    std::ifstream in(DATA_FILE);
    if (!in) return;

    std::string line;
    Event e;
    int fieldCount = 0;

    while (std::getline(in, line)) {
        if (line == "---") {
            Node* newNode = new Node{e, nullptr};
            addEventSorted(head, newNode);
            fieldCount = 0;
            continue;
        }

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

void addEventSorted(Node*& head) {
    Event newEvent = createEventFromInput();
    Node* newNode = new Node{newEvent, nullptr};
    addEventSorted(head, newNode);
    saveEventToFile(newEvent);
}

void addEventSorted(Node*& head, Node* newNode) {
    if (!head || isDateBefore(newNode->data.date, head->data.date)) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next && isDateBefore(current->next->data.date, newNode->data.date)) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void printAllEvents(const Node* head) {
    const Node* current = head;
    while (current) {
        const Event& e = current->data;
        std::cout << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n";
        std::cout << "🗓️ Дата: " << e.date << "\n";
        std::cout << "📚 Тема: " << e.topic << "\n";
        std::cout << "📝 Заглавие: " << e.title << "\n";
        std::cout << "📍 Място: " << e.location << "\n";
        std::cout << "👤 Лидер: " << e.leader << "\n";
        std::cout << "🤝 Участници: " << e.participants << "\n";
        std::cout << "🏁 Резултат: " << e.outcome << "\n";
        current = current->next;
    }
}

void clearList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
