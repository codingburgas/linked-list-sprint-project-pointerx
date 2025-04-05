#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

void showMainMenu() {
    system("cls");

    ifstream file("../../interface/mainMenu.txt");
    if (!file.is_open()) {
        cerr << "Cannot open mainMenu.txt!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();

    int choice;
    cout << "\nYour choice: ";
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInvalid input. Please enter a number from 1 to 6.\n";
        return;
    }

    switch (choice) {
    case 1:
        cout << "\n You selected: Add new event\n";
        break;
    case 2:
        cout << "\n You selected: Search event by date or topic\n";
        break;
    case 3:
        cout << "\n You selected: Edit event\n";
        break;
    case 4:
        cout << "\n You selected: Delete event\n";
        break;
    case 5:
        cout << "\n You selected: Generate report\n";
        break;
    case 6:
        cout << "\n Exiting the application...\n";
        break;
    default:
        cout << "\n Invalid choice! Please enter a number from 1 to 6.\n";
        break;
    }
}
