
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <limits>
#include <cfloat>

using namespace std;

// ================== COLORES ================== //
enum Colors {
    DEFAULT_COLOR = 7,
    SUCCESS_COLOR = 10,
    INFO_COLOR = 9,
    ERROR_COLOR = 12,
    TIE_COLOR = 14,
    MAGENTA_COLOR = 13,
    CYAN_COLOR = 11
};

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ================== UTILIDADES ================== //
void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int readSafeInt(string message, int min = INT_MIN, int max = INT_MAX) {
    int value;
    while (true) {
        cout << message;
        cin >> value;
        if (cin.fail()) {
            clearBuffer();
            setColor(ERROR_COLOR);
            cout << "Invalid input. Try again.\n";
            setColor(DEFAULT_COLOR);
        } else if (value < min || value > max) {
            setColor(ERROR_COLOR);
            cout << "Value out of range (" << min << "-" << max << "). Try again.\n";
            setColor(DEFAULT_COLOR);
        } else {
            clearBuffer();
            return value;
        }
    }
}

float readSafeFloat(string message, float min = -FLT_MAX, float max = FLT_MAX) {
    float value;
    while (true) {
        cout << message;
        cin >> value;
        if (cin.fail()) {
            clearBuffer();
            setColor(ERROR_COLOR);
            cout << "Invalid input. Please enter a valid number.\n";
            setColor(DEFAULT_COLOR);
        } else if (value < min || value > max) {
            setColor(ERROR_COLOR);
            cout << "Value out of range. Try again.\n";
            setColor(DEFAULT_COLOR);
        } else {
            clearBuffer();
            return value;
        }
    }
}

char readSafeChar(string message) {
    char option;
    while (true) {
        cout << message;
        cin >> option;
        option = tolower(option);
        if (option == 'y' || option == 'n') {
            clearBuffer();
            return option;
        } else {
            setColor(ERROR_COLOR);
            cout << "Invalid option. Only 'y' or 'n'.\n";
            setColor(DEFAULT_COLOR);
            clearBuffer();
        }
    }
}

// ================== JUEGO RULETA ================== //
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
    } while (!(option == 'r' || option == 'b' || option == 'g'));

    bet = readSafeFloat("How much do you want to bet?: $", 1, balance);
    int result = rand() % 37;
    setColor(SUCCESS_COLOR);
    cout << "\nThe wheel spins..." << endl;
    Sleep(1000);
    cout << "Result: " << result << (result == 0 ? " (Green)" : isRed(result) ? " (Red)" : " (Black)") << endl;

    balance -= bet;
    if (option == 'g' && result == 0) {
        setColor(SUCCESS_COLOR);
        cout << "You won $" << bet * 35 << "!" << endl;
        balance += bet * 36;
    } else if (option == 'r' && isRed(result) && result != 0) {
        setColor(SUCCESS_COLOR);
        cout << "You won $" << bet << "!" << endl;
        balance += bet * 2;
    } else if (option == 'b' && !isRed(result) && result != 0) {
        setColor(SUCCESS_COLOR);
        cout << "You won $" << bet << "!" << endl;
        balance += bet * 2;
    } else {
        setColor(ERROR_COLOR);
        cout << "You lost." << endl;
    }
    setColor(DEFAULT_COLOR);
    cout << "Current balance: $" << balance << endl;
}

void betRange(float& balance) {
    int option;
    float bet;
    do {
        setColor(INFO_COLOR);
        cout << "\n1. Low (1-12)\n2. Medium (13-24)\n3. High (25-36)\n";
        cout << "Choose an option: ";
        setColor(DEFAULT_COLOR);
        cin >> option;
        clearBuffer();
    } while (!(option >= 1 && option <= 3));

    bet = readSafeFloat("How much do you want to bet?: $", 1, balance);
    int result = rand() % 37;
    setColor(SUCCESS_COLOR);
    cout << "\nThe wheel spins..." << endl;
    Sleep(1000);
    cout << "Result: " << result << endl;

    balance -= bet;
    bool won = false;
    switch (option) {
        case 1: won = (result >= 1 && result <= 12); break;
        case 2: won = (result >= 13 && result <= 24); break;
        case 3: won = (result >= 25 && result <= 36); break;
    }

    if (result == 0) {
        setColor(ERROR_COLOR);
        cout << "It's 0. You lose." << endl;
    } else if (won) {
        setColor(SUCCESS_COLOR);
        cout << "You won $" << bet * 3 << "!" << endl;
        balance += bet * 3;
    } else {
        setColor(ERROR_COLOR);
        cout << "You lose." << endl;
    }
    setColor(DEFAULT_COLOR);
    cout << "Current balance: $" << balance << endl;
}

void betNumber(float& balance) {
    int number;
    float bet;
    do {
        setColor(INFO_COLOR);
        cout << "\nEnter a number (0-36): ";
        setColor(DEFAULT_COLOR);
        cin >> number;
        clearBuffer();
    } while (number < 0 || number > 36);

    bet = readSafeFloat("How much do you want to bet?: $", 1, balance);
    int result = rand() % 37;
    setColor(SUCCESS_COLOR);
    cout << "\nThe wheel spins..." << endl;
    Sleep(1000);
    cout << "Result: " << result << endl;

    balance -= bet;
    if (result == number) {
        setColor(SUCCESS_COLOR);
        cout << "You won $" << bet * 35 << "!" << endl;
        balance += bet * 36;
    } else {
        setColor(ERROR_COLOR);
        cout << "You lose." << endl;
    }
    setColor(DEFAULT_COLOR);
    cout << "Current balance: $" << balance << endl;
}

void playRoulette(float& balance) {
    if (balance < 100) {
        setColor(ERROR_COLOR);
        cout << "Minimum balance required: $100.\n";
        setColor(DEFAULT_COLOR);
        return;
    }

    int option;
    char continuePlaying;
    do {
        setColor(CYAN_COLOR);
        cout << "\n--- ROULETTE MENU ---\n";
        setColor(DEFAULT_COLOR);
        cout << "1. Bet by color\n2. Bet by range\n3. Bet by number\n4. Exit\n";
        option = readSafeInt("Select an option: ", 1, 4);

        switch (option) {
            case 1: betColor(balance); break;
            case 2: betRange(balance); break;
            case 3: betNumber(balance); break;
            case 4: return;
        }

        if (balance < 100) {
            setColor(ERROR_COLOR);
            cout << "Insufficient balance.\n";
            setColor(DEFAULT_COLOR);
            return;
        }

        continuePlaying = readSafeChar("Do you want to place another bet? (y/n): ");
    } while (continuePlaying == 'y');
}

// ================== MAIN ================== //
int main() {
    srand(time(NULL));
    float balance = readSafeFloat("Enter initial balance (min $100): $", 100);
    playRoulette(balance);
    return 0;
}
