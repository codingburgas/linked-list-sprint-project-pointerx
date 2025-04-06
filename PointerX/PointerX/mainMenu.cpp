
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "event.h"

Node* head = nullptr;

void showMainMenu() {
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
    std::cout << "\nВашият избор: ";
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nНевалиден избор. Моля въведете число от 1 до 6.\n";
        return;
    }

    switch (choice) {
        case 1:
            std::cout << "\n📌 Добавяне на ново събитие\n";
            std::cin.ignore(); // изчистване на буфера
            system("cls");
            std::cout << "Вашият избор: 1\n\n📌 Добавяне на ново събитие\n";
            addEventSorted(head);
            break;
        case 2:
            std::cout << "\n🔍 Търсене по дата или тема (в процес на разработка)\n";
            break;
        case 3:
            std::cout << "\n✏️ Редактиране на събитие (в процес на разработка)\n";
            break;
        case 4:
            std::cout << "\n🗑️ Изтриване на събитие (в процес на разработка)\n";
            break;
        case 5:
            std::cout << "\n📋 Списък на всички събития:\n";
            printAllEvents(head);
            break;
        case 6:
            std::cout << "\n👋 Изход от програмата. Освобождаване на памет...\n";
            clearList(head);
            exit(0);
            break;
        default:
            std::cout << "\nМоля въведете валидно число от 1 до 6.\n";
    }

    std::cout << "\nНатиснете Enter за връщане в менюто...";
    std::cin.ignore();
    std::cin.get();
    showMainMenu();
}
