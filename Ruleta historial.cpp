#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

const int redNumbers[] = {1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36};

bool isRed(int n) {
    for (int i = 0; i < 18; i++) {
        if (redNumbers[i] == n) return true;
    }
    return false;
}

void saveHistory(string type, string option, int result, float bet, bool win) {
    ofstream file("roulette_history.txt", ios::app);
    if (file.is_open()) {
        file << "Type: " << type << " | Option: " << option << " | Result: " << result
             << " | Bet: $" << bet << " | Outcome: " << (win ? "Win" : "Lose") << "\n";
        file.close();
    }
}

void viewHistory() {
    ifstream file("roulette_history.txt");
    string line;
    cout << "\n========= BET HISTORY =========\n";
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Could not open history.\n";
    }
    cout << "===============================\n";
}

void betColor(float& balance) {
    char option;
    float bet;

    do {
        cout << "Choose a color - (r) red, (b) black: ";
        cin >> option;
        option = tolower(option);
    } while (!(option == 'r' || option == 'b'));

    do {
        cout << "How much do you want to bet?: ";
        cin >> bet;
    } while (bet <= 0 || bet > balance);

    int result = rand() % 37;
    cout << "Result: " << result << endl;

    balance -= bet;
    bool win = false;

    if (result == 0) {
        cout << "It's 0. You lose.\n";
    } else {
        bool isResultRed = isRed(result);
        if ((isResultRed && option == 'r') || (!isResultRed && option == 'b')) {
            cout << "You won!\n";
            balance += bet * 2;
            win = true;
        } else {
            cout << "You lost.\n";
        }
    }

    saveHistory("Color", (option == 'r' ? "Red" : "Black"), result, bet, win);
    cout << "Current balance: $" << balance << endl;
}

void betRange(float& balance) {
    int option;
    float bet;

    do {
        cout << "1. Low (1-12)\n2. Medium (13-24)\n3. High (25-36)\nChoose an option: ";
        cin >> option;
    } while (option < 1 || option > 3);

    do {
        cout << "How much do you want to bet?: ";
        cin >> bet;
    } while (bet <= 0 || bet > balance);

    int result = rand() % 37;
    cout << "Result: " << result << endl;

    balance -= bet;
    bool win = false;

    if (result == 0) {
        cout << "It's 0. You lose.\n";
    } else {
        switch (option) {
            case 1: win = (result >= 1 && result <= 12); break;
            case 2: win = (result >= 13 && result <= 24); break;
            case 3: win = (result >= 25 && result <= 36); break;
        }

        if (win) {
            cout << "You won!\n";
            balance += bet * 3;
        } else {
            cout << "You lost.\n";
        }
    }

    string desc = (option == 1 ? "Low" : option == 2 ? "Medium" : "High");
    saveHistory("Range", desc, result, bet, win);
    cout << "Current balance: $" << balance << endl;
}

void betNumber(float& balance) {
    int number;
    float bet;

    do {
        cout << "Choose a number (0-36): ";
        cin >> number;
    } while (number < 0 || number > 36);

    do {
        cout << "How much do you want to bet?: ";
        cin >> bet;
    } while (bet <= 0 || bet > balance);

    int result = rand() % 37;
    cout << "Result: " << result << endl;

    balance -= bet;
    bool win = (result == number);

    if (win) {
        cout << "You won!\n";
        balance += bet * 36;
    } else {
        cout << "You lost.\n";
    }

    saveHistory("Number", to_string(number), result, bet, win);
    cout << "Current balance: $" << balance << endl;
}

void playRoulette(float& balance) {
    if (balance < 100) {
        cout << "Minimum balance required to play is $100.\n";
        return;
    }

    int option;
    char cont;

    do {
        cout << "\n===== ROULETTE MENU =====\n";
        cout << "1. Bet by color\n2. Bet by range\n3. Bet by number\n4. View history\n5. Exit\n";
        cout << "Choose an option: ";
        cin >> option;

        switch (option) {
            case 1: betColor(balance); break;
            case 2: betRange(balance); break;
            case 3: betNumber(balance); break;
            case 4: viewHistory(); break;
            case 5: return;
            default: cout << "Invalid option\n";
        }

        if (option >= 1 && option <= 3) {
            cout << "Do you want to place another bet? (y/n): ";
            cin >> cont;
        } else {
            cont = 'y';
        }

    } while (cont == 'y' || cont == 'Y');
}

int main() {
    srand(time(0));
    float balance;

    cout << "Enter your starting balance: $";
    cin >> balance;

    playRoulette(balance);

    cout << "Thanks for playing. Final balance: $" << balance << endl;
    return 0;
}