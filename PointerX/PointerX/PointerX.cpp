
#include <windows.h>
#include <iostream>
#include "event.h"
#include "mainMenu.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Node* head = nullptr;

    // Зареждане от файл преди показване на менюто
    loadEventsFromFile(head);

    showMainMenu(head);

    // Освобождаваме паметта при изход
    clearList(head);

    return 0;
}
