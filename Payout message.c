#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

#define DEFAULT_COLOR 7
#define INFO_COLOR 11
#define SUCCESS_COLOR 10
#define ERROR_COLOR 12
#define CYAN_COLOR 3

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clearBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}

int readSafeInt(string message, int min, int max) {
    int value;
    while (true) {
        cout << message;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            clearBuffer();
            cout << "Invalid input. Try again.\n";
        } else {
            clearBuffer();
            return value;
        }
    }
}

float readSafeFloat(string message, float min, float max) {
    float value;
    while (true) {
        cout << message;
        cin >> value;
        if (cin.fail() || value < min || value > max) {
            clearBuffer();
            cout << "Invalid input. Try again.\n";
        } else {
            clearBuffer();
            return value;
        }
    }
}

char readSafeChar(string message) {
    char c;
    while (true) {
        cout << message;
        cin >> c;
        clearBuffer();
        c = tolower(c);
        if (c == 'y' || c == 'n') return c;
        cout << "Invalid input. Enter 'y' or 'n'.\n";
    }
}


const int redNumbers[] = {
    1, 3, 5, 7, 9, 12,
    14, 16, 18, 19, 21,
    23, 25, 27, 30, 32, 34, 36
};


bool isRed(int n) {
    for (int num : redNumbers) {
        if (num == n) return true;
    }
    return false;
}


void showPayoutMessage(float gained, float balance) {
    setColor(SUCCESS_COLOR);
    cout << "You gained $" << gained << " this round." << endl;
    setColor(DEFAULT_COLOR);
    cout << "Updated balance: $" << balance << endl;
}

void betColor(float& balance) {
    char option;
    float bet;

    do {
        setColor(INFO_COLOR);
        cout << "\n╔══════════════════════════════╗" << endl;
        cout << "║       COLOR BETTING         ║" << endl;
        cout << "╠══════════════════════════════╣" << endl;
        cout << "║ (r) Red    (pays 1:1)       ║" << endl;
        cout << "║ (b) Black  (pays 1:1)       ║" << endl;
        cout << "║ (g) Green (0) (pays 35:1)   ║" << endl;
        cout << "╚══════════════════════════════╝" << endl;
        cout << "Choose an option: ";
        setColor(DEFAULT_COLOR);
        cin >> option;
        option = tolower(option);
        clearBuffer();

        if (!(option == 'r' || option == 'b' || option == 'g')) {
            setColor(ERROR_COLOR);
            cout << "Invalid option, try again" << endl;
            setColor(DEFAULT_COLOR);
        }
    } while (!(option == 'r' || option == 'b' || option == 'g'));

    bet = readSafeFloat("How much do you want to bet?: $", 1, balance);

    int result = rand() % 37;
    setColor(SUCCESS_COLOR);
    cout << "\nThe wheel spins..." << endl;
    Sleep(1000);
    cout << "Result: " << result << (result == 0 ? " (Green)" : isRed(result) ? " (Red)" : " (Black)") << endl;

    balance -= bet;
    float gained = 0;

    if (option == 'g' && result == 0) {
        gained = bet * 35;
        balance += bet * 36;
    } 
    else if (option == 'r' && isRed(result) && result != 0) {
        gained = bet;
        balance += bet * 2;
    }
    else if (option == 'b' && !isRed(result) && result != 0) {
        gained = bet;
        balance += bet * 2;
    } else {
        setColor(ERROR_COLOR);
        cout << "You lost" << endl;
    }

    if (gained > 0) showPayoutMessage(gained, balance);
    else cout << "Current balance: $" << balance << endl;

    setColor(DEFAULT_COLOR);
}

int main() {
    srand(time(0));
    float balance = 500;
    betColor(balance);
    return 0;
}