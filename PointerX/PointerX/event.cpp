
#include <iostream>
#include <iomanip>
#include "event.h"

// Помощна функция за въвеждане на събитие
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

// Сравняване на дати като стрингове
bool isDateBefore(const std::string& d1, const std::string& d2) {
    return d1 < d2;
}

// Добавяне на събитие в списъка, сортирано по дата
void addEventSorted(Node*& head) {
    Event newEvent = createEventFromInput();
    Node* newNode = new Node{newEvent, nullptr};

    if (!head || isDateBefore(newEvent.date, head->data.date)) {
        newNode->next = head;
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next && isDateBefore(current->next->data.date, newEvent.date)) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

// Показване на всички събития (за тестване)
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

// Освобождаване на паметта
void clearList(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}
